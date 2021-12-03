# Offer 06.从尾到头打印链表

```
输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。

 

示例 1：

输入：head = [1,3,2]
输出：[2,3,1]
```

### 解法

##### 解法一 

​	遍历链表，将值存入数组中，反转数组

##### 解法二（辅助栈）

​	通过栈来存入链表的值，再把栈中的值弹出

##### 解法三（递归）

​	通过递归的回溯，将值存入数组中

### 代码

##### 解法一

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> arr;
        while(head!=NULL){
            arr.push_back(head->val);
            head = head->next;
        }
        reverse(arr.begin(),arr.end());
        return arr;
    }
};
```

##### 解法二

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    public int[] reversePrint(ListNode head) {
        Stack<ListNode> stack = new Stack<ListNode>();
        ListNode temp = head;
        while (temp != null) {
            stack.push(temp);
            temp = temp.next;
        }
        int size = stack.size();
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = stack.pop().val;
        }
        return arr;
    }
}
```

##### 解法三

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
    ArrayList<Integer> temp = new ArrayList<>();

    public int[] reversePrint(ListNode head) {
        reAdd(head);
        int[] arr = new int[temp.size()];
        for(int i=0;i<arr.length;i++){
            arr[i] = temp.get(i);
        }
        return arr;
    }

    private void reAdd(ListNode p){
        if(p == null){
            return;
        }
        reAdd(p.next);
        temp.add(p.val);
    }
}
```

