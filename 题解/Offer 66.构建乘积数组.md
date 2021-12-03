# Offer 66.构建乘积数组

```
给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B 中的元素 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

 

示例:

输入: [1,2,3,4,5]
输出: [120,60,40,30,24]

 

提示：

    所有元素乘积之和不会溢出 32 位整数
    a.length <= 100000
```

### 解法

##### 双层暴力循环

容易想到，可以直接利用双层循环将结果中每一个下标对应的乘积算出来

时间超时

时间复杂度O(n方)

##### 利用矩阵

![Picture1.png](https://pic.leetcode-cn.com/6056c7a5009cb7a4674aab28505e598c502a7f7c60c45b9f19a8a64f31304745-Picture1.png)

![image-20200722133931006](C:\Users\25454\AppData\Roaming\Typora\typora-user-images\image-20200722133931006.png)

### 代码

##### 暴力

```c++
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        vector<int> res;
        int sum = 1;
        for(int i=0;i<a.size();i++){
            sum = 1;
            for(int j=0;j<a.size();j++){
                if(i != j){
                    sum *= a[j];
                }
            }
            res.push_back(sum);
        }
        return res;
    }
};
```

##### 利用矩阵

```java
class Solution {
    public int[] constructArr(int[] a) {
        if(a.length == 0) return new int[0];
        int[] b = new int[a.length];
        b[0] = 1;
        int temp = 1;
        for(int i=1;i<a.length;i++){
            b[i] = b[i-1] * a[i-1];
        }
        for(int i=a.length-2;i>=0;i--){
            temp *= a[i+1];
            b[i] *= temp;
        }
        return b;
    }
}
```

