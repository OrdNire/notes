# Offer 29.顺时针打印矩阵

```
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

 

示例 1：

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]

示例 2：

输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]

 

限制：

    0 <= matrix.length <= 100
    0 <= matrix[i].length <= 100
```

### 解法

一步步移动，并以一个矩阵来记录是否已经走过，遇到边界或者遇到已经走过的点则转移方向

### 代码

```java
class Solution {
    public int[] spiralOrder(int[][] matrix) {
        int direct = 1;
        int count = 0;
        for(int i=0;i<matrix.length;i++){
            for(int j=0;j<matrix[i].length;j++){
                count++;
            }
        }
        int now = 0;
        int i = 0;
        int j = 0;
        int[] res = new int[count];
        int min = Integer.MIN_VALUE;
        while(now<count){
            if(now == count-1){
                res[now] = matrix[i][j];
                break;
            }
            if(direct == 1){
                if(j+1<matrix[i].length && matrix[i][j+1] != min){
                    res[now] = matrix[i][j];
                    matrix[i][j] = min;
                    now++;
                    j++;
                }else{
                    direct = 2;
                    continue;
                }
            }
            if(direct == 2){
                if(i+1<matrix.length && matrix[i+1][j] != min){
                    res[now] = matrix[i][j];
                    matrix[i][j] = min;
                    now++;
                    i++;            
                }else{
                    direct = 3;
                    continue;
                }
            }
            if(direct == 3){
                if(j-1>=0 && matrix[i][j-1] != min){
                    res[now] = matrix[i][j];
                    matrix[i][j] = min;
                    now++;
                    j--;
                }else{
                    direct = 4;
                    continue;
                }
            }
            if(direct == 4){
                if(i-1>=0 && matrix[i-1][j] != min){
                    res[now] = matrix[i][j];
                    matrix[i][j] = min;
                    now++;
                    i--;
                }else{
                    direct = 1;
                    continue;
                }
            }
        }
        return res;
    }
}
```

