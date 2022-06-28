#pragma once
#include "header.h"


void clear(Node& m) {
    m.antonyms.clear(); m.synonyms.clear(); m.definitions.clear(); m.word.clear();
}

bool insert(Trie& T, string word, const Node& current) {
    if (word == "") return false;
    Node* root = T.root;
    for (unsigned int i = 0; i < word.size(); i++) {
        int ch = word[i] - DEC;
        if (ch < 0 || ch >= TRIE_LIMIT) return false;
        if (!root->child[ch]) {
            root->child[ch] = new Node();
        }
        root = root->child[ch];
    }
    root->word = word; root->definitions = current.definitions; root->antonyms = current.antonyms; root->synonyms = current.synonyms; 
    root->user_definitions = current.user_definitions;
    for (auto info : current.definitions) {
        string def = info.first.second;
        root->def.push_back(def);
    }
    return true;
}

bool remove_eng(Trie& T, string word) {
    Node* root = T.root;
    for (unsigned int i = 0; i < word.size(); i++) {
        int ch = word[i] - DEC;
        if (ch < 0 || ch >= TRIE_LIMIT) return false;
        if (!root->child[ch]) return false;
        else root = root->child[ch];
    }
    root->antonyms.clear(); root->definitions.clear(); root->synonyms.clear();
    return true;
}

string normalize(string s) {
    string ns = "";
    for (int i = 0; i < s.size(); i++) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            ns += s[i] - 'A' + 'a';
        }
        else {
            ns += s[i];
        }
    }
    return ns;
}

void convert(json data, Trie& root) {
    Node k;
    //clock_t start = clock();
    for (auto a = data.begin(); a != data.end(); a++) {
        clear(k);
        k.word = normalize(a.key());
        for (auto i = a->at("ANTONYMS").begin(); i != a->at("ANTONYMS").end(); i++) k.antonyms.push_back((string)*i);
        for (auto i = a->at("SYNONYMS").begin(); i != a->at("SYNONYMS").end(); i++) k.synonyms.push_back((string)*i);
        for (auto i = a->at("USERDEFINITIONS").begin(); i != a->at("USERDEFINITIONS").end(); i++) {
            UserDef info;
            info.definition = i.key();
            info.username = i->at(0); info.like = i->at(1); info.dislike = i->at(2);
            for (auto u = 0; u < i->at(3).size(); u++)  info.list.push_back({ i->at(3)[u][0], i->at(3)[u][1] });
            k.user_definitions.push_back(info);
        }
        auto meanings = a->at("MEANINGS");
        vector<string> examples;
        for (auto b = meanings.begin(); b != meanings.end(); b++) {
            examples.clear();
            for (unsigned int j = 2; j < b->size(); j++) {
                if (b->at(j).is_array()) {
                    for (unsigned int d = 0; d < b->at(j).size(); d++) examples.push_back(b->at(j)[d]);
                }
            }
            k.definitions.push_back({ {b->at(0), b->at(1)}, examples });
        }
        insert(root, k.word, k);
    }
    //cout << "READ DATA IN " << getTime(start, clock()) << "ms";
}

void convert(Node* T, vector<Node>& v) {
    if (!T) return;
    if (!T->word.empty()) v.push_back(*T);
    for (int i = 0; i < TRIE_LIMIT; i++) {
        if (T->child[i]) convert(T->child[i], v);
    }
}

bool edit_eng(Trie& T, string word, string username, string new_definition) {
    Node* current = search(T, word);
    if (!current) return false;
    current->user_definitions.push_back({ username, new_definition });
    return true;
}

json writeToJSON(Node* root) {
    vector<Node> data; convert(root, data);
    json main = json({});
    for (int i = 0; i < data.size(); i++) {
        Node current = data[i];
        json meanings = json({});
        json elements_of_userdefinition = json({});
        for (int j = 0; j < current.user_definitions.size(); j++) {
            json info = json::array();
            info.push_back(current.user_definitions[j].username);  info.push_back(current.user_definitions[j].like);
            info.push_back(current.user_definitions[j].dislike);  info.push_back(current.user_definitions[j].list);
            elements_of_userdefinition[current.user_definitions[j].definition] = info;
        }
        json elements_of_meanings = json({});
        for (int j = 0; j < current.definitions.size(); j++) {
            pair<pair<string, string>, vector<string>> p = current.definitions[j];
            json a = { p.first.first, p.first.second, p.second };
            elements_of_meanings[to_string(j + 1)] = a;
        }
        meanings["MEANINGS"] = elements_of_meanings;
        meanings["ANTONYMS"] = current.antonyms;
        meanings["SYNONYMS"] = current.synonyms;
        meanings["USERDEFINITIONS"] = elements_of_userdefinition;
        main[current.word] = meanings;
    }
    return main;
}

bool writeJson(const Trie& T, string path) {
    if (path.empty() || !T.root) return false;
    ofstream file(path, ios::out);
    if (file.fail()) {
        file.close();
        return false;
    }
    json data = writeToJSON(T.root);
    file << data;
    file.close();
    return true;
}

bool readJson(Trie& T, string path) {
    if (path.empty()) return false;

    ifstream data_file(path, ifstream::binary);
    if (data_file.fail()) {
        data_file.close();
        return false;
    }

    json data; data_file >> data;
    data_file.close();
    convert(data, T);
    return true;
}