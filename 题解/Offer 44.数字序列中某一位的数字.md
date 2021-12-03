# Offer 44.数字序列中某一位的数字

```
数字以0123456789101112131415…的格式序列化到一个字符序列中。在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。

请写一个函数，求任意第n位对应的数字。

 

示例 1：

输入：n = 3
输出：3

示例 2：

输入：n = 11
输出：0

 

限制：

    0 <= n < 2^31
```

### 题解

![Picture2.png](https://pic.leetcode-cn.com/16836ca609f8b4d9af776b35eab4a4c4a86d76f4628a1bc931e56d197617bbb4-Picture2.png)

![Picture1.png](https://pic.leetcode-cn.com/2cd7d8a6a881b697a43f153d6c10e0e991817d78f92b9201b6ab71e44cb619de-Picture1.png)

![Picture3.png](https://pic.leetcode-cn.com/1f2cefd22a9825eb4a52d606a4aee2f93dd659d1b332d3b6a6ed68e5289e8d01-Picture3.png)

![Picture4.png](https://pic.leetcode-cn.com/09af6bd37d9c79d9b904bedef01f0464aee1cd15e18d8a2ea86b70b312a830c3-Picture4.png)

### 代码

```java
class Solution {
    public int findNthDigit(int n) {
        int digit = 1;
        long start = 1;
        long count = 9;
        while(n > count){
            n -= count;
            digit ++;
            start *= 10;
            count = start*digit*9;
        }
        long num = start + (n-1)/digit;
        return Long.toString(num).charAt((n-1)%digit)-'0';
    }
}
```

