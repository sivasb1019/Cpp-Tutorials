/*
Function Pointers and Callbacks:
    - A name of a function is also pointing to an address.
    - A function pointer is a pointer that points to a function instead of a data value. 
    - This allows you to dynamically call different functions at runtime. 
    - Function pointers are useful in scenarios such as callback functions, implementing dynamic dispatch, and passing functions as arguments to other functions.
    - A callback is a function that is passed as an argument to another function and is expected to be called (or executed) at some point during the execution of the function it is passed to. 
    - This technique is widely used in event-driven programming, asynchronous processing, and many libraries and APIs to allow user-defined behavior.

Callback Concept:
    - A callback is essentially a way to allow a lower-level function to call a higher-level function at an appropriate time. 
    - It is typically used when you need to provide custom behavior without modifying the core logic of the function.

Syntax of Callback Function Using Function Pointers:
    - Define a function that will act as the callback.
    - Pass the function as an argument to another function using a function pointer.
    - Inside the called function, invoke the callback function at the appropriate time.
*/

#include <iostream>
using namespace std;

// A function that takes two integers and a function pointer as arguments
void applyOperation(int a, int b, int (*operation)(int, int)) {
    int result = operation(a, b);  // Call the function pointed to by operation
    cout << "Result of operation: " << result << endl;
}

// A function to multiply two integers
int multiply(int x, int y) {
    return x * y;
}

int add(int a, int b) {
    return a + b;
}

int main() {
    // Declare a function pointer and assign it the address of the add function
    int (*func_ptr)(int, int) = add;
    
    // Call the function through the pointer
    int result = func_ptr(5, 3);  // Equivalent to add(5, 3)
    
    cout << "Result of addition: " << result << endl;

    // Call applyOperation with the multiply function pointer. This is called function callback.
    applyOperation(4, 5, multiply);  
    
    return 0;
}
