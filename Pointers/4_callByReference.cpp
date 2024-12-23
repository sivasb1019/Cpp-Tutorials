/*
Call by Reference is a method of passing arguments to a function where the function gets direct access to the original variable in the calling environment. This means that any changes made to the parameter inside the function will directly affect the original argument used in the function call.

How Call by Reference Works:
In Call by Reference, instead of passing a copy of the argument to the function (as in Call by Value), the address (or reference) of the argument is passed. The function works with the original data rather than a copy, which allows it to modify the actual data.

Syntax:
To use Call by Reference in C++:

You pass the argument using the reference operator & in the function declaration and definition.

By using call By Reference, we can save some amount of memory compared to call By Value.
*/

#include <iostream>
using namespace std;

// Function that takes a reference to an integer as a parameter
void modifyValue(int &num) {
    num = num * 2; // Modify the original variable
}
void incrementValue(int *num) {
    *num = *num + 1; // Increment the original variable
}

int main() {
    int x = 10;

    cout << "Before calling the function: " << x << endl;
    
    // Pass the variable by reference. Here we used two ways to implement call By Reference
    modifyValue(x);
    cout << "After calling the modifyValue function: " << x << endl; // x is modified

    incrementValue(&x);
    cout << "After calling the incrementValue function: " << x << endl; // x is incemented by 1
    
    return 0;
}
