#include<iostream>
using namespace std;

struct Node{
  int data;
  Node* next;
};

void createnewNode(char value, Node* &head){
  Node* newNode =  new Node();
  newNode -> data = value;
  newNode -> next = head;
  
  if( head == nullptr){
    head = newNode;
    return;
  }
  Node* temp = head;
  while(temp -> next != NULL){
    temp = temp -> next;
  }

head = newNode;
newNode -> next = temp;

}

void display(Node* head){
  Node* temp = head;
  while(temp != NULL){
    cout << temp -> data << " ";
    temp = temp -> next;
  }
cout << endl;
};

int main(){
  struct Node* head = nullptr;
  char name[] = "Hello World";
  int size = sizeof(name)/sizeof(name[0]);
  for(int i = 0; i < size; i++){
    createnewNode(name[i], head);
  }
  display(head);
  return 0;

  createnewNode('r', head);
  createnewNode('a', head);
  createnewNode('m', head);

  display(head);
  return 0;
}


