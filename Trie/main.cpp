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
    genWords(500000, 100, "randomdata.txt");
    binaryFileTesting("randomdata.txt");
}
