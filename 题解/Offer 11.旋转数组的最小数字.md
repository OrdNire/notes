# Offer 11.旋转数组的最小数字

```
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  

示例 1：

输入：[3,4,5,1,2]
输出：1

示例 2：

输入：[2,2,2,0,1]
输出：0
```

### 思路

##### 解法一：

​	直接历遍数组找到后一个元素小于前一个元素，返回

##### 二分法

​	二分法是对排序数组进行查找，而旋转数组是部分排序，可用二分法来去掉部分排序好的，缩小范围

​	![Picture1.png](https://pic.leetcode-cn.com/5884538fb9541a31a807d59c81226ded3dcd61df66efcdeb000165036ea68bb9-Picture1.png)



### 代码

##### 解法一：

```java
public int minArray(int[] numbers) {
    for(int i=0;i<numbers.length-1;i++){
        if(numbers[i+1]<numbers[i]){
            return numbers[i+1];
        }
    }
    return numbers[0];
}
```

##### 二分法

```java
public int minArray(int[] numbers) {
    int f=0,l=numbers.length-1;
    int mid;
    while(f<l){
        mid = (f+l)/2;
        if(numbers[mid]<numbers[l]){
            l=mid;
        }else if(numbers[mid]>numbers[l]){
            f=mid+1;
        }else{
            l--;
        }
    }
    return numbers[f];
}
```

