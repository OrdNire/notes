#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_
#include <iostream>
using namespace std;

// 节点结构
template <typename T>
struct AVLTreeNode {
    AVLTreeNode(T value, AVLTreeNode<T> *l, AVLTreeNode<T> *r)
        : key(value), lchild(l), rchild(r) {}

    T key;
    int height;
    AVLTreeNode<T> *lchild;
    AVLTreeNode<T> *rchild;
};

template <typename T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void preOrder();    // 前序遍历
    void inOrder();     // 中序遍历
    void postOrder();   // 后序遍历

    void destroy();     // 销毁AVL树

    void insert(T key); // 插入
    void remove(T key); // 移除

    AVLTreeNode<T> *search_recurse(T key);  // 递归搜素指定值
    AVLTreeNode<T> *search_iterator(T key); // 迭代搜素
    T minimum();        // 返回最小值
    T maximum();        // 返回最大值

    int height();       // 返回树的高度

    T get_root_value() const;

private:
    AVLTreeNode<T> *root;   // 根
private:
    void preOrder(AVLTreeNode<T>* pnode) const;
    void inOrder(AVLTreeNode<T>* pnode) const;
    void postOrder(AVLTreeNode<T>* pnode) const;
 
    void destroy(AVLTreeNode<T>* pnode);
    int  height(AVLTreeNode<T>* root);
    int  max(int a, int b);
 
    AVLTreeNode<T>* insert(AVLTreeNode<T>* pnode, T key);       
    AVLTreeNode<T>* remove(AVLTreeNode<T>* pnode, T key); //删除AVL树中节点，并返回被删除的节点
 
    AVLTreeNode<T>* minimum(AVLTreeNode<T>* pnode) const;
    AVLTreeNode<T>* maximum(AVLTreeNode<T>* pnode) const;
 
    AVLTreeNode<T>* search_recurse(AVLTreeNode<T>* pnode, T key) const;
    AVLTreeNode<T>* search_iterator(AVLTreeNode<T>* pnode, T key) const;
 
    AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* pnode);        //单旋:左旋操作
    AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* pnode);        //单旋:右旋操作
    AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* pnode);    //双旋:先左旋后右旋操作
    AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* pnode);    //双旋:先右旋后左旋操作
};

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
AVLTree<T>::~AVLTree() {
    destroy(root);
}

template <typename T>
T AVLTree<T>::get_root_value() const {
    return root->key;
}

template <typename T>
int AVLTree<T>::max(int a, int b) {
    return a > b ? a : b;
}

template <typename T>
int AVLTree<T>::height(AVLTreeNode<T>* root) {
    if(root == nullptr) return 0;
    return root->height;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>*pnode) const {
    if(pnode == nullptr) return nullptr;
    while(pnode->lchild != nullptr)
        pnode = pnode->lchild;
    return pnode;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>*pnode) const {
    if(pnode == nullptr) return nullptr;
    while(pnode->rchild != nullptr)
        pnode = pnode->rchild;
    return pnode;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* pnode) {
    AVLTreeNode<T> *prchild = pnode->rchild;
    pnode->rchild = prchild->lchild;
    prchild->lchild = pnode;

    // 更新高度
    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
    prchild->height = max(height(prchild->lchild), height(prchild->rchild)) + 1;

    return prchild;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>* pnode) {
    AVLTreeNode<T> *plchild = pnode->lchild;
    pnode->lchild = plchild->rchild;
    plchild->rchild = pnode;

    // 更新高度
    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
    plchild->height = max(height(plchild->lchild), height(plchild->rchild)) + 1;

    return plchild;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* pnode) {
    pnode->lchild = leftRotation(pnode->lchild);
    return rightRotation(pnode);
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* pnode) {
    pnode->rchild = rightRotation(pnode->rchild);
    return leftRotation(pnode);
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* pnode, T key) {
    if(pnode == nullptr) {
        pnode = new AVLTreeNode<T>(key, nullptr, nullptr);
    }
    else if(key >= pnode->key) {   // 插入到右子树
        pnode->rchild = insert(pnode->rchild, key);
        // 如果失衡，调整
        if(height(pnode->rchild) - height(pnode->lchild) == 2) {
            // 需要左旋
            if(key >= pnode->rchild->key)
                pnode = leftRotation(pnode);
            else if(key < pnode->rchild->key)   // 右旋左旋
                pnode = rightLeftRotation(pnode);
        }
    }
    else if(key < pnode->key) {     // 插入到左子树
        pnode->lchild = insert(pnode->lchild, key);
        if(height(pnode->lchild) - height(pnode->rchild) == 2) {
            // 右旋
            if(key < pnode->lchild->key)
                pnode = rightRotation(pnode);
            else if(key >= pnode->lchild->key)
                pnode = leftRightRotation(pnode);
        }
    }
    // 更新高度
    pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
    return pnode;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* pnode, T key) {
    if(pnode != nullptr) {
        if(pnode->key == key) {
            // 左右子树都不为空
            if(pnode->lchild != nullptr && pnode->rchild != nullptr) {
                // 选择最大高度的子树来替换根节点，减少调整次数
                if(height(pnode->lchild) > height(pnode->rchild)) {
                    AVLTreeNode<T> *t = maximum(pnode->lchild);
                    pnode->key = t->key;
                    pnode->lchild = remove(pnode->lchild, t->key);
                }else {
                    AVLTreeNode<T> *t = minimum(pnode->rchild);
                    pnode->key = t->key;
                    pnode->rchild = remove(pnode->rchild, t->key);
                }
            }
            else {
                AVLTreeNode<T> *t = pnode;
                if(pnode->lchild != nullptr)
                    pnode = pnode->lchild;
                else if(pnode->rchild != nullptr)
                    pnode = pnode->rchild;
                delete t;
                return nullptr; // 如果直接删除根节点，根节点会被置换到叶子，所以这里需要返回null，不然会返回删除节点的内容
            }
        }
        else if(key >= pnode->key) {
            pnode->rchild = remove(pnode->rchild, key);
            if(height(pnode->lchild) - height(pnode->rchild) == 2) {
                if(height(pnode->lchild->lchild) > height(pnode->lchild->rchild))
                    pnode = rightRotation(pnode);
                else
                    pnode = leftRightRotation(pnode);
            }
        }
        else if(key < pnode->key) {
            pnode->lchild = remove(pnode->lchild, key);
            if(height(pnode->rchild) - height(pnode->lchild) == 2) {
                if(height(pnode->rchild->rchild) > height(pnode->rchild->lchild))
                    pnode = leftRotation(pnode);
                else
                    pnode = rightLeftRotation(pnode);
            }
        }
        return pnode;
    }
    return nullptr;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_recurse(AVLTreeNode<T>* pnode, T key) const {
    if(pnode == nullptr) return nullptr;
    if(key > pnode->key)
        return search_recurse(pnode->rchild, key);
    else if(key < pnode->key)
        return search_recurse(pnode->lchild, key);
    return pnode;
}

template <typename T>
AVLTreeNode<T>* AVLTree<T>::search_iterator(AVLTreeNode<T>* pnode, T key) const {
    while(pnode != nullptr) {
        if(key > pnode->key)
            pnode = pnode->rchild;
        else if(key < pnode->key)
            pnode = pnode->lchild;
        else
            return pnode;
    }
    return nullptr;
}

template <typename T>
void AVLTree<T>::destroy(AVLTreeNode<T>* pnode) {
    if(pnode != nullptr) {
        destroy(pnode->lchild);
        destroy(pnode->rchild);
        delete pnode;
        pnode = nullptr;
    }
}

template <typename T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* pnode) const {
    if(pnode != nullptr) {
        cout << pnode->key << endl;
        preOrder(pnode->lchild);
        preOrder(pnode->rchild);
    }
}

template <typename T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* pnode) const {
    if(pnode != nullptr) {
        inOrder(pnode->lchild);
        cout << pnode->key << endl;
        inOrder(pnode->rchild);
    }
}

template <typename T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* pnode) const {
    if(pnode != nullptr) {
        postOrder(pnode->lchild);
        postOrder(pnode->rchild);
        cout << pnode->key << endl;
    }
}

template <typename T>
void AVLTree<T>::preOrder() {
    preOrder(root);
}

template <typename T>
void AVLTree<T>::inOrder() {
    inOrder(root);
}

template <typename T>
void AVLTree<T>::postOrder() {
    postOrder(root);
}

template <typename T>
void AVLTree<T>::destroy() {
    destroy(root);
}

template <typename T>
void AVLTree<T>::insert(T key) {
    root = insert(root, key);
}

template <typename T>
void AVLTree<T>::remove(T key) {
    root = remove(root, key);
}

template <typename T>
AVLTreeNode<T> *AVLTree<T>::search_recurse(T key) {
    return search_recurse(root, key);
}

template <typename T>
AVLTreeNode<T> *AVLTree<T>::search_iterator(T key) {
    return search_iterator(root, key);
}


template <typename T>
int AVLTree<T>::height() {
    return height(root);
}

template <typename T>
T AVLTree<T>::minimum() {
    AVLTreeNode<T> *t = minimum(root);
    if(t != nullptr) 
        return t->key;
}

template <typename T>
T AVLTree<T>::maximum() {
    AVLTreeNode<T> *t = maximum(root);
    if(t != nullptr) 
        return t->key;
}

#endif