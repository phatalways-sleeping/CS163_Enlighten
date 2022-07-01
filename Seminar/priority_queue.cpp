#pragma once
#include "priority_queue.h"

bool empty(min_heap pq){
    return pq.size == 0;
}
int size(min_heap pq){
    return pq.size;
}

bool insert(min_heap &pq, Node *val){
    if (pq.size == pq.cap) return false;
    int id = pq.size++;
    pq.data[id] = val;
    while (id != 0 && pq.data[parent(id)]->weight > pq.data[id]->weight){
        swap(pq.data[id], pq.data[parent(id)]);
        id = parent(id);
    }
    return true;
}
Node *extract(min_heap &pq){
    if (empty(pq)) return NULL;
    Node *ret = pq.data[0];
    swap(pq.data[0], pq.data[--pq.size]);
    modify(pq, 0);
    return ret;
}

void modify(min_heap &pq, int id){
    int l = Left(id), r = Right(id);
    int best = l;
    if (r < pq.size && pq.data[best]->weight > pq.data[r]->weight)
        best = r;
    if (best < pq.size && pq.data[best]->weight < pq.data[id]->weight){
        swap(pq.data[best], pq.data[id]);
        modify(pq, best);
    }
}

int parent(int id){
    return (id - 1) / 2;
}

int Left(int id){
    return id * 2 + 1;
}

int Right(int id){
    return id * 2 + 2;
}
