# Offer 40.最小的k个数

```
入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

 

示例 1：

输入：arr = [3,2,1], k = 2
输出：[1,2] 或者 [2,1]

示例 2：

输入：arr = [0,1,2,1], k = 1
输出：[0]

 

限制：

    0 <= k <= arr.length <= 10000
    0 <= arr[i] <= 10000
```

### 解法

##### 计数排序

历遍数组，将数组中的元素作为索引扔进大数组中，下标作为值，对应的值作为个数。

### 代码

```java
class Solution {
    public int[] getLeastNumbers(int[] arr, int k) {
        int[] book = new int[10001];
        for(int i=0;i<arr.length;i++){
            book[arr[i]]++;
        }
        int[] res = new int[k];
        int n = 0;
        for(int i=0;i<10001;i++){
            if(book[i]!=0 && n<k){
                for(int j=0;j<book[i];j++){
                    if(n<k){
                        res[n] = i;
                        n++;
                    }
                }
            }
        }
        return res;
    }
}
```

