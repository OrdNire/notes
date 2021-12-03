# Offer 49.丑数

```
我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

 

示例:

输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。

说明:  

    1 是丑数。
    n 不超过1690。
```

### 题解

##### 动态规划

![image-20200731143107754](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200731143107754.png)



![image-20200731143133718](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200731143133718.png)

![image-20200731143154049](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200731143154049.png)

![image-20200731143203529](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200731143203529.png)

**个人理解:**丑数一定是2/3/5乘以上一个丑数，那么这个丑数一定是上一个丑数乘以2/3/5得来的，通过三个指针来维护乘2/3/5三个不同的情况，如果当前丑数是某一个指针乘以对应的数的来的，那么该指针向右移动一位表示已经用过该数，同时另外两个指针如果乘以对应的数和该数一样，则也要右移一位表示来维护该数已经被对应的使用过

### 代码

```java
class Solution {
    public int nthUglyNumber(int n) {
        int[] dp = new int[n];
        dp[0] = 1;
        int p2 = 0,p3 = 0,p5 = 0;
        for(int i=1;i<n;i++){
            int a = dp[p2]*2,b = dp[p3]*3,c = dp[p5]*5;
            dp[i] = Math.min(Math.min(a,b),c);
            if(a == dp[i]) p2++;
            if(b == dp[i]) p3++;
            if(c == dp[i]) p5++;
        }
        return dp[n-1];
    }
}
```

