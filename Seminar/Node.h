#pragma once

struct Node{
    int weight;
    char ch = '\0';
    Node *left = NULL, *right = NULL;
    Node(){
        weight = 0;
        ch = '\0';
        left = right = NULL;
    }
    Node(int val){
        weight = val;
        ch = '\0';
        left = right = NULL;
    }
    Node(int val, char __ch){
        weight = val;
        ch = __ch;
    }
};


