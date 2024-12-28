/*
Array as Function Arguments in C/C++:
Passing an Array to a Function: 
    - When you pass an array to a function, you are actually passing a pointer to the first element of the array. 
    - This is because in C/C++, arrays are not passed by value, but instead, the array name is treated as a pointer.

Passing a Fixed-Size Array: 
    - You can pass an array with a fixed size to a function, but the size needs to be known at compile time. 
    - The array size is part of the type, so you need to specify it in the function signature.

Array Size Information is Lost: 
    - When you pass an array to a function, the array size information is lost. 
    - C and C++ only pass the pointer to the first element of the array, so you must manually pass the size of the array to the function if you need it.

Arrays and Memory: 
    - Arrays are passed to functions by reference. 
    - That means if you modify the contents of the array within the function, the changes will persist in the calling function. 
    - This is because the function operates on the same memory location as the original array.
*/

#include <iostream>

using namespace std;

int SumOfElements(int* A, int size) {  // int* A or int A[] both are same
    int i, sum = 0;
    
    cout << "SOE - Size of A = " << sizeof(A) << ", size of A[0] = " << sizeof(A[0]) << endl;
    
    for (i = 0; i < size; i++) {
        sum += A[i];  // A[i] is the same as *(A + i), accessing array elements
    }

    return sum;  
}

int main() {
    int A[] = {1, 2, 3, 4, 5};
    
    int size = sizeof(A) / sizeof(A[0]);
    
    int total = SumOfElements(A, size);  // A can be used for &A[0]
    
    cout << "Sum of elements = " << total << endl;
    
    cout << "Main - Size of A = " << sizeof(A) << ", size of A[0] = " << sizeof(A[0]) << endl;
    
    return 0;
}
