#include<iostream>
using namespace std;

typedef struct Node {
  int data;
  Node* left = NULL;
  Node *right = NULL;
}Node;

Node*root = NULL;

Node* CreateNode(int a) {
  Node* p = new Node();
  p -> data = a;
  p -> left = NULL;
  p -> right = NULL;
  return p;
}

int countNodes(Node*root){
  if (root == NULL){
    return NULL;
  }
  return 1 + countNodes(root->left)+ countNodes(root->right);
}
// Maintaining heap property while inserting a node
Node* insertNode(Node*root, int num, int index, int total){
  if (root == NULL){
    return CreateNode(num);
  }
  if(2*index+1 < total){
    root->left = insertNode(root->left,num,2*index+1,total);
    if(root->left->data <root->data){
      swap(root->left->data,root->data);
    }
  }else {
    if (2*index+2 <total){
      root->right = insertNode(root->right,num,2*index+2,total);
      if (root->right->data < root->data){
        swap ( root->right->data , root->data);
      }
    }
  }
  return root;
}
//Inserting a node in the heap
Node* insertHeap(Node*root, int num){
  int total= countNodes(root);
root = insertNode(root,num,0, total);
}
void inorder(Node*root){
  if (root != NULL){
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
  }
}
//Get min-value(top Priopity) of the heap
int getmin(Node*root){
  if(root==NULL){
    cout<<"Heap is empty"<<endl;
    return -1;
  }
  return root->data;
}
//get last node based on index and total count
Node*getlastNode(Node*root, int index, int total){
  if (root == NULL)return NULL;
  if (index == total -1 )return root;

  Node* temp = getlastNode(root->left, 2*index+1, total);
  if (temp != NULL)return temp;
  return getlastNode(root->right, 2*index+2, total);
}
//Delete Last Node and Tree
Node* deletelastNode(Node*root, int index, int total, int& found){
  if (root==NULL)return NULL;
  if (index==total-1){
    delete root;
    found =1;
    return NULL;
  }
  root->left = deletelastNode(root->left,2*index+1,total,found);
  if (found == 0){
    return root;
  }
  root->right = deletelastNode(root->right,2*index+2,total,found);
  if (found == 0){
    return root;
  }
}
//restore Heap Property after deletion
Node* heapify(Node*root){
  if (root == NULL) return NULL;
  Node* smallest = root;
  if (root->left != NULL && root->left->data < smallest->data) {
    smallest = root->left;
  }
  if( root->right != NULL && root->right->data < smallest->data) {
    smallest = root->right;
  }
  if (smallest != root) {
    swap(root->data, smallest->data);
    heapify(smallest);
  }
  return root;
}
//Remove the min-value(top Priopity) of the heap
Node* removeMin(Node*root){
  int total = countNodes(root);
  if (total == 0) {
    cout << "Heap is empty" << endl;
    return NULL;
  }
  if (total == 1) {
    delete root;
    return NULL;
  }
  Node* lastNode = getlastNode(root, 0, total);
  if (lastNode == NULL) {
    cout << "Last node not found" << endl;
    return root;
  }
  root->data = lastNode->data; // Replace root with last node
  int found = 0;
  root = deletelastNode(root, 0, total, found); // Delete last node
  root = heapify(root); // Restore heap property
  return root;
}
int main(){
  root = insertHeap(root, 10);
  root = insertHeap(root, 20);
  root = insertHeap(root, 5);
  root = insertHeap(root, 15);
  root = insertHeap(root, 30);
  root = insertHeap(root, 25);

  cout<<"Heap in-order traversal: ";
  inorder(root);
  cout << endl;

  cout<<"Top priority (min value) in the heap: " << getmin(root) << endl;
  root = removeMin(root);
  cout<<"Heap after removing min value: ";
  inorder(root);
  cout << endl;
  return 0;
}