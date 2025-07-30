#include<iostream>
using namespace std;

struct node {
    int data;
    node* left;
    node* right;
};
struct node*root = NULL;

node* createNode(int a) {
    node* p = new node();
    p->data = a;
    p->left = NULL;
    p->right = NULL;
    return p;
}

node* insert(node* root, int num) {
    if (root == NULL) {
        return createNode(num);
    }
    if (num < root->data) {
        root->left = insert(root->left, num);
    }
    else if (num > root->data) {
        root->right = insert(root->right, num);
    }
    else {
        cout << "Duplicate Data" << endl;
    }
    return root;
}

void inOrder(node* root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << root->data << ", ";
        inOrder(root->right);
    }
}

node* findMin(node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

node* deleteNode(node* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else {

        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }

        else if (root->left == NULL) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            node* temp = root->left;
            delete root;
            return temp;
        }

        else {
            node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

int main() {
    node* root = NULL;
    root = insert(root, 7);
    root = insert(root, 9);
    root = insert(root, 6);
    root = insert(root, 8);
    root = insert(root, 2);
    root = insert(root, 10);
    root = insert(root, 3);

    cout << "InOrder before deletion: ";
    inOrder(root);
    cout << endl;

    root = deleteNode(root, 7); 
    cout << "InOrder after deletion: ";
    inOrder(root);
    cout << endl;

    return 0;
}
