#include <iostream>
using namespace std;

struct Node{
	int data;
	Node* left;
	Node* right;
};

class SearchTree {
public:
	SearchTree(){root = NULL;}
	
	void create(){
		int x;
		cin >> x;
		while(x != 0){
			insert(x,root);
			cin >> x;
		}
	}
	
	void insert(int x,Node* &p){
		if(!p){
			p = new Node();
			p->data = x;
			p->left = NULL;
			p->right = NULL;
			return;
		}
		if(x <= p->data) insert(x,p->left);
		else insert(x,p->right);
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
