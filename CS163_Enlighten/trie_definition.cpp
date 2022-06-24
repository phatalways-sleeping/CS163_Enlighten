#pragma once
#include "header.h"

bool build_definition_trie_TxtFile(Trie& T_def, string fileName) {
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
            vector <string> words = splitword(def);
            for (auto w : words)
                if (!insert(T_def, w, word)) {
                    cout << "Can't insert " << w << ": " << word << endl;
                }
                else count++;
            string prefix = "";
            for (auto w : words) {
                prefix += w;
                if (!insert(T_def, prefix, word)) {
                    //cout << "Can't insert " << def << ": " << word << endl;
                }
                else count++;
            }
        }
        else continue;
    }

    cout << "Read data from " << fileName << ": " << count << " words in " << getTime(start, clock()) << " ms\n";
    f.close();
    return true;
}

vector <string> splitword(string str) {
    while (str.size() && str[0] == ' ') str.erase(str.begin());
    while (str.size() && str.back() == ' ') str.pop_back();
    for (int i = str.size() - 1; i > 0; i--) if (str[i] == ' ' && str[i + 1] == ' ')
        str.erase(str.begin() + i);
    /// delete space
    vector <string> ret;
    string tmp = "";
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            ret.push_back(tmp);
            tmp = "";
        }
        else tmp.push_back(str[i]);
    }
    if (tmp != "") ret.push_back(tmp);
    return ret;
}

bool cmp(pair <int, string> x, pair <int, string> y) {
    if (x.first == y.first) return x.second.size() < y.second.size();
    return x.first > y.first;
}

vector <string> search_def(Trie& T, string def, int nums) {
    vector <string> words = splitword(def);
    map <string, int> freq;
    string prefix = "";
    int perfect = 0;
    for (auto w : words) {

        //cout << w << endl;
        Node* info = search(T, w);
        if (info) {
            sort(info->def.begin(), info->def.end());
            int count = unique(info->def.begin(), info->def.end()) - info->def.begin();
            for (int i = 0; i < count; i++) {
                string s = info->def[i];
                if (s != "") freq[s]++;
                //cout << s << endl;
            }
        }
        perfect++;
        prefix += w;
        info = search(T, prefix);
        if (info) {
            sort(info->def.begin(), info->def.end());
            int count = unique(info->def.begin(), info->def.end()) - info->def.begin();
            for (int i = 0; i < count; i++) {
                string s = info->def[i];
                if (s != "") freq[s] += perfect;
                //cout << s << endl;
            }
        }
    }

    vector <pair<int, string>> bestwords;

    for (auto it : freq) {
        string s = it.first;
        int cnt = it.second;
        bestwords.push_back({ cnt, s });
    }
    sort(bestwords.begin(), bestwords.end(), cmp);
    while (bestwords.size() > nums) bestwords.pop_back();
    vector <string> ret;
    for (auto it : bestwords) {
        ret.push_back(it.second);
        //cout << it.second << ": " << it.first << endl;
    }
    return ret;
}
