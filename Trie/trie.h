#ifndef TRIE_H
#define TRIE_H

#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Node{
    vector <string> def;
    Node *child[256];
    Node(){
        for (int i = 0; i < 256; i++) child[i] = NULL;
    }
};

struct Trie{
    Node *root = new Node();
};

bool inputTxtFile(Trie &T, string fileName);
void writeBinaryFile(ofstream &f, Node* node);
bool outputBinaryFile(Trie T,  string fileName);
void readBinaryFile(ifstream &f, Node* &node);
bool inputBinaryFile(Trie &T, string fileName);

Node *search(Trie T, string keyword); // return all definitions
bool insert(Trie &T, string word, string def);
bool edit(Trie &T, string word, int id, string def);
bool remove(Trie &T, string word);
bool reset(Trie &T);

#endif
