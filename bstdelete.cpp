#include<iostream>
using namespace std;

typedef struct node{
  int data;
  node* left;
 node* right;
}node;
node* root=NULL;

void insertBST( node*& root,int data){
  if(root==NULL){
    root=new node();
    root->data=data;
    root->left=NULL;
    root->right=NULL;
    return;
  }
  if(data<root->data){
    insertBST(root->left,data);
  }
  else {
    insertBST(root->right,data);
  }
}
void postorder(node* root){
  if( root == NULL)
  return;
  postorder(root->left);
  postorder(root->right);
cout<<root->data<<" ";
}
node* findmin(node* root){
  while(root && root->left != NULL){
    root= root->left;
  }
  return root;
}
node* deletenode(node* root, int key){
  if(root==NULL){
    return NULL;
  }
  else if (key<root->data){
    root->left= deletenode(root->left,key);
  }
  else if (key> root-> data){
    root->right = deletenode(root->right,key);
  }
  else{
    if(root->left && root->right ==NULL){
      delete root;
      return NULL;
    }
    else if(root->left == NULL){
return root->right;
    }
    else if(root->right == NULL){
return root->left;
    }
    node* temp = findmin(root->right);
    root->data=temp->data;
    root->right= deletenode(root->right, temp->right -> data);

    }
    return root;
  };
  int main(){
  insertBST(root,15);
insertBST(root,10);
insertBST(root,5);
insertBST(root,20);
insertBST(root,17);
insertBST(root,25);
insertBST(root,11);

 postorder(root);


int delkey;
cout<<"Enter the number you wanna delete: ";
cin>>delkey;

deletenode(root,delkey);

cout<<"postorder fter deletion: \n";
postorder(root);
return 0;
  }
