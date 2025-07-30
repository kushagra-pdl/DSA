#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    
    Node(int val) {
        data = val;
        left = right = nullptr;
        height = 1;
    }
}; 

int height(Node* root) {
    if (root == nullptr) return 0;
    return root->height;
}

int getBalanceFactor(Node* root) {
    if (root == nullptr) return 0;
    return height(root->left) - height(root->right);
}

void updateHeight(Node* root) {
    if (root == nullptr) return;
    root->height = 1 + max(height(root->left), height(root->right));
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    updateHeight(x);
    updateHeight(y);
    
    return y;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    updateHeight(y);
    updateHeight(x);
    
    return x;
}

void displayTree(Node* root, int space = 0) {
    if (root == nullptr) return;
    
    space += 5;
    displayTree(root->right, space);
    
    cout << endl;
    for (int i = 5; i < space; i++) cout << " ";
    cout << "(" << root->data << ")";
    if (root->left || root->right) {
        cout << " / \\";
    }
    cout << " (BF:" << getBalanceFactor(root) << ")\n";
    
    displayTree(root->left, space);
}

bool isBalanced(Node* root) {
    if (root == nullptr) return true;
    
    int balance = getBalanceFactor(root);
    if (balance > 1 || balance < -1) return false;
    
    return isBalanced(root->left) && isBalanced(root->right);
}

Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }
    
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    
    updateHeight(root);
    return root;
}

int main() {
  Node*root=NULL;
   root = insertNode(root, 10);
   root = insertNode(root, 20);
   root = insertNode(root, 30);
   root = insertNode(root, 40);
   root = insertNode(root, 50);
   root = insertNode(root, 25);
   displayTree(root);
   return 0;
} 