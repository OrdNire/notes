# Offer 59-2.队列的最大值

```
请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1

示例 1：

输入: 
["MaxQueue","push_back","push_back","max_value","pop_front","max_value"]
[[],[1],[2],[],[],[]]
输出: [null,null,null,2,1,2]

示例 2：

输入: 
["MaxQueue","pop_front","max_value"]
[[],[],[]]
输出: [null,-1,-1]

 

限制：

    1 <= push_back,pop_front,max_value的总操作数 <= 10000
    1 <= value <= 10^5
```

### 题解

##### 使用辅助队列

维护一个递减的辅助双端队列

当队列中有新元素加入时，将辅助队列中所以比其小的值删除，再将此值插入到辅助队列，可以保证辅助队列为一个单调递减的数列，原队列中最大值就为辅助队列中首部

当对队列进行出队时，在原队列中，在最大值前面的数出队，不会影响辅助队列的最值结果，当原队列出队的值等于辅助队列首部最大值，则两队列首部一并出队。

获取最大值即辅助队列首部

### 代码

使用辅助队列

```java
class MaxQueue {
    Queue<Integer> que;
    Deque<Integer> help = new LinkedList<>();

    public MaxQueue() {
        this.que = new LinkedList<>();
    }
    
    public int max_value() {
        if(!que.isEmpty()){
            return help.peekFirst();
        }
        return -1;
    }
    
    public void push_back(int value) {
        while(!help.isEmpty() && help.peekLast() < value){
            help.removeLast();
        }
        que.offer(value);
        help.addLast(value);
    }
    
    public int pop_front() {
        if(que.isEmpty()){
            return -1;
        }
        int ans = que.poll();
        if(ans == help.peek()){
            help.removeFirst();
        }
        return ans;
    }
}

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue obj = new MaxQueue();
 * int param_1 = obj.max_value();
 * obj.push_back(value);
 * int param_3 = obj.pop_front();
 */
```

