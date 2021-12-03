# Offer 10-1.斐波那契数列

```
写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项。斐波那契数列的定义如下：

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.

斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

 

示例 1：

输入：n = 2
输出：1

示例 2：

输入：n = 5
输出：5

 

提示：

    0 <= n <= 100
```

### 解法

##### 递归：

​	直接采用递归计算

##### 带备忘录的递归：

​	因为递归会重复计算很多次，例如求fib(n)会计算fib(n-1)和fib(n-2)，计算fib(n+1)会计算fib(n)+fib(n-1)，重复计算多次。导致时间超时，采用备忘录记录计算过的值

##### 动态规划：

​	用dp[n]数组记录第i个斐波那契数；

​	转移方程为dp(i) = dp(i - 1) + dp(i - 2);

​	初始为dp[0] = 0; dp[1] = 1;

​	返回dp[n];

​	**可见斐波那契数只与前两个相关，所以可以用三个变量,a,b,sum来记录前两个值和当前斐波那契数**

### 代码

##### 递归(超时)

```java
class Solution {
    public int fib(int n) {
        int res = fib0(n);
        return res%1000000007;
    }

    public int fib0(int n){
        if(n == 0)
            return 0;
        if(n == 1)
            return 1;
        return fib(n-1)+fib(n-2);
    }
}
```

##### 备忘率递归

```java
class Solution {
    int[] dp = new int[100+1];

    public int fib(int n) {
        if(n == 0)
            return 0;
        if(n == 1)
            return 1;
        if(dp[n] != 0){
            return dp[n];
        }else{
            dp[n] = (fib(n-1) + fib(n-2))%1000000007;
            return dp[n];
        }
    }
}
```

##### 动态规划

```java
class Solution {
    public int fib(int n) {
        int sum,a=0,b=1;
        for(int i=0;i<n;i++){
            sum = (a+b)%1000000007;
            a = b;
            b = sum;
        }
        //返回a是因为，求第n个数的斐波那契循环多算了一次，返回前一个数
        return a;
    }
}
```

