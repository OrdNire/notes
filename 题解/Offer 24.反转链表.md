# Offer 24.反转链表

```java
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。

 

示例:

输入: 1->2->3->4->5->NULL
输出: 5->4->3->2->1->NULL

 

限制：

0 <= 节点个数 <= 5000
```

### 解法

##### 	三指针反转链表

​	借助三个指针来反转链表

##### 	双指针

​	定义两个指针，第一个初始为null，第二个初始指向头，再定义一个临时指针用于帮助双指针移动

![img](https://pic.leetcode-cn.com/9ce26a709147ad9ce6152d604efc1cc19a33dc5d467ed2aae5bc68463fdd2888.gif)

##### 	递归

```
使用递归函数，一直递归到链表的最后一个结点，该结点就是反转后的头结点，记作 t .
此后，每次函数在返回的过程中，让当前结点的下一个结点的 next 指针指向当前节点。
同时让当前结点的 next 指针指向 null ，从而实现从链表尾部开始的局部反转
当递归函数全部出栈后，链表反转完成。
```

### 代码

##### 	三指针反转链表

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
    public ListNode reverseList(ListNode head) {
        if(head == null || head.next == null){
            return head;
        }
        ListNode p = head;
        ListNode q = p.next;
        ListNode r = q.next;
        q.next = p;
        if(r==null){
            p.next = null;
            head = q;
            return head;
        }
        while(r.next!=null){
            p = q;
            q = r;
            r = r.next;
            q.next = p;
        }
        r.next = q;
        head.next = null;
        head = r;
        return head;
    }
}
```

##### 	双指针

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
    public ListNode reverseList(ListNode head) {
        ListNode p = null,q = head;
        ListNode t;
        while(q!=null){
            t= q.next;
            q.next = p;
            p = q;
            q = t;
        }
        return p;
    }
}
```

##### 递归

```java
class Solution {
    public ListNode reverseList(ListNode head) {
        if(head == null || head.next == null){
            return head;
        }
        ListNode t = reverseList(head.next);
        head.next.next = head;
        head.next = null;
        return t;
    }
}
```

