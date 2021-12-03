## L1-204 Ribbon负载均衡-轮询算法

**思路**

1. 根据指令集，每一轮R的次数%集群个数得到的下标取某一台机器
2. 指令为S结束该轮，次数重归1
3. 指令为E结束

**代码**

```c++
#include <iostream>
#include <string>
using namespace std;

int main(){
	int n;
	cin>>n;
	string ip[n];
	char mana[10000];
	int m = 0;
	for(int i=0;i<n;i++){
		cin>>ip[i];
	}
	while(1){
		cin>>mana[m];
		if(mana[m] == 'E'){
			break;
		}
		m++;
	}
	int count = 1;
	for(int i=0;i<m;i++){
		if(mana[i] == 'S'){
			count = 1;
		}else if(mana[i] == 'R'){
			cout<<ip[count%n]<<endl;
			count++;
		}
	}
	return 0;
}
```

