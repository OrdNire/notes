# Offer 12.矩阵中的路径

```
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。

[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]

但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。

 

示例 1：

输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true

示例 2：

输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false

提示：

    1 <= board.length <= 200
    1 <= board[i].length <= 200
```

### 

### 解法

##### 深度优先搜索+剪枝

**深度优先搜索(DFS)**：暴力法历遍矩阵中的每个字符串可能性。DFS通过递归，先朝着一个方向搜到底，再回溯到上一个节点，沿着另一个方向进行搜索，以此类推

**剪枝**：在搜索中，遇到这条路不可能和目标字符串匹配的情况（矩阵元素和目标字符不同，元素已经被访问），则立刻返回，成为可行性剪枝

**算法步骤**：

递归参数：矩阵(board),行(i)和列(j),当前目标字符(word)的索引(k);

终止条件：

1. 返回false：索引越界或当前元素与目标不符合或元素已经访问
2. 返回true：word已经全部匹配,k=len(word)-1;

递推：

1. 标记当前矩阵元素：蒋board(i)(j)暂存与变量temp，并修改字符为'/',代表此元素已经访问
2. 搜索下一个元素：从元素上，下，左，右四个方向开始下层递归，使用||连接(表示只需要一条可行路径),并记录结果至res
3. **还原当前矩阵元素**：蒋temp的值还原至board(i)(j)，因为题目只需要一条路径不能交叉，而如果不返回，会导致路径无法走全。

回溯：

返回res，代表是否搜索到当前字符串

### 代码

```java
class Solution {
    public boolean exist(char[][] board, String word) {
        char[] words = word.toCharArray();
        for(int i=0;i<board.length;i++){
            for(int j=0;j<board[i].length;j++){
                if(dfs(board,words,i,j,0)) return true;
            }
        }
        return false;
    }

    private boolean dfs(char[][] board,char[] words,int i,int j,int k){
        if(i<0 || i>=board.length || j<0 || j>=board[0].length || board[i][j]!= words[k]){
            return false;
        }
        if(k == words.length-1){
            return true;
        }
        char temp = board[i][j];
        board[i][j] = '/';
        boolean res = dfs(board,words,i+1,j,k+1) || dfs(board,words,i-1,j,k+1) || 
            		  dfs(board,words,i,j+1,k+1) || dfs(board,words,i,j-1,k+1);
        board[i][j] = temp;
        return res;
    }
}
```

