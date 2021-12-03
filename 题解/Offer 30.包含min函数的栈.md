# Offer 30.包含min函数的栈

```java
定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，调用 min、push 及 pop 的时间复杂度都是 O(1)。

 

示例:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.min();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.min();   --> 返回 -2.

 

提示：

    各函数的调用总次数不超过 20000 次
```

### 解法

##### 辅助栈

普通栈中获取最小值min()函数的时间复杂度为O(n),需要历遍整个栈

可以引入辅助栈，将每次push进来的值做比较，如果当前栈为空，或者值比当前辅助栈栈顶的值小或者等于，则入辅助栈

同时pop()时，如果原栈的栈顶和辅助栈的栈顶值相同，则将两个栈同时pop，保证辅助栈的栈顶都是原栈中最小的值

### 代码

```java
class MinStack {
    Stack<Integer> stack;
    Stack<Integer> helpStack;

    /** initialize your data structure here. */
    public MinStack() {
        stack = new Stack<>();
        helpStack = new Stack<>();
    }
    
    public void push(int x) {
        stack.push(x);
        if(helpStack.isEmpty() || x<=helpStack.peek()){
            helpStack.push(x);
        }
    }
    
    public void pop() {
        if(helpStack.peek().equals(stack.peek())){
            stack.pop();
            helpStack.pop();
        }else{
            stack.pop();
        }
    }
    
    public int top() {
        return stack.peek();
    }
    
    public int min() {
        return helpStack.peek();
    }
}

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.min();
 */
```

