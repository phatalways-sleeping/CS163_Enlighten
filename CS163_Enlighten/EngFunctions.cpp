#pragma once
#include "header.h"


void clear(Node& m) {
    m.antonyms.clear(); m.synonyms.clear(); m.definitions.clear(); m.word.clear();
}

bool insert(Trie& T, string word, const Node& current) {
    if (word == "") return false;
    Node* root = T.root;
    for (int i = 0; i < word.size(); i++) {
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root->child[ch]) {
            root->child[ch] = new Node();
        }
        root = root->child[ch];
    }
    root->word = word; root->definitions = current.definitions; root->antonyms = current.antonyms; root->synonyms = current.synonyms; 
    return true;
}

bool remove_eng(Trie& T, string word) {
    Node* root = T.root;
    for (int i = 0; i < word.size(); i++) {
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root->child[ch]) return false;
        else root = root->child[ch];
    }
    root->antonyms.clear(); root->definitions.clear(); root->synonyms.clear();
    return true;
}

void convert(json data, Trie& root) {
    Node k;
    //clock_t start = clock();
    for (auto a = data.begin(); a != data.end(); a++) {
        clear(k);
        k.word = a.key();
        for (auto i = a->at("ANTONYMS").begin(); i != a->at("ANTONYMS").end(); i++) k.antonyms.push_back((string)*i);
        for (auto i = a->at("SYNONYMS").begin(); i != a->at("SYNONYMS").end(); i++) k.synonyms.push_back((string)*i);
        for (auto i = a->at("USERDEFINITIONS").begin(); i != a->at("USERDEFINITIONS").end(); i++) k.user_definitions.push_back({i.key(), i.value()});
        auto meanings = a->at("MEANINGS");
        vector<string> examples;
        for (auto b = meanings.begin(); b != meanings.end(); b++) {
            examples.clear();
            for (int j = 2; j < b->size(); j++) {
                if (b->at(j).is_array()) {
                    for (int d = 0; d < b->at(j).size(); d++) examples.push_back(b->at(j)[d]);
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
    for (int i = 0; i < 256; i++) {
        if (T->child[i]) convert(T->child[i], v);
    }
}

bool edit_eng(Trie& T, string word, string username, string new_definition) {
    Node* current = search(T, word);
    if (!current) return false;
    current->user_definitions.push_back({ username, new_definition });
    return true;
}

json writeToJSON(const Trie& T) {
    vector<Node> data; convert(T.root, data);
    json main = json({});
    for (int i = 0; i < data.size(); i++) {
        Node current = data[i];
        json meanings = json({});
        json elements_of_userdefinition = json({});
        for (int j = 0; j < current.user_definitions.size(); j++)
            elements_of_userdefinition[current.user_definitions[j].first] = current.user_definitions[j].second;
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