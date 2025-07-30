#include<iostream>
using namespace std;

#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

// Swap two elements in the heap
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Insert a new value into the min-heap
void insert(int value) {
    heap[heapSize] = value;
    int i = heapSize;
    heapSize++;
    // Bubble up
    while (i != 0 && heap[(i-1)/2] > heap[i]) {
        swap(heap[i], heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

// Display the heap as an array
void display() {
    for (int i = 0; i < heapSize; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

// Display the heap as a tree (sideways)
void graphicalDisplay(int index = 0, int space = 0) {
    if (index >= heapSize) return;
    space += 5;
    // Right child
    graphicalDisplay(2 * index + 2, space);
    // Print current node
    cout << endl;
    for (int i = 5; i < space; i++) cout << " ";
    cout << heap[index] << "\n";
    // Left child
    graphicalDisplay(2 * index + 1, space);
}

int main() {
    insert(10);
    insert(5);
    insert(15);
    insert(3);
    insert(7);
    insert(12);
    insert(18);
    insert(1);
    insert(4);

    cout << "Min-Heap array: ";
    display();
    cout << "\nGraphical display (tree):\n";
    graphicalDisplay();
    return 0;
}




