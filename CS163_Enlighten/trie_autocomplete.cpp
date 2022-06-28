#pragma once
#include "header.h"

void fillCompleteList(Node* cur, string word, vector<string>& completeList, int limit)
{
    if (!cur || int(completeList.size()) >= limit) return;
    if (int(cur->def.size()) > 0) completeList.push_back(word);
    for (int i = 0; i < TRIE_LIMIT; i++)
    {
        char ch = char(i) + DEC;
        if (cur->child[i])
        {
            fillCompleteList(cur->child[i], word + ch, completeList, limit);
        }
        if (int(completeList.size()) >= limit) return;
    }
}

vector<string> autocomplete(Trie T, string word, int limit)
{
    vector<string> completeList(0);
    Node* root = T.root;
    for (unsigned int i = 0; i < word.size(); i++)
    {
        int ch = word[i] - DEC;
        if (ch < 0 || ch >= TRIE_LIMIT || !root->child[ch]) return completeList;
        root = root->child[ch];
    }
    fillCompleteList(root, word, completeList, limit);
    return completeList;
}