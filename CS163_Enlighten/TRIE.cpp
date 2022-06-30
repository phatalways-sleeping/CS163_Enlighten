#pragma once
#include "header.h"

bool getstr(string s, string& word, string& def) {
    if (s.size() < 3) return false;
    int pos = s.find('\t');
    if (pos == s.size()) return false;
    word = s.substr(0, pos);
    def = s.substr(pos + 1);

    return true;
}

Node* search(Trie &T, string word) {
    Node* root = T.root;
    for (unsigned int i = 0; i < word.size(); i++) {
        int ch = word[i] - DEC;
        if (ch < 0 || ch >= TRIE_LIMIT) {
            //insert(T, word, "");
            return NULL;
        }
        if (!root->child[ch]) {
            //insert(T, word, "");
            return NULL;
        }
        else root = root->child[ch];
    }
    if (!root || root->word.empty()) return NULL;
    return root;
}

bool insert(Trie& T, string word, string def) {
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
    (root->def).push_back(def);
    root->word = word;
    vector <string> examples;
    pair <string, string> type_and_defi = { "", def };
    root->definitions.push_back({ type_and_defi, examples });
    return true;
}
bool insert(Trie& T, string word, string type, string def) {
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
    (root->def).push_back(def);
    root->word = word;
    vector <string> examples;
    pair <string, string> type_and_defi = { type, def };
    root->definitions.push_back({ type_and_defi, examples });
    return true;
}

bool edit(Trie& T, string word, int id, string def) {
    Node* root = T.root;
    for (unsigned int i = 0; i < word.size(); i++) {
        int ch = word[i] - DEC;
        if (ch < 0 || ch >= TRIE_LIMIT) return false;
        if (!root->child[ch]) return false;
        else root = root->child[ch];
    }
    root->def[id] = def;
    return true;
}

bool remove(Trie& T, string word) {
    Node* root = T.root;
    for (unsigned int i = 0; i < word.size(); i++) {
        int ch = word[i] - DEC;
        if (ch < 0 || ch >= TRIE_LIMIT) return false;
        if (!root->child[ch]) return false;
        else root = root->child[ch];
    }
    root->def.clear();
    return true;
}

void deallocateNode(Node *&node) {
    if (!node) return;
    for (int i = 0; i < TRIE_LIMIT; ++i) {
        if (node->child[i]) deallocateNode(node->child[i]);
    }
    node->def.clear();
    node->definitions.clear();
    node->user_definitions.clear();
    node->antonyms.clear();
    node->synonyms.clear();
    delete node;
}

void reset(Trie& T) {
    deallocateNode(T.root);
    T.root = NULL;
}


bool inputTxtFile(Trie& T, string fileName) {
    ifstream f(fileName);
    if (!f.is_open()) {
        cout << "Can't open file!\n";
        return false;
    }

    clock_t start = clock();
    int count = 0;
    while (!f.eof()) {
        string s, word = "", def = "";
        getline(f, s, '\n');
        if (getstr(s, word, def)) {
            if (!insert(T, word, def)) {
                cout << "Can't insert " << word << ": " << def << endl;
            }
            else count++;
        }
        else continue;
    }

    cout << "Read data from " << fileName << ": " << count << " words in " << getTime(start, clock()) << " ms\n";
    f.close();
    return true;
}

void writeBinaryFile(ofstream& f, Node* node) {
    if (!node) return;
    int defSize = node->def.size();
    f.write((char*)&defSize, sizeof(int));
    for (int i = 0; i < defSize; i++) {
        string s = node->def[i];
        f.write(s.c_str(), s.size());
        f.write("\0", sizeof(char));
    }
    for (int i = 0; i < TRIE_LIMIT; i++) {
        if (node->child[i]) {
            f.write((char*)&i, sizeof(int));
            writeBinaryFile(f, node->child[i]);
        }
    }
    int delim = -1;
    f.write((char*)&delim, sizeof(int));
}

bool outputBinaryFile(Trie T, string fileName) {
    ofstream f(fileName, ios::binary);
    if (!f.is_open()) {
        f.close();
        return false;
    }
    writeBinaryFile(f, T.root);
    f.close();
    return true;
}

void readBinaryFile(ifstream& f, Node*& node) {
    int defSize;
    f.read((char*)&defSize, sizeof(int));
    for (int i = 0; i < defSize; i++) {
        string def;
        getline(f, def, '\0');
        node->def.push_back(def);
    }

    int cur = 0;
    while (1) {
        f.read((char*)&cur, sizeof(int));
        if (cur == -1) break;
        if (!node->child[cur]) node->child[cur] = new Node;
        readBinaryFile(f, node->child[cur]);
    }
}

bool inputBinaryFile(Trie& T, string fileName) {
    ifstream f(fileName, ios::binary);
    if (!f.is_open()) {
        f.close();
        return false;
    }
    clock_t start = clock();
    readBinaryFile(f, T.root);
    cout << "Read data from " << fileName << " in " << getTime(start, clock()) << " ms\n";
    f.close();
    return true;
}

