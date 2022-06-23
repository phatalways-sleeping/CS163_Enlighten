#pragma once
#include "header.h"

long long Rand(long long l, long long r) {
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
        (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
        (long long)rand() * (RAND_MAX + 1) +
        (long long)rand()) % (r - l + 1);
}


void genWords(int nums_word, int len_def, string fileName) {
    srand(time(NULL));
    ofstream f(fileName);
    clock_t start = clock();
    for (int i = 0; i < nums_word; i++) {
        string word = "", def = "";
        int len_word = Rand(1, 10);
        for (int j = 0; j < len_word; j++)
            word.push_back((char)(Rand(65, 90)));
        for (int j = 0; j < len_def; j++)
            def.push_back((char)(Rand(32, 127)));
        f << word << ":" << def << endl;
    }
    cout << "Gen " << nums_word << " words with len_def = " << len_def << " in " << getTime(start, clock()) << " ms\n";
    f.close();
}

void trie_testing(string fileName) {
    Trie T;
    string word;
    if (!inputTxtFile(T, fileName)) {
        cout << "Can't open file\n";
        return;
    }

    do {
        cout << "Search: "; cin >> word;
        Node* it = search(T, word);
        if (it == NULL || it->def.empty()) cout << word << " not found!\n";
        else {
            cout << word << ": ";
            for (auto s : it->def) cout << s << ", ";
            cout << endl;
        }
    } while (word != "vinhne");
}

void trie_definition_testing(string fileName) {
    Trie T_def;
    build_definition_trie_TxtFile(T_def, fileName);
    string def;
    while (getline(cin, def)) {
        cout << def << " -> top 5 words: ";
        vector<string> top = search_def(T_def, def, 5);
        for (auto s : top) cout << s << " ";
        cout << endl;
    }
}

void trie_autocorrect(string fileName) {
    Trie T;
    string word;
    if (!inputTxtFile(T, fileName)) {
        cout << "Can't open file\n";
        return;
    }

    while (getline(cin, word)) {
        cout << "Search: " << word << endl;
        vector <string> autocorrect = correct_words(T, word, 10);
        cout << "Do you mean:\n";
        int count = 0;
        for (int i = 0; i < autocorrect.size(); i++) {
            string w = autocorrect[i];
            Node* info = search(T, w);
            if (info) {
                count++;
                cout << "\t" << count << " - " << w << ": ";
                for (auto s : info->def) cout << s << " ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
}

void trie_revision_testing(string fileName, vector<string> searchHistory, vector<string> favoriteList) {
    Trie T;
    if (!inputTxtFile(T, fileName)) {
        cout << "Can't open file\n";
        return;
    }
    srand(time(NULL));
    vector<vector<string>> listWord = revisionWord(T, 1, searchHistory, favoriteList);
    for (auto i : listWord) {
        cout << i[0] << ":\n";
        int correctAns;
        for (int j = 2; j <= 5; ++j) {
            cout << char('A' + j - 2) << ". " << i[j] << '\n';
            if (i[j] == i[1]) correctAns = j;
        }
        cout << "Answer: ";
        char ans;
        cin >> ans;
        if (ans - 'A' + 2 != correctAns) cout << "Incorrect, answer is: " << char('A' + correctAns - 2);
        else cout << "Correct";

        cout << "\n\n";
    }
}