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
    int cnt = unique(ret.begin(), ret.end()) - ret.begin();
    vector <string> final_words;
    for (int i = 0; i < min(cnt, nums); i++)
        final_words.push_back(ret[i]);
    return final_words;
}

double EV(string input, vector<string> v) {
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
