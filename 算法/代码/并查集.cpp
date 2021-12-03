#include <stdio.h>

//	���鼯
//	Ҫ�󣺸��ݷ����ͬ���ϵ��ͳ���ж��ٸ������Ŷ� 

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
		f[v] = getFather(f[v]);		//�ݹ���ݣ������ڵ�����Ϊ·�Ͼ��������н��ĸ��� 
		return f[v];				//���鼯��"·��ѹ��" 
	}
}

void merge(int v,int u){
	int t1,t2;		//��¼v,u������
	t1 = getFather(v);
	t2 = getFather(u);
	if(t1 != t2){
		f[t2] = t1;		// ����"����ԭ��"���ұߵļ�����Ϊ��ߵļ��ϵ��Ӽ� 
	} 
}



int main()
{
	
	int x,y;
	scanf("%d %d",&n,&m);
	init();		//��ʼ�� 
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
