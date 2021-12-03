# Offer 47.礼物的最大价值

```
在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

 

示例 1:

输入: 
[
  [1,3,1],
  [1,5,1],
  [4,2,1]
]
输出: 12
解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物

 

提示：

    0 < grid.length <= 200
    0 < grid[0].length <= 200
```

### 题解

##### DFS

深度优先搜索找拿到价值最多的礼物，但是时间复杂度O(n方)，超出时间限制

##### 动态规划

根据题目，价值只能来自于矩阵当前位置的上和左，所以可得状态转移方程

1. 当i==0时，只能来自于左边 dp(i)(j) = dp(i)(j-1)
2. 当j==0时，只能来自于上边 dp(i)(j) = dp(i-1)(j)
3. 当i和j都不为0时，dp(i)(j) = MAX{dp(i)(j-1),dp(i-1)(j)}

返回的值为由矩阵右下角的值

### 代码

##### DFS

```java
class Solution {
    private int max = -1;
    private int[][] book = new int[200][200];
    private int[][] next = new int[][]{{0,1},{1,0}};

    public int maxValue(int[][] grid) {
        dfs(0,0,grid.length,grid[0].length,0,grid);
        return max;
    }

    private void dfs(int x,int y,int n,int m,int sum,int[][] grid){
        if(x < 0 || x >= n || y < 0 || y >= m) return;

        sum += grid[x][y];
        if(sum > max){
            max = sum;
        }    
        
        int tx,ty;
        for(int i=0;i<2;i++){
            tx = x + next[i][0];
            ty = y + next[i][1];
            if(book[tx][ty] == 0){
                book[tx][ty] = 1;
                dfs(tx,ty,n,m,sum,grid);
                book[tx][ty] = 0;
            }
        }
    }
}
```

##### 动态规划

```java
class Solution {
    public int maxValue(int[][] grid) {
        int n = grid.length,m = grid[0].length;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0 && j==0) continue;
                else if(i==0) grid[i][j] = grid[i][j-1] + grid[i][j]; 
                else if(j==0) grid[i][j] = grid[i-1][j] + grid[i][j];
                else grid[i][j] += Math.max(grid[i][j-1],grid[i-1][j]);
            }
        }
        return grid[n-1][m-1];
    }
}
```

