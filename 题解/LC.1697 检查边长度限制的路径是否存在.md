# LC.1697 检查边长度限制的路径是否存在

链接：https://leetcode-cn.com/problems/checking-existence-of-edge-length-limited-paths/

>给你一个 n 个点组成的无向图边集 edgeList ，其中 edgeList[i] = [ui, vi, disi] 表示点 ui 和点 vi 之间有一条长度为 disi 的边。请注意，两个点之间可能有 超过一条边 。
>
>给你一个查询数组queries ，其中 queries[j] = [pj, qj, limitj] ，你的任务是对于每个查询 queries[j] ，判断是否存在从 pj 到 qj 的路径，且这条路径上的每一条边都 严格小于 limitj 。
>
>请你返回一个 布尔数组 answer ，其中 answer.length == queries.length ，当 queries[j] 的查询结果为 true 时， answer 第 j 个值为 true ，否则为 false 。
>



>输入：n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
>输出：[false,true]
>对于第一个查询，0 和 1 之间没有小于 2 的边，所以我们返回 false 。
>对于第二个查询，有一条路径（0 -> 1 -> 2）两条边都小于 5 ，所以这个查询我们返回 true 。



**题解**

该题本质上是一道并查集的题，对于询问，我们要判断询问的两点之间是否存在每一条边都小于询问限制的边长

那么我们可以转换一下思维，两点之间所有边限制边长，我们可以只需要利用所有边长小于限制边的边，利用并查集，最后我们只需要判断询问的两点之间是否连通即可

所以，第一步就是将边和询问都按照权值排序，每一次遍历询问都只需要将边权小于限制长度的边长加入并查集，最后判断一下询问的两点是否连通即可，很典型的并查集

c

**代码**

```c
const int N = 100010;

struct Node {
    int a, b, c, d;

    bool operator< (const Node& t) const {
        return c < t.c;
    }
}e[N],q[N];

class Solution {
public:

    vector<int> p;

    int find(int x){
        if(p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& ee, vector<vector<int>>& qq) {
        int m = ee.size(), k = qq.size();
        for(int i = 0;i < m;i ++){
            e[i] = {ee[i][0],ee[i][1],ee[i][2]};
        }
        for(int i = 0;i < k;i ++){
            q[i] = {qq[i][0],qq[i][1],qq[i][2],i};
        }

        sort(e,e + m),sort(q,q + k);
        p.resize(n);
        for(int i = 0;i < n;i ++) p[i] = i;
        vector<bool> res(k);
        for(int i = 0,j = 0;i < k;i ++){

            while(j < m && e[j].c < q[i].c){
                int a = e[j].a, b = e[j].b;
                p[find(a)] = find(b);
                j ++;
            }
            res[q[i].d] = find(q[i].a) == find(q[i].b);
        }

        return res;
    }
};
```

