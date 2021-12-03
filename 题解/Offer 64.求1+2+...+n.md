# Offer 64.求1+2+...+n

```
求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

 

示例 1：

输入: n = 3
输出: 6

示例 2：

输入: n = 9
输出: 45

 

限制：

    1 <= n <= 10000
```

### 题解

##### 递归

由题，可用工具只有逻辑运算和加减，以及位运算符

根据逻辑运算符的短路性质，以&&为例，若前为false则后面不会执行，以此可以用来作为递归的结束条件

##### 快速乘

![image-20200728155431592](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200728155431592.png)

```c++
int quickMulti(int A, int B) {
    int ans = 0;
    for ( ; B; B >>= 1) {
        if (B & 1) {
            ans += A;
        }
        A <<= 1;
    }
    return ans;
}
```

![image-20200728155500015](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200728155500015.png)



![image-20200728160201576](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200728160201576.png)

### 代码

##### 递归

```
class Solution {
public:
    int sumNums(int n) {
        n && (n += sumNums(n-1));
        return n;
    }
};
```

##### 快速乘法

```c++
class Solution {
public:
    int sumNums(int n) {
        int ans = 0, A = n, B = n + 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        (B & 1) && (ans += A);
        A <<= 1;
        B >>= 1;

        return ans >> 1;
    }
};
```

