#include <iostream>
#include "huffman.h"
#include "windows.h"
using namespace std;

/* Testing huffman coding
int main(){
    /// Testing min_heap
    //min_heap pq = min_heap();
//    insert(pq, 10);
//    insert(pq, 3, 'a');
//    insert(pq, 5, 'c');
//    insert(pq, 7, 'd');
//    cout << size(pq) << " " << pq.cap << endl; /// 4 10000
//    pair <int, char> x = extract(pq); cout << x.first << " " << x.second << endl; /// 3 a
//     x = extract(pq); cout << x.first << " " << x.second << endl; /// 5 c
//     x = extract(pq); cout << x.first << " " << x.second << endl; /// 7 d
//     x = extract(pq); cout << x.first << " " << x.second << endl; /// 10
//     x = extract(pq); cout << x.first << " " << x.second << endl; /// 1e9

    SetConsoleOutputCP(CP_UTF8);
    /// Huffman
    int n = 7;
    char ch[] = {'A', 'E', 'S', 'T', 'P', 'I', '\n'};
    int w[] = {10, 15, 3, 4, 13, 12, 1};
    Node *Tree = HuffmanTree(ch, w, n);
    cout << endl;
    cout << travel(Tree, "") << endl;
    //printTree(Tree, "");c
    cout << endl;
    drawTheTree(Tree, 1, "", "");
    //cout << Tree -> weight << endl;
    deleteTree(Tree);
    drawTheTree(Tree, 1, "", ""); /// empty

    return 0;
    /// test huffmantree with n = 100000 (10^5)
    n = 1e5;
    int w1[100000];
    char w2[100000];
    for (int i = 0; i < n; i++){
        int x = 3LL * i * (i - 3) % 10000007  + 4 * i + 6;
        x %= 10000007;
        char c = x % 26 + 'a';
        w1[i] = x;
        w2[i] = c;
    }
    Tree = HuffmanTree(w2, w1, n);
}
*/
