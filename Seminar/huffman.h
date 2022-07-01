#pragma once
#include "priority_queue.h"

Node *HuffmanTree(char ch[], int w[], int n);
void deleteTree(Node *&root);
int travel(Node *root, string code);
void printTree(Node *root, string str);
void drawTheTree(Node *pRoot, bool isRight, string pattern, string code);
