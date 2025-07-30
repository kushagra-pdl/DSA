#include<iostream>
using namespace std;
int main(){
int arr[] = {5, 2, 9, 1, 5, 6, 90, 3, 4, 8, 7, 0, 10};
cout<<"Original array: ";
for(int i = 0; i < 13; i++) {
    cout << arr[i] << " ";
}
int i, j, temp;
for(i = 0; i < 13 - 1; i++) {
    for(j = 0; j < 13 - i - 1; j++) {
        if(arr[j] > arr[j + 1]) {
            temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
        }
    }
    cout << "\nPass " << i + 1 << ": ";
    for(int k = 0; k < 13; k++) {
        cout << arr[k] << " ";
    }
}
cout<<"\nSorted array: ";
for(i = 0; i < 13; i++) {
    cout << arr[i] << " ";

}
cout << endl;
}