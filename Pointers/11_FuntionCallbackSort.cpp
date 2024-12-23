#include <iostream>
using namespace std;

bool compare(int a, int b, int desc){
    if(desc) return a < b;
    else return a > b;
}

void swap(int &a, int &b){
    a = a + b;
    b = a - b;
    a = a - b;
}

void bubbleSort(int *a, int size, bool (*func)(int, int, int), int desc=0){
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size-i-1; j++){
            if(func(a[j], a[j+1], desc)){
                swap(a[j], a[j+1]);
            }
        }
    }
}

int main(){
    int arr[] = {10, 27, 12, 30, 28, 1};
    int size = sizeof(arr)/sizeof(arr[0]);

    cout << "Ascending order: ";
    bubbleSort(arr, size, compare);
    for(int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
    cout << "\nDescending order: ";
    bubbleSort(arr, size, compare, 1);
    for(int i=0; i<size; i++){
        cout << arr[i] << " ";
    }

}