/*
Pointers with Multi-Dimensional Arrays
    - Pointers can be used to access elements in multi-dimensional arrays because the array's name itself acts as a pointer to its first element.
2 dimentional array:
arr[i][j] = *(arr[i] + j) = *(*(arr + i) + j)

For 3 dimentional array:
Lets assume int arr2[3][2][2] and address start from 1
1d[3]-> 2 dimension [2]  -> 3 dimension [2]
arr2[0] -> arr2[0][0], arr2[0][1] -> arr2[0][0][0], arr2[0][0][1], arr2[0][1][0], arr2[0][1][1] -> 1 to 16
arr2[1] -> arr2[1][0], arr2[1][1] -> arr2[1][0][0], arr2[1][0][1], arr2[1][1][0], arr2[1][1][1] -> 17 to 32
arr2[2] -> arr2[2][0], arr2[2][1] -> arr2[2][0][0], arr2[2][0][1], arr2[2][1][0], arr2[2][1][1] -> 33 to 48

arr2[i][j][k] = *(arr2[i][j] + k) = *(*(arr2[i] + j) + k) = *(*(*(arr2 + i) + j) + k)
*/
#include <iostream>
using namespace std;

void twoDimension(int (*p)[3]){ // int p[][3]
    
    // Accessing elements using pointer arithmetic
    cout << "First element: " << *(*p) << endl;         // Dereference twice to access arr[0][0]
    cout << "Second element: " << *(*p + 1) << endl;    // arr[0][1]
    cout << "Third element: " << *(*p + 2) << endl;    // arr[0][1]
    cout << "Fourth element: " << *(*p + 3) << endl;    // arr[1][0]
    cout << "Fourth element: " << *(*(p + 1)) << endl;  // arr[1][0]
    //cout << "Seventh element: " << *(*(p + 2)) << endl;  // arr[2][0]
}

void threeDimension(int (*p)[2][2]){ // int p[][2][2]
    cout << "This is how you pass 3 dimensional array to the functions." << endl;
}
int main() {
    int arr[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    twoDimension(arr);

    int arr2[3][2][2] = {
        {{5, 10}, {15, 20}},
        {{25, 30}, {35, 40}},
        {{45, 50}, {55, 60}}
    };
    threeDimension(arr2);


    // cout << "arr: " << arr << " &arr[0]: " << &arr[0] << " " << **arr << endl; // 1
    // cout << "*arr: " << *arr << " arr[0]: " << arr[0] << " &arr[0][0]: " << &arr[0][0] << endl; // 1
    // cout << "arr+1: " << arr+1 << " &arr[1]: " << &arr[1] << endl; // 4
    // cout << "*(arr+1): " << *(arr+1) << " arr[1]: " << arr[1] << " &arr[1][0]: " << &arr[1][0] << endl << endl;
    
    // printf("arr: %u &arr[0]: %u **arr: %u\n", *arr, *&arr[0], **arr);
    // printf("*arr: %u arr[0]: %u &arr[0][0]: %u\n", *arr, arr[0], &arr[0][0]);
    // printf("arr+1: %u &arr[1]: %u\n", (arr + 1), &arr[1]);
    // printf("*(arr+1): %u arr[1]: %u &arr[1][0]: %u\n", *(arr + 1), arr[1], &arr[1][0]);
    // printf("*(arr+1)+2: %u %d\n\n",*(arr+1)+2, **(arr+1)+2);

    // Pointer to the 2D array
    //int *p = arr; // error, we cannot assign multi dimensional array like this 
    //int (*p)[3] = arr;  // `p` points to an array of 3 integers



    return 0;
}
