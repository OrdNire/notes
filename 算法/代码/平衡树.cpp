#include <iostream>
using namespace std;

struct Node{
	int data;
	Node* left;
	Node* right;
	int bal;//平衡因子 
};

class SearchTree {
public:
	SearchTree(){root = NULL;}
	
	void create(){
		int x;
		cin >> x;
		while(x != 0){
			insert(x,root,0);
			cin >> x;
		}
	}
	
	void insert(int x,Node* &p,int &b){
		if(!p){
			p = new Node();
			p->data = x;
			p->left = NULL;
			p->right = NULL;
			p->bal = 0;
			b = 1;
			return;
		}
		if(x <= p->data){
			insert(x,p->left,b);
			if(b) Ibalance_L(p,b);//"左"平衡处理 
		}
		else{
			insert(x,p->right,b);
			if(b) Ibalance_R(p,b)//"右"平衡处理 
		}
	}
	
	void Ibalance_L(Node* &p,int &b){
		Node* p1,p2;
		if(p->bal == 1){
			p->bal = 0;
			b = 0;
			return;
		}else if(p->bal == 0){
			p->bal = -1;
			return;
		}else{
			p1 = p->left;
			if(p1->bal == -1){//LL旋转 
				p->left = p1->right;
				p->bal = 0;
				p1->right = p;
				p1->bal = 0;
				p = p1;//p1作为根
				b = 0;//停止回溯 
				return;	 
			}else{
				p2 = p1->right;
				p1->right = p2->left;
				p2->left = p1;
				p->left = p2->right;
				p2->right = p;
				if(p2->bal == 0){
					p->bal = 0;
					p1->bal = 0;
				}else if(p2->bal == -1){
					p1->bal = 0;
					p->bal = 1;
				}else{
					p1->bal = -1;
					p->bal = 0;
				}
				p = p2;
				p->bal = 0;
				b = 0;
				return;
			}
		}
	}
	
	Node* search(int x,Node* p){
		while(p){
			if(p->data == x) return p;
			else if(x < p->data) p = p->left;
			else p = p->right;
		}
		return NULL;
	}
	
	void preTra(){
		pre(root);
	}
	
	void pre(Node* p){
		
		if(!p) return;
		
		cout << p->data << " ";
		pre(p->left);
		pre(p->right);
	}
	
	bool empty(){
		return !root;
	}
	
	Node* getRoot(){
		return root;
	}		
private:
	Node* root;
};

int main()
{
	SearchTree tree;
	tree.create();
	tree.preTra();
//	Node* res = tree.search(25,tree.getRoot());
////	cout << res->data << endl;
	return 0;
}
