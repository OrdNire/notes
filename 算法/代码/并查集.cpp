#include <stdio.h>

//	并查集
//	要求：根据犯罪的同伙关系，统计有多少个犯罪团队 

int f[10001],n,m,sum = 0;
void init(){
	for(int i=1;i<=n;i++){
		f[i] = i;
	}
	return;
}

int getFather(int v){
	if(f[v] == v){
		return v;
	}else{
		f[v] = getFather(f[v]);		//递归回溯，将根节点设置为路上经过的所有结点的父亲 
		return f[v];				//并查集的"路径压缩" 
	}
}

void merge(int v,int u){
	int t1,t2;		//记录v,u的祖先
	t1 = getFather(v);
	t2 = getFather(u);
	if(t1 != t2){
		f[t2] = t1;		// 根据"靠左原则"将右边的集合作为左边的集合的子集 
	} 
}



int main()
{
	
	int x,y;
	scanf("%d %d",&n,&m);
	init();		//初始化 
	for(int i=0;i<m;i++){
		scanf("%d %d",&x,&y);
		merge(x,y);
	}
	
	for(int i=1;i<=n;i++){
		if(f[i] == i){
			sum++;
		}
	}
	
	printf("sum=%d",sum);
	
	return 0;
}
