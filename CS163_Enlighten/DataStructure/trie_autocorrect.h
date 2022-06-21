#pragma once
#include "trie.h"

vector <string> correct_words(Trie T, string word, int nums){
    vector <string> ret;
    string new_word = word;
    /// fix 1 char
    Node *info = search(T, word);
    if (info && info -> def.size()) ret.push_back(word);
    for (int i = word.size() - 1; i >= 0; i--){
        for (char ch = 'a'; ch <= 'z'; ch++) if (ch != word[i]){
            new_word[i] = ch;
            info = search(T, new_word);
            if (info && info -> def.size())
                ret.push_back(new_word);
        }
        new_word[i] = word[i];
    }

    /// erase 1 char
    for (int i = word.size() - 1; i >= 0; i--){
        new_word = word;
        new_word.erase(new_word.begin() + i);
        info = search(T, new_word);
            if (info && info -> def.size())
                ret.push_back(new_word);
    }

    /// insert 1 char
    for (int i = word.size(); i >= 0; i--){

        for (char ch = 'a'; ch <= 'z'; ch++){
            new_word = word;
            new_word.insert(new_word.begin() + i, ch);
            info = search(T, new_word);
                if (info && info -> def.size())
                    ret.push_back(new_word);
        }
    }


    /// return
    if (ret.size() > 1)
    sort(ret.begin() + 1, ret.end());
    while (ret.size() > nums) ret.pop_back();
    return ret;
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
