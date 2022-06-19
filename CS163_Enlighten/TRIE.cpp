#include"struct_and_dependencies.h"


void clear(MEANINGS& m) {
    m.antonyms.clear(); m.synonyms.clear(); m.definitions.clear(); m.word.clear();
}

MEANINGS* search(TRIE T, string word) {
    MEANINGS* root = T.root;
    for (int i = 0; i < word.size(); i++) {
        int ch = word[i];
        if (ch < 0 || ch > 255) return NULL;
        if (!root->child[ch]) return NULL;
        else root = root->child[ch];
    }
    return root;
}

bool insert(TRIE& T, string word, const MEANINGS& current) {
    if (word == "") return false;
    MEANINGS* root = T.root;
    for (int i = 0; i < word.size(); i++) {
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root->child[ch]) {
            root->child[ch] = new MEANINGS();
        }
        root = root->child[ch];
    }
    root->word = word; root->definitions = current.definitions; root->antonyms = current.antonyms; root->synonyms = current.synonyms; root->examples = current.examples;
    return true;
}

bool remove(TRIE& T, string word) {
    MEANINGS* root = T.root;
    for (int i = 0; i < word.size(); i++) {
        int ch = word[i];
        if (ch < 0 || ch > 255) return false;
        if (!root->child[ch]) return false;
        else root = root->child[ch];
    }
    root->antonyms.clear(); root->definitions.clear(); root->examples.clear(); root->synonyms.clear();
    return true;
}

void convert(json data, TRIE& root) {
    MEANINGS k;
    //clock_t start = clock();
    for (auto a = data.begin(); a != data.end(); a++) {
        clear(k);
        k.word = a.key();
        for (auto i = a->at("ANTONYMS").begin(); i != a->at("ANTONYMS").end(); i++) k.antonyms.push_back((string)*i);
        for (auto i = a->at("SYNONYMS").begin(); i != a->at("SYNONYMS").end(); i++) k.synonyms.push_back((string)*i);
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