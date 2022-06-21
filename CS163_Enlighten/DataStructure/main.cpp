#include <iostream>
#include <windows.h>
#include "trie.h"
#include "trie_definition.h"
#include "demo.h"
#include <queue>
#include <map>
using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    //genWords(200000, 100, "randomdata.txt");
    //trie_testing("hihi.txt");
    trie_autocorrect("Datasets130000.txt");
    //trie_definition_testing("Datasets130000.txt");
}
