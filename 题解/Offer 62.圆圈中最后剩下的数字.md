# Offer 62.圆圈中最后剩下的数字

```
0,1,,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。

例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

 

示例 1：

输入: n = 5, m = 3
输出: 3

示例 2：

输入: n = 10, m = 17
输出: 2

 

限制：

    1 <= n <= 10^5
    1 <= m <= 10^6
```

### 解法

##### 利用队列

每一次删除的位置是在当前位置的基础上，移动m%剩下数字个数 个位置

想到可以利用队列，维护每一次的起始位置都为队列的头部，将每一次需要删除数字的前面的数放入该队列尾部，再删除队列头部，维护一个始终以头部为起始位置的队列

但用时慢

##### 数学公式

该题是经典的约瑟夫环的问题

![image-20200722124951420](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200722124951420.png)

### 代码

##### 利用队列

```
class Solution {
    public int lastRemaining(int n, int m) {
        Deque<Integer> que = new LinkedList<>();
        for(int i=0;i<n;i++){
        	que.addLast(i);
        }
        while(que.size()>1) {
        	int index = m%n;
        	if(index == 1) {
        		que.removeFirst();
        	}else if(index == 0) {
        		for(int i=1;i<que.size();i++) {
        			que.addLast(que.removeFirst());
        		}
        		que.removeFirst();
        	}else {
        		for(int i=1;i<index;i++) {
        			que.addLast(que.removeFirst());
        		}
        			que.removeFirst();
        	}
        	n--;
        }
		return que.peekFirst();
    }
}
```

##### 数学公式

```
class Solution {
public:
    int lastRemaining(int n, int m) {
        return f(n,m);
    }
private:
    int f(int n,int m){
        if(n == 1){
            return 0;
        }
        int x = f(n-1,m);
        return (m+x)%n;
    }
};
```

