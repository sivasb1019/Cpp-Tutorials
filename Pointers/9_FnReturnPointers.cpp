/*
Returning a Pointer from a Function
There are two main types of pointers you can return from a function:
    - Returning a pointer to a static variable – Safe, as the memory is allocated in the program's data segment.
    - Returning a pointer to dynamically allocated memory – The memory is allocated during runtime using new and should be explicitly freed using delete.

Memory Management:
    - If you return a pointer to dynamically allocated memory, the caller is responsible for deallocating it using delete[] (for arrays) or delete (for single objects).
    - Failure to free dynamically allocated memory results in memory leaks.

Returning Pointers to Local Variables:
    - Do NOT return pointers to local variables. Local variables are destroyed when the function exits, so the pointer will point to a memory location that is no longer valid (dangling pointer).

*/

#include <iostream>
using namespace std;

int* getStaticVariable() {
    static int value = 10;  // Static variable
    return &value;
}

int* createDynamicArray(int size) {
    int* arr = new int[size];
    
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
    
    return arr;  // Return pointer to the dynamically allocated array
}

int main() {
    int* ptr = getStaticVariable();
    cout << "The value is: " << *ptr << endl;  // Dereference the pointer to get the value

    int* array = createDynamicArray(*ptr);
    
    // Print the array elements
    for (int i = 0; i < *ptr; ++i) {
        cout << array[i] << " ";
    }
    cout << endl;
    
    // Free the dynamically allocated memory
    delete[] array;
    
    return 0;
}
