/*
In C and C++, pointers and arrays are closely related. An array is a collection of elements of the same type stored in contiguous memory locations, while a pointer is a variable that stores the memory address of another variable.

Key Differences Between Arrays and Pointers:
Array:
    - An array is a collection of elements, all of the same type, stored contiguously in memory.
    - The array name represents the address of the first element.
    - The size of an array is fixed at the time of its declaration.

Pointer:
    - A pointer is a variable that stores the address of another variable.
    - Pointers can be reassigned to point to different locations in memory during runtime.
    - A pointer can point to any type of data (e.g., integers, floats, arrays).
Array and Pointer Relationship:
    - In many situations, arrays and pointers can be used interchangeably.
    - An array name is essentially a pointer to the first element of the array.


Address - &arr[i] or ptr+i, i means index
Value -arr[i] or *ptr+1

*/

#include <iostream>
using namespace std;

int main() {
    int arr[5] = {10, 20, 30, 40, 50};  // Array of 5 integers

    int* ptr = arr;  // Pointer to the first element of the array

    // Access array elements using the pointer
    cout << "First element: " << *ptr << endl;  // Dereference pointer to get the first element
    cout << "Second element: " << *(ptr + 1) << endl;  // Access the second element using pointer arithmetic

    // Using pointer to print all elements in the array
    for (int i = 0; i < 5; i++) {
        cout << "Element " << i + 1 << ": " << *(ptr + i) << endl;
    }

    return 0;
}
