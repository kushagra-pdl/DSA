#include<iostream>
using namespace std;

struct Node{
  int data;
  Node*left=NULL;
  Node*right=NULL;  
  int height=0;
};

Node*root=NULL;


int height(Node* root);
int getBF(Node* root);
Node* leftrotate(Node* root);
Node* rightrotate(Node* root);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
void levelorder(Node* root);
int getmin(Node* root);
int getmax(Node* root);

Node*createNode(int a){
  Node*p = new Node();
  p->data = a;
  p->left = NULL;
  p->right = NULL;
  p->height = 1;
  return p;
}

Node*insertNode(Node*root, int num){
  if (root == NULL){
    return createNode(num);
  }
  if (num < root->data){
    root->left = insertNode(root->left, num);
  }
  else{
    root->right = insertNode(root->right, num);
  }
  root->height = 1 + max(height(root->left), height(root->right));
  int bf = getBF(root);
  if (bf > 1 && num < root->left->data){
    return rightrotate(root);
  }
  if (bf < -1 && num > root->right->data){
    return leftrotate(root);
  }
  if (bf > 1 && num > root->left->data){
    root->left = leftrotate(root->left);
    return rightrotate(root);
  }
  if (bf < -1 && num < root->right->data){
    root->right = rightrotate(root->right);
    return leftrotate(root);
  }
  return root;
}

int height(Node* root) {
  if (root == NULL) return 0;
  return root->height;
}

int getBF(Node* root) {
  if (root == NULL) return 0;
  return height(root->left) - height(root->right);
}


Node* leftrotate(Node*root){
  Node*temp = root->right;
  root->right = temp->left;
  temp->left = root;
  return temp;
}
Node* rightrotate(Node*root){
  Node*temp = root->left;
  root->left = temp->right;
  temp->right = root;
  return temp;
}
Node* checkBF(Node*root){
  int balancefactor = getBF(root);
  if (balancefactor > 1 && getBF(root->left) >= 0){
    return rightrotate(root);
  }
  if (balancefactor < -1 && getBF(root->right) <= 0){
    return leftrotate(root);
  }
  if (balancefactor > 1 && getBF(root->left) < 0){
    root->left = leftrotate(root->left);
    return rightrotate(root);
  }
  if (balancefactor < -1 && getBF(root->right) > 0){
    root->right = rightrotate(root->right);
    return leftrotate(root);
  }
  return root;
}

void inorder(Node* root) {
  if (root == NULL) return;
  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

void preorder(Node* root) {
  if (root == NULL) return;
  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}

void postorder(Node* root) {
  if (root == NULL) return;
  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}

void levelorder(Node* root) {
  if (root == NULL) return;
  // Simple level order without queue for now
  cout << root->data << " ";
}

int getmin(Node* root) {
  if (root == NULL) return -1;
  while (root->left != NULL) root = root->left;
  return root->data;
}

int getmax(Node* root) {
  if (root == NULL) return -1;
  while (root->right != NULL) root = root->right;
  return root->data;
}

Node* traverse(Node*root){
  if (root == NULL){
    return NULL;
  }
  root->left = traverse(root->left);
  root->right = traverse(root->right);
  return checkBF(root);
}
int main(){
  // Create Right-Right imbalance
  root = insertNode(root, 10);
  root = insertNode(root, 20);
  root = insertNode(root, 30);
  
  cout << "Before: BF=" << getBF(root) << " ";
  inorder(root);
  cout << endl;
  
  // Fix with rotation
  root = insertNode(root, 40);
  
  cout << "After: BF=" << getBF(root) << " ";
  inorder(root);
  cout << endl;
  
  return 0;
}