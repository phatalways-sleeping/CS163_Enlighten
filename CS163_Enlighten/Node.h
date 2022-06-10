#pragma once
#include<string>
using std::string;
struct Node {
    string data;
    Node* next = nullptr;
    Node(string value, Node* next_) { data = value; next = next_; }
};

bool contains(Node* head, string value) {
    while (head) {
        if (head->data == value) return true;
        head = head->next;
    }
    return false;
}

void insert(Node*& head, string value) {
    if (!contains(head, value)) head = new Node(value, head);
}

void remove(Node*& head, string value) {
    if (!head) return;
    Node* current = head, * prev = nullptr;
    while (current && current->data != value) {
        prev = current;
        current = current->next;
    }
    if (!current) return;
    if (!prev) {
        head = head->next;
    }
    else {
        prev->next = current->next;
    }
    delete current;
}