#include<iostream>
using namespace std;

struct node{
	int data;
	struct node* left;
	struct node* right;
};
struct node * root =NULL;

void insertBst(struct node*& root, int data){
	if(root==NULL){
		root=new node();
    root->data = data;
		root->left=NULL;
		root->right=NULL;
		return;	
	}
 if(data < root->data)
	insertBst(root->left, data);
else
	insertBst(root->right, data);

 
}

 void displayData(struct node* root){
	if(root==NULL){
		return;
	}

	displayData(root->left);
	displayData(root->right);
	cout<<root->data<<" " ;
}


int main(){
	insertBst(root,60);
	insertBst(root,70);
	insertBst(root,30);
	insertBst(root,20);
	insertBst(root,10000);
	insertBst(root,29);
	insertBst(root,101);
	insertBst(root,109);
	insertBst(root,150);
	insertBst(root,-1);
	displayData(root);
}