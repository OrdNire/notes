# 单源最短路径——Dijkstra算法

指定一个点到其余各个顶点的最短路径

**算法核心**

Dijkstra算法是通过一个dis数组，存储指定顶点到所有顶点的初始路径

此失的初始路径成为“估计值”，因为该路径是否最短未知

通过寻找离指定点最近的顶点i为起点，寻找以该顶点到其它顶点的距离是否比指定点直接到其它顶点的距离短，以此来“松弛”路径，并更新dis(i)数组的值为确定的最短路径

以此类推，当所有估计值转换为确定值时，问题解决

**此方法在未做任何优化下时间复杂度**O(n方)

**代码**

```c++
#include <iostream>
using namespace std;

int main()
{
	//book[i] = 0表示i点处于估计值，1表示i点处于确定值 
	int e[11][11],dis[11],book[11]={0};
	int inf = 99999999;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
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
	//初始dis数组 
	for(int i=1;i<=n;i++){
		dis[i] = e[1][i];
	}
	
	//从顶点1开始寻找所有顶点离1的最短路径
	book[1] = 1; 
	
	//Dijkstra算法核心部分 
	for(int i=1;i<=n-1;i++){
		//找到离1顶点最近的顶点
		int min = inf;
		int u;
		for(int j=1;j<=n;j++){
			if(book[j] == 0 && dis[j] < min){
				min = dis[j];
				u = j;
			}
		} 
		//标记为确认点 
		book[u] = 1;
		//根据此点的出边来寻找从1到该点所有出边的最短路径
		for(int j=1;j<=n;j++){ 
			if(e[u][j] < inf){
				if(dis[j] > dis[u] + e[u][j]){
					dis[j] = dis[u] + e[u][j];
				}
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		cout<<dis[i]<<" ";
	}
	return 0;
}
```

