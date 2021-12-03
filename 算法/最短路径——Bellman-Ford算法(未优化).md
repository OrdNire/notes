# 最短路径——Bellman-Ford算法(未优化)

**Dijkstra算法能解决单源最短路径问题，即一个顶点到其它所有顶点的最短路径**

但如果有负权边，则dis所确定的该顶点到其它某一个顶点的确定值会改变，无法解决负权变的问题

Bellman-Ford算法可以有效解决负权边的问题

**Bellman-Ford算法**

原理：使用邻接表存储每一条边的信息，即U为起始顶点,V为终止顶点，W为权值

首先初始化源点到各个顶点的距离dis

再进行对各边的松弛，此步和Dijkstra算法相同

```c++
//以1为源点为例
//对每一条边进行松弛
for(int i=1;i<=m;i++){
    if(dis[v[i]] > dis[u[i]] + w[i]){
        dis[v[i]] = dis[u[i]] + w[i];
    }
}
```

松弛完第一轮后，**可以得到该源点”只能经过一条边“到其余顶点的最短路径长度**

松弛完第二轮后，**可以得到该源点"最多经历两条边"到其余顶点的最短路径长度**

以此类推，

容易得到，需要经过n-1轮松弛，n为顶点个数，即最多经历n-1条边得到源点到其余顶点的最短路径长度

**代码**

```c++
#include <iostream>
using namespace std;

int main()
{
	int inf = 99999999;
	int n,m;
	cin>>n>>m;
	int dis[n+1],u[m+1],v[m+1],w[m+1];
	//读入边 
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
	}
	//初始化dis,这里以1作为源点为例,即dis[i]存储1到各顶点的最短路径 
	for(int i=1;i<=n;i++){
		dis[i] = inf;
	} 
	dis[1] = 0;
	
	//Bellman-Ford核心算法 
	for(int k=0;k<n-1;k++){
		for(int i=1;i<=m;i++){
			if(dis[v[i]] > dis[u[i]] + w[i]){
				dis[v[i]] = dis[u[i]] + w[i];
			}
		}
	}
	
	//输出结果
	for(int i=1;i<=n;i++){
		cout<<dis[i]<<" ";
	} 
	return 0;
}
```



**此外，Bellman-Ford算法同时也能检测图是否是负权回路**

如果n-1轮松弛结束后，仍然能进行有效松弛，则表示该图是负权回路

```c++
//检测负权回路
flag = 0;
for(int i=0;i<=m;i++){
    if(dis[v[i]] > dis[u[i]] + w[i]){
        flag = 1;
    }
}
if(flag){
    cout<<"此图含有复权回路";
}
```

**此外，n-1其实是最大松弛轮数，存在n-1轮前就已经松弛完全全部且得到所有的最短路径**

可以添加一个check变量标记dis在本轮松弛中是否发送了变化，若没用变化则可以直接跳出

```c++
#include <iostream>
using namespace std;

int main()
{
	int inf = 99999999;
	int n,m;
	cin>>n>>m;
	int dis[n+1],u[m+1],v[m+1],w[m+1];
	//读入边 
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>w[i];
	}
	//初始化dis,这里以1作为源点为例,即dis[i]存储1到各顶点的最短路径 
	for(int i=1;i<=n;i++){
		dis[i] = inf;
	} 
	dis[1] = 0;
	
	//Bellman-Ford核心算法 
	for(int k=0;k<n-1;k++){
        int check = 0;//记录本轮是否发送松弛，未松弛则已经得到结果
		for(int i=1;i<=m;i++){
			if(dis[v[i]] > dis[u[i]] + w[i]){
				dis[v[i]] = dis[u[i]] + w[i];
                check = 1;
			}
		}
        //没有发生松弛，则dis未更新，结束循环
        if(!check){
            break;
        }
	}
    
    //检测负权回路
    flag = 0;
   	for(int i=1;i<=m;i++){
        if(dis[v[i]] > dis[u[i]] + w[i]){
            flag = 1;
        }
    }
    if(flag) cout<<"此图有负权回路";
	
	//输出结果
	for(int i=1;i<=n;i++){
		cout<<dis[i]<<" ";
	} 
	return 0;
}
```

**复杂度分析**

Bellman-Ford算法的时间复杂度在未优化是为O(NM);

空间复杂度O(M);