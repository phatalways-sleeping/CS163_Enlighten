#pragma once
#include "header.h"
//----------------------------------------------------------------------------------------------------

vector <string> correct_words(Trie T, string word, int nums) {
    vector <string> ret;
    string new_word = word;
    Node* info = search(T, word);
    if (info && info->def.size()) ret.push_back(word);
    /// swap adj-char

    for (int i = word.size() - 1; i > 0; i--) if (word[i] != word[i - 1]) {
        new_word = word;
        swap(new_word[i], new_word[i - 1]);
        info = search(T, new_word);
        if (info && info->def.size())
            ret.push_back(new_word);
    }

    /// erase 1 char
    for (int i = word.size() - 1; i >= 0; i--)if (i == 0 || word[i] != word[i - 1]) {
        new_word = word;
        new_word.erase(new_word.begin() + i);
        info = search(T, new_word);
        if (info && info->def.size())
            ret.push_back(new_word);
    }

    /// insert 1 char
    for (int i = word.size(); i >= 0; i--) {
        for (char ch = 'a'; ch <= 'z'; ch++) {
            new_word = word;
            new_word.insert(new_word.begin() + i, ch);
            info = search(T, new_word);
            if (info && info->def.size())
                ret.push_back(new_word);
        }
    }

    /// fix 1 char
    new_word = word;
    for (int i = word.size() - 1; i >= 0; i--) {
        for (char ch = 'a'; ch <= 'z'; ch++) if (ch != word[i]) {
            new_word[i] = ch;
            info = search(T, new_word);
            if (info && info->def.size())
                ret.push_back(new_word);
        }
        new_word[i] = word[i];
    }

    /// return
    //if (ret.size() > 1) sort(ret.begin() + 1, ret.end());
    string path = JSONPATH + "unigram_freq.csv";
    return EV(path, ret);

    int cnt = unique(ret.begin(), ret.end()) - ret.begin();
    vector <string> final_words;
    for (int i = 0; i < min(cnt, nums); i++)
        final_words.push_back(ret[i]);
    return final_words;
}

double EEV(string input, vector<string> v) {
    int length = input.length();
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
        int s = (v[i].length() <= length) ? v[i].length() : length;
        for (int j = 0; j < s; j++) {
            if (input[j] == v[i][j]) count++;
        }
    }
    return (double)count / (length * v.size());
}

vector<string> EV(string path, vector<string> v) {
    WordTrie tree;  getTree(path, tree);
    vector<pair<double, int>> s;
    for (int i = 0; i < v.size(); i++) s.push_back({ (search(tree, v[i])) ? search(tree, v[i])->freq : 0, i });
    //sort(s.begin(), s.end(), less<pair<double, int>>());
    vector<string> k;
    for (int i = 0; i < v.size(); i++)
        k.push_back(v[s[i].second]);
    //k.push_back(v[s[1].second]); k.push_back(v[s[2].second]);
    return k;
}

Word* search(WordTrie T, string word) {
    Word* root = T.root;
    for (int i = 0; i < word.size(); i++) {
        int ch = word[i];
        if (ch < 0 || ch > 255) return NULL;
        if (!root->child[ch]) return NULL;
        else root = root->child[ch];
    }
    return root;
}

bool insert(WordTrie& T, string word, double freq) {
    if (word == "") return false;
    Word* root = T.root;
    for (int i = 0; i < word.size(); i++) {
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root->child[ch]) {
            root->child[ch] = new Word();
        }
        root = root->child[ch];
    }
    root->freq = freq;
    return true;
}

void getTree(string path, WordTrie& root) {
    ifstream file(path, ios::in);
    if (file.is_open()) {
        vector<pair<string, double>> v;
        string line, word;
        vector<string> k;
        while (getline(file, line)) {
            stringstream s(line);
            k.clear();
            while (getline(s, word, ',')) k.push_back(word);
            v.push_back({ k[0], stod(k[1]) / TOTAL });
        }
        for (int i = 0; i < v.size(); i++) insert(root, v[i].first, v[i].second);
        cout << v[0].first << "-" << v[0].second << endl;
    }
    file.close();
}

