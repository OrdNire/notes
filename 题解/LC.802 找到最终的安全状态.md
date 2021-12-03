# LC.802 找到最终的安全状态

>在有向图中, 我们从某个节点和每个转向处开始, 沿着图的有向边走。 如果我们到达的节点是终点 (即它没有连出的有向边), 我们停止。

>现在, 如果我们最后能走到终点，那么我们的起始节点是最终安全的。 更具体地说, 存在一个自然数 K,  无论选择从哪里开始行走, 我们走了不到 K 步后必能停止在一个终点。

>哪些节点最终是安全的？ 结果返回一个有序的数组。

>该有向图有 N 个节点，标签为 0, 1, ..., N-1, 其中 N 是 graph 的节点数.  图以以下的形式给出: graph[i] 是节点 j 的一个列表，满足 (i, j) 是图的一条有向边。

```
示例：
输入：graph = [[1,2],[2,3],[5],[0],[5],[],[]]
输出：[2,4,5,6]
这里是上图的示意图。

```

![LC802](D:\个人资料\Notes\题解\images\LC802.png)

> 提示：
>
>     graph 节点数不超过 10000.
>     图的边数不会超过 32000.
>     每个 graph[i] 被排序为不同的整数列表， 在区间 [0, graph.length - 1] 中选取。
>



**题解**

该题是一个图论的题目，根据提示可知，无平行边和自环。

该题翻译过来的意思就是判断从某个点开始后面没有环，即总会从某个点开始走到一个没有出边的点即停止，那么该点就为安全状态的点。

逆向思考，没有出边的点一定是安全点，那么进入该点的点也一定是个安全点，因为可以到这个出度为0的安全点停下，以此类推，逆推回去的所有点都是安全点

那么这道题就转换为了拓扑排序的题，且该题是一个逆拓扑排序的题，但是可以将有向边逆向，即转换为求一个正向拓扑排序的题



**代码**

```c
const int N = 100010;
class Solution {
public:
    int h[N],e[N],ne[N],idx;
    int d[N];
    int n;
    vector<int> ans;

    void add(int a, int b){
        e[idx] = b,ne[idx] = h[a],h[a] = idx ++;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        n = graph.size();
        memset(h, -1, sizeof h);
        memset(d, 0 ,sizeof d);

        for(int i = 0;i < graph.size();i ++){
            for(int j : graph[i]){
                add(j, i);
                d[i] ++;
            }
        }

        queue<int> q;
        for(int i = 0;i < n;i ++){
            if(!d[i]){
                q.push(i);
                ans.push_back(i);
            }
        }
            

        while(q.size()){

            int t = q.front();
            q.pop();

            for(int i = h[t];i != -1;i = ne[i]){
                int j = e[i];
                d[j] --;
                if(!d[j]){
                    q.push(j);
                    ans.push_back(j);
                }
            }

        }

        sort(ans.begin(),ans.end());

        return ans;
    }
};
```