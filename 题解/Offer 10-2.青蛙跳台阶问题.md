# Offer 10-2.青蛙跳台阶问题

```
一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

示例 1：

输入：n = 2
输出：2

示例 2：

输入：n = 7
输出：21

提示：

    0 <= n <= 100

```

### 解法

##### 递归(超时)

​	直接递归，将跳上每一阶的可能性相加，但大量重复计算导致时间超时

##### 备忘录递归

​	带一个备忘录记录每一阶的可能性，进行递归

##### 动态规划

​	根据转移方程 dp[n] = dp[n-1]+dp[n-2]

### 代码

##### 递归

```java
class Solution {
    public int numWays(int n) {
        if(n == 0){
            return 1;
        }
        if(n == 1){
            return 1;
        }
        if(n == 2){
            return 2;
        }
        return numWays(n-1)+numWays(n-2);
    }
}
```

##### 备忘录递归

```java
class Solution {
    private int[] mem = new int[101];

    public int numWays(int n) {
        if(mem[n]!=0){
            return mem[n];
        }
        if(n == 0){
            mem[n] = 1;
        }else if(n == 1){
            mem[n] = 1;
        }else if(n == 2){
            mem[n] = 2;
        }else{
            mem[n] = (numWays(n-1)%1000000007+numWays(n-2)%1000000007)%1000000007;
        }
        return mem[n];
    }
}
```

##### 动态规划

```java
class Solution {
    public int numWays(int n) {
       int a=1,b=1,sum;
       for(int i=0;i<n;i++){
           sum = (a+b)%1000000007;
           a = b;
           b = sum;
       }
       return a;
    }
}
```

