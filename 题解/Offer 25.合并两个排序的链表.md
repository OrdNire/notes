# Offer 25.合并两个排序的链表

```
输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。

示例1：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4

限制：

0 <= 链表长度 <= 1000
```

### 思路

##### 解法一：

​	连接两个链表后排序

##### 递归解法：

​	比较L1和L2当前所指节点的值，将小的连接大的。

##### 迭代：

​	建一个链表，L1和L2的节点比较大小，小的就加进新链表

### 代码

##### 解法一：

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */

public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
    //判断两链表是否同时为空
    if(l1==null && l2==null) {
        return null;
    }
    ListNode p1=l1;
    ListNode p2=l2;
    //连接两链表
    if(l1!=null) {
        while(p1.next!=null) {
            p1=p1.next;
        }
        p1.next=l2;
        p1=l1;
    }else {
        p1=l2;
    }
    ListNode head=p1;
    ListNode index;
    int temp;
    while(p1.next!=null) {
        index=p1;
        p2 = p1;
        //不能为p2.next!=null,否则最后一个节点无法比较
        while(p2!=null) {
            if(p2.val<=index.val) {
                index=p2;
            }
            p2=p2.next;
        }
        temp = index.val;
        index.val = p1.val;
        p1.val = temp;
        p1=p1.next;
    }
    return head;
}
```

##### 递归：

```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */

public class Solution25 {
	public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
		if(l1 == null) {
			return l2;
		}
		if(l2 == null) {
			return l1;
		}
		if(l1.val > l2.val) {
			l2.next = mergeTwoLists(l1,l2.next);
			return l2;
		}else {
			l1.next = mergeTwoLists(l1.next,l2);
			return l1;
		}
	}
}
```

##### 迭代：

```java
public class Solution25 {
	public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
		if(l1 == null) {
			return l2;
		}
		if(l2 == null) {
			return l1;
		}
		ListNode head = new ListNode(0);
		ListNode cur = head;
		while(l1 != null && l2 != null) {
			if(l1.val>=l2.val) {
				cur.next = l2;
				l2 = l2.next;
				cur = cur.next;
			}else {
				cur.next = l1;
				l1 = l1.next;
				cur = cur.next;
			}
		}
		if(l1 == null) {
			cur.next = l2;
		}else {
			cur.next = l1;
		}
		return head.next;
	}
}
```

