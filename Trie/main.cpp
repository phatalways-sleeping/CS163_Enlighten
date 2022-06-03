#include <iostream>
#include <windows.h>
#include "trie.h"
#include "demo.h"
using namespace std;

int main()
{
    string word = "";
    word.push_back((char) (Rand(32, 127)));
    cout << word << endl;
    SetConsoleOutputCP(CP_UTF8);
    genWords(100000, 100, "randomdata.txt");
    trie_testing("randomdata.txt");
}
