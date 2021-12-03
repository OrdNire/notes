# AVL平衡树解析及c++模板实现



AVL树的名字来源于它的发明作者G.M. **A**delson-**V**elsky 和 E.M. **L**andis。AVL树是最先发明的自平衡二叉查找树（Self-Balancing Binary Search Tree,简称平衡二叉树）

一棵AVL树有如下必要条件：

1. 条件一：它必须是二叉查找树。
2. 条件二：每个节点的左子树和右子树的高度差至多为1。



![img](https://pic1.zhimg.com/80/v2-e090a8e3171c8db07e1cda720039e700_720w.jpg)

![img](https://pic3.zhimg.com/80/v2-7b3cbb7cf1d996c072516b7146144e52_720w.jpg)

![img](https://pic1.zhimg.com/80/v2-90521aa91ad8fd7677ed7899d586761c_720w.jpg)



### AVL树的相关概念

**平衡因子**：将二叉树上节点的左子树高度减去右子树高度的值即为该节点的平衡因子BF(Balance Factor)

例如上图 88节点的BF：1-0 = 1
				 30节点的BF：0-1 = -1

对于平衡二叉树，BF的取值在 [-1, 1] 之间，绝对值大于1则需要进行调整

**最小平衡树**：距离节点最近的，且BF绝对值大于1的子树



### AVL树的实现解析

**1.节点结构**

```c++
template <typename T>
struct AVLTreeNode {
    AVLTreeNode(T value, AVLTreeNode<T> *l, AVLTreeNode<T> *r)
        : key(value), lchild(l), rchild(r) {}

    T key;
    int height;
    AVLTreeNode<T> *lchild;
    AVLTreeNode<T> *rchild;
};
```

这里其实有两种得到BF的方法，一是将BF作为节点的属性存储下来，二是我们这里使用height存储节点的高度，那么某个节点的BF值就可以利用其左子树高度减去右子树高度得到



**2.AVL树的抽象数据结构(ADT)**

```c++
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
```



**3.求树的高度**

```c++
template <typename T>
int AVLTree<T>::height(AVLTreeNode<T>* root) {
    if(root == nullptr) return 0;
    return root->height;
}

template <typename T>
int AVLTree<T>::height() {
    return height(root);
}
```



**4.失衡调整**

​	这里的失衡调整都是对 **最小平衡树** 来进行调整

1. 左单旋转

![左单旋转](D:\个人资料\Notes\算法基础总结\img\左单旋转.png)

- 根的右子树的左子树赋值给根的右子树
- 然后将根调整到右子树的左子树
- 更新高度值

```c++
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
```



2. 右单旋转

   ![右单旋转](D:\个人资料\Notes\算法基础总结\img\右单旋转.png)

- 根的左子树的右子树赋值给根的左子树
- 然后将根调整的左子树的右子树
- 更新高度值

```c++
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
```



3.先左旋后右旋

![左旋再右旋](D:\个人资料\Notes\算法基础总结\img\左旋再右旋.png)

```c++
template <typename T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* pnode) {
    pnode->lchild = leftRotation(pnode->lchild);
    return rightRotation(pnode);
}
```



4. 先右旋再左旋

![先右旋再左旋](D:\个人资料\Notes\算法基础总结\img\先右旋再左旋.png)

```c++
template <typename T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* pnode) {
    pnode->rchild = rightRotation(pnode->rchild);
    return leftRotation(pnode);
}
```



**总结：四种失衡调整**

| 类型         | 使用情形                                           |
| :----------- | :------------------------------------------------- |
| 单左旋       | 在左子树插入左孩子节点，使得平衡因子绝对值由1增至2 |
| 单右旋       | 在右子树插入右孩子节点，使得平衡因子绝对值由1增至2 |
| 先左旋后右旋 | 在左子树插入右孩子节点，使得平衡因子绝对值由1增至2 |
| 先右旋后左旋 | 在右子树插入左孩子节点，使得平衡因子绝对值由1增至2 |



**5.插入新节点**

```c++
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
```



**6.删除节点**

删除节点也可能导致AVL树的失衡，实际上删除节点和插入节点是一种互逆的操作：

1. 删除**右子树的节点**导致AVL树失衡时，相当于在左子树插入节点导致AVL树失衡，即情况情况二或情况四。
2. 删除**左子树的节点**导致AVL树失衡时，相当于在右子树插入节点导致AVL树失衡，即情况情况一或情况三。

另外，AVL树也是一棵二叉排序树，因此在删除节点时也要维护二叉排序树的性质。

```c++
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
```

**后续的查找实现了递归和非递归版本，还要三种遍历方式，详细可以查看下方的原代码**



### 总结

总结来说，AVL树是对二叉搜索树的优化，二叉搜索树的最坏时间复杂度为 O(n)，而平衡树的最坏时间复杂度为 O(logn)，差距很大，速度有很大的提升，**所以对于需要搜素，又有频繁的插入和删除的，平衡树是一种优秀的数据结构**。



### 全部源码

```c++
/*
	AVLTree.h
	author: ordinaire
	date: 	2021-8-30
*/
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
```



**测试**

```c++
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
```

```
// 输入
7
88 70 61 96 120 90 65
// 输出
=====pre=====
88
65
61
70
96
90
120
=====in=====
61
65
70
88
90
96
120
=====post=====
61
70
65
90
120
96
88
=======
90
65
61
70
96
120
null
65
90
```