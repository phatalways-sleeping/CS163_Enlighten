#pragma once
#include "header.h"

bool randomWord(Trie T, pair<string, string>& ques) {
    Node* root = T.root;
    string word = "";
    while (root) {
        vector<int> validChild(0);
        if (root->def.size() > 0 && word != "") {
            for (int i = 0; i < 4; ++i) validChild.push_back(-1);
        }
        for (int i = 0; i < TRIE_LIMIT; ++i) {
            if (root->child[i]) validChild.push_back(i);
        }
        if (validChild.size() == 0) break;
        int nextChild = validChild[Rand(0ll, validChild.size() - 1)];
        if (nextChild == -1) {
            ques = { word, root->def[Rand(0ll, root->def.size() - 1)] };
            return true;
        }
        word += char(nextChild + DEC);
        root = root->child[nextChild];
    }
    return false;
}

vector<vector<string>> revisionWord(Trie T, int level, vector<string> searchHistory, vector<string> favoriteList) {
    srand(time(NULL));
    vector<vector<string>> listWord(0);
    vector<string> mergeList(0);
    for (auto s : searchHistory) if (search(T, s)) mergeList.push_back(s);
    for (auto s : favoriteList) if (search(T, s)) mergeList.push_back(s);
    sort(mergeList.begin(), mergeList.end());
    mergeList.erase(unique(mergeList.begin(), mergeList.end()), mergeList.end());
    int numOld = 0, limSize = 60;
    if (level == 1) numOld = 10;
    else if (level == 2) numOld = 5;
    numOld = min(numOld, (int) mergeList.size());
    cerr << numOld << '\n';

    for (int i = 0; i < 10; ++i) {
        vector<string> word(0);
        pair<string, string> A;
        while (1) {
            if (i >= numOld) {
                while (!randomWord(T, A) || A.first == A.second) {}
            }
            else {
                A.first = mergeList[Rand(0, mergeList.size() - 1)];
                Node* defA = search(T, A.first);
                // bug khi tu trong his va fav ko xuat hien trong tu dien
                A.second = defA->def[Rand(0, defA->def.size() - 1)];
            }
            bool isStop = true;
            for (auto s : listWord) {
                if (s[0] == A.first || s[0] == A.second) {
                    isStop = false;
                    break;
                }
            }
            if (isStop) break;
        }
        pair<string, string> B;
        while (!randomWord(T, B) || B.first == B.second || B.first == A.first) {}
        pair<string, string> C;
        while (!randomWord(T, C) || C.first == C.second || C.first == A.first || C.first == B.first) {}
        pair<string, string> D;
        while (!randomWord(T, D) || D.first == D.second || D.first == A.first || D.first == B.first || D.first == C.first) {}
        if (Rand(0ll, 1ll)) {
            word.push_back(A.first); word.push_back(A.second); word.push_back(A.second); word.push_back(B.second); word.push_back(C.second); word.push_back(D.second);
        }
        else {
            word.push_back(A.second); word.push_back(A.first); word.push_back(A.first); word.push_back(B.first); word.push_back(C.first); word.push_back(D.first);
        }
        for (int j = 0; j < 10; ++j) swap(word[Rand(2ll, 5ll)], word[Rand(2ll, 5ll)]);
        for (int j = 0; j < word.size(); ++j) {
            if (word[j].size() > limSize) {
                while (word[j].size() > limSize) word[j].pop_back();
                word[j] += "...";
            }
        }
        listWord.push_back(word);
    }
    return listWord;
}