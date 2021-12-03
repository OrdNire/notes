# Offer 04.二位数组中的查找

```
在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

 

示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]

给定 target = 5，返回 true。

给定 target = 20，返回 false。
```

### 思路

##### 一

直接二层循环找到返回

##### 二

在第二层循环利用二分查找

### 代码

##### 一

```java
public boolean findNumberIn2DArray(int[][] matrix, int target) {
    if(matrix==null || matrix.length==0){
        return false;
    }
    int n = matrix.length,m = matrix[0].length;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j]==target){
                return true;
            }
        }
    }
    return false;
}
```

##### 二

```java
public boolean findNumberIn2DArray(int[][] matrix, int target) {
    if(matrix==null || matrix.length==0){
        return false;
    }
    int n = matrix.length,m = matrix[0].length;
    int f=0,l=m-1;
    int mid;
    for(int i=0;i<n;i++){
        while(f<=l) {
            mid=(f+l)/2;
            if(matrix[i][mid]==target) {
                return true;
            }else if(matrix[i][mid]<target) {
                f=mid+1;
            }else if(matrix[i][mid]>target) {
                l=mid-1;
            }
        }
        f=0;
        l=m-1;
    }
    return false;
}
```

