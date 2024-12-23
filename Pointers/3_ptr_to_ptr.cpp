/*A pointer to a pointer (also known as a pointer of pointer) is a concept in C and C++ where you have a pointer that points to another pointer. This allows for multiple levels of indirection.

Syntax:
    type **pointer_to_pointer;

type: The data type of the value the pointer will point to (e.g., int, char).
pointer_to_pointer: The variable that holds the address of a pointer, which in turn holds the address of the actual data.
Concept:
Pointer: A pointer holds the address of a variable.
Pointer to Pointer: A pointer that holds the address of another pointer.
*/

#include <iostream>
using namespace std;

int main() {
    int num = 10;                // Regular integer variable
    int* ptr = &num;             // Pointer that holds the address of `num`
    int** ptr_to_ptr = &ptr;     // Pointer to pointer that holds the address of `ptr`

    // Accessing the value using pointer to pointer
    cout << "Value of num: " << **ptr_to_ptr << endl;   // Dereferencing twice to get the value of `num`

    // Accessing the address of `num`
    cout << "Address of num: " << &num << endl;         
    cout << "Address of num via pointer: " << *ptr_to_ptr << endl; // `*ptr_to_ptr` is the address of `num`
    cout << "Address of ptr: " << ptr_to_ptr << endl;   // `ptr_to_ptr` is the address of `ptr`

    return 0;
}
