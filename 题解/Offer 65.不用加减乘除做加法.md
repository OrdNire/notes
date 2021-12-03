# Offer 65.不用加减乘除做加法

```
写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“*”、“/” 四则运算符号。

 

示例:

输入: a = 1, b = 1
输出: 2

 

提示：

    a, b 均可能是负数或 0
    结果不会溢出 32 位整数
```

### 题解

![image-20200722132104957](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200722132104957.png)

### 代码

```c++
class Solution {
public:
    int add(int a, int b) {
        //c++中会报错,-1<<1会未定义，则可人工消除最高位1
        int x = ~(1<<31);
        while(b!=0){
            int c = (a&b&x)<<1;
            a = a^b;
            b = c;
        }
        return a;
    }
};
```

