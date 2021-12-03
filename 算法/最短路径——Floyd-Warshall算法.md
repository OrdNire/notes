# 最短路径——Floyd-Warshall算法

##### 求图中任意两点最短路径，可以用n方次深度优先搜索，广度优先搜索。

但以邻接矩阵的形式存储图，DFS时间复杂度O(n方)，BFS时间复杂度为O(n*m)

但如果数据量较大，时间空间都会成指数增长

### Floyd-Warshall算法

此算法利用了动态规划，两顶点之间如果加上一个顶点作为中转，路径减小，则更新图，下一次再在该图的基础上再次插入一个新顶点作为中转，路径小，则更新，以此类推。以局部最优达到全局最优

##### 代码

```c++
#include <iostream>
using namespace std;

int main()
{
	int e[11][11],inf=99999999;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(i == j){
				e[i][j] = 0;
			}else{
				e[i][j] = inf;
			}
		}
	}
	int a,b,c;
	for(int i=0;i<m;i++){
		cin>>a>>b>>c;
		e[a][b] = c;
	}
	
	//Floyd-Warshall算法核心语句 
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(e[i][k] < inf && e[k][j] < inf && e[i][j] > e[i][k] + e[k][j]){
					e[i][j] = e[i][k] + e[k][j];
				}
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<"("<<i<<","<<j<<"):"<<e[i][j]<<endl;
		}
	}
	return 0;
}
```

