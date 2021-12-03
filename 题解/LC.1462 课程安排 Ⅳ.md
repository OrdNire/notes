# LC.1462 课程安排 Ⅳ

> 你总共需要上 n 门课，课程编号依次为 0 到 n-1 。
>
> 有的课会有直接的先修课程，比如如果想上课程 0 ，你必须先上课程 1 ，那么会以 [1,0] 数对的形式给出先修课程数对。
>
> 给你课程总数 n 和一个直接先修课程数对列表 prerequisite 和一个查询对列表 queries 。
>
> 对于每个查询对 queries[i] ，请判断 queries[i][0] 是否是 queries[i][1] 的先修课程。
>
> 请返回一个布尔值列表，列表中每个元素依次分别对应 queries 每个查询对的判断结果。
>
> 
>
> **注意：**如果课程 **a** 是课程 **b** 的先修课程且课程 **b** 是课程 **c** 的先修课程，那么课程 **a** 也是课程 **c** 的先修课程。



> 输入：n = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
> 输出：[false,true]
> 解释：课程 0 不是课程 1 的先修课程，但课程 1 是课程 0 的先修课程。



**题解**

**BFS/DFS**：

直接使用BFS或者DFS搜索两点是否连通，但是对于多个询问，事件复杂度较高



```c
const int N = 100010;
class Solution {
public:

    int h[N],e[N],ne[N],idx;

    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        
        memset(h,-1,sizeof h);

        for(auto item : prerequisites) add(item[0],item[1]);

        vector<bool> ans;
        for(auto item : queries) ans.push_back(bfs(item[0],item[1]));

        return ans;
    }

    void add(int a, int b){
        e[idx] = b,ne[idx] = h[a],h[a] = idx ++;
    }

    bool bfs(int start,int end){

        bool st[N];
        memset(st,false,sizeof st);
        queue<int> q;
        q.push(start);
        st[start] = true;

        while(q.size()){
            int t = q.front();
            q.pop();
            
            for(int i = h[t];i != -1;i = ne[i]){
                int j = e[i];
                if(j == end) return true;
                if(!st[j]){
                    st[j] = true;
                    q.push(j);
                }
            }
        }

        return false;
    }
};
```



**Floyd**

根据Floyd的原理，可以就该图的传递闭包，然后只需要在矩阵中判断两点是否连通即可，时间复杂度O(n^3)



```c
class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        bool g[n][n];
        memset(g, false, sizeof g);

        for(auto& i : prerequisites) g[i[0]][i[1]] = true;

        for(int k = 0;k < n;k ++)
            for(int i = 0;i < n;i ++)
                for(int j = 0;j < n;j ++)
                    g[i][j] = g[i][j] || (g[i][k] && g[k][j]);
            
        vector<bool> ans;
        for(auto& i : queries) ans.push_back(g[i[0]][i[1]]);

        return ans;
    
    }
};
```

