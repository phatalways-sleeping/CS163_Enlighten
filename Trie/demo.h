#pragma once
#include "clock.h"
#include <iostream>
#include <fstream>
#include <iomanip>

long long Rand(long long l, long long r){
    return l + ((long long) rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
            (long long) rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
            (long long) rand() * (RAND_MAX + 1) +
            (long long) rand()) % (r - l + 1);
}

void genWords(int nums_word, int len_def, string fileName){
    srand(time(NULL));
    ofstream f(fileName);
    clock_t start = clock();
    for (int i = 0; i < nums_word; i++){
        string word = "", def = "";
        int len_word = Rand(1, 10);
        for (int j = 0; j < len_word; j++)
            word.push_back((char) (Rand(65, 90)));
        for (int j = 0; j < len_def; j++)
            def.push_back((char) (Rand(32, 127)));
        f << word << ":" << def << endl;
    }
    cout << "Gen " << nums_word << " words with len_def = " << len_def << " in " << getTime(start, clock()) << " ms\n";
    f.close();
}

void trie_testing(string fileName){
    Trie T;
    string word;
    if (!inputTxtFile(T, fileName)){
        cout << "Can't open file\n";
        return;
    }

    do {
        cout << "Search: "; cin >> word;
        Node *it = search(T, word);
        if (it == NULL || it -> def.empty()) cout << word << " not found!\n";
        else{
            cout << word << ": " << it -> def[0] << endl;
        }
    }
    while (word != "");
}

