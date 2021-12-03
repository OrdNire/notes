# Offer 35.复杂链表的复制

```
请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

 

示例 1：

输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

示例 2：

输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]

示例 3：

输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]]

示例 4：

输入：head = []
输出：[]
解释：给定的链表为空（空指针），因此返回 null。

 

提示：

    -10000 <= Node.val <= 10000
    Node.random 为空（null）或指向链表中的节点。
    节点数目不超过 1000 。
```

示例1：

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e1.png)

示例2：

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e2.png)

示例3：

**![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/09/e3.png)**

### 解法

##### 哈希表

哈希表的key存放原来链表的节点，value存放复制出来的节点。这样就形成了可以根据原来链表的节点直接定位到复制出来链表的节点。

然后将原链表节点的next对应的复制节点复制给此节点对应的复制节点的next。实现复制链表的链接。

同理，random同样可以用此方法复制

### 代码

##### 哈希表

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        map<Node*,Node*> mp;
        Node* t = head;
        while(t!=NULL){
            mp[t] = new Node(t->val);
            t = t->next;
        }
        t = head;
        while(t!=NULL){
            if(t->next){
                mp[t]->next = mp[t->next];
            }
            if(t->random){
                mp[t]->random = mp[t->random];
            }
            t = t->next;
        }
        return mp[head];
    }
};
```

