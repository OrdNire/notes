#include <iostream>
using namespace std;

struct Bhnode{
	int weight;
	int parent;
	int left,right;
};

// 2*n-1是因为n个存节点，过程会有n-1次合并，则多n-1用来存过程的节点 
Bhnode hf[2*n - 1];

int main()
{
	
	return 0;
}
