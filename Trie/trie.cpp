#pragma once
#include "trie.h"
#include "clock.h"
#include <iostream>
#include <fstream>
#include <iomanip>

bool getstr(string s, string &word, string &def){
    if (s.size() < 3) return false;
    int pos = s.find(':');
    if (pos == s.size()) return false;
    word = s.substr(0, pos);
    def = s.substr(pos + 1);
    return true;
}

bool inputTxtFile(Trie &T, string fileName){
    ifstream f(fileName);
    if (!f.is_open()) {
        cout << "Can't open file!\n";
        return false;
    }

    clock_t start = clock();
    int count = 0;
    while (!f.eof()){
        string s, word = "", def = "";
        getline(f, s, '\n');
        if (getstr(s, word, def)) {
            if (!insert(T, word, def)){
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

Node *search(Trie T, string word){
    Node *root = T.root;
    for (int i = 0; i < word.size(); i++){
        int ch = word[i];
        if (ch < 0 || ch > 255) return NULL;
        if (!root -> child[ch]) return NULL;
        else root = root -> child[ch];
    }
    return root;
}

bool insert(Trie &T, string word, string def){
    if (word == "") return false;
    Node *root = T.root;
    for (int i = 0; i < word.size(); i++){
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root -> child[ch]){
            root -> child[ch] = new Node();
        }
        root = root -> child[ch];
    }
    (root -> def).push_back(def);
    return true;
}

bool edit(Trie &T, string word, int id, string def){
    Node *root = T.root;
    for (int i = 0; i < word.size(); i++){
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root -> child[ch]) return false;
        else root = root -> child[ch];
    }
    root -> def[id] = def;
    return true;
}

bool remove(Trie &T, string word){
    Node *root = T.root;
    for (int i = 0; i < word.size(); i++){
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root -> child[ch]) return false;
        else root = root -> child[ch];
    }
    root -> def.clear();
    return true;
}
bool reset(Trie &T){

}

