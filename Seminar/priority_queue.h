#pragma once
#include <iostream>
#include "Node.h"
using namespace std;

struct min_heap{
    int size, cap, iter;
    Node **data;

    min_heap(){
        iter = size = 0;
        cap = 1e4;
        data = new Node*[cap];
        for (int i = 0; i < cap; i++) data[i] = NULL;
    }
    min_heap(int _cap){
        iter = size = 0;
        cap = _cap;
        data = new Node*[cap];
        for (int i = 0; i < cap; i++) data[i] = NULL;
    }
};
int parent(int id);
int Left(int id);
int Right(int id);
bool empty(min_heap pq);
int size(min_heap pq);
bool insert(min_heap &pq, Node *val);
Node* extract(min_heap &pq);
void modify(min_heap &pq, int id);
