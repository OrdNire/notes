#include <iostream>
#include "AVLTree.h"
using namespace std;

int main()
{
    AVLTree<int> tree;
    int n;
    cin >> n;
    for(int i = 0;i < n;i ++) {
        int x;
        cin >> x;
        tree.insert(x);
    }
    cout << "=====pre=====" << endl;
    tree.preOrder();
    cout << "=====in=====" << endl;
    tree.inOrder();
    cout << "=====post=====" << endl;
    tree.postOrder();

    tree.remove(88);
    tree.remove(100);

    cout << "=======" << endl;
    tree.preOrder();
    auto t = tree.search_recurse(88);
    if(t == nullptr) cout << "null" << endl;
    else cout << t->key << endl;

    t = tree.search_recurse(65);
    if(t == nullptr) cout << "null" << endl;
    else cout << t->key << endl;

    cout << tree.get_root_value();
    
    return 0;
}