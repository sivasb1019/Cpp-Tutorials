/*
character array and pointers can be closely related, as both are used to store and manipulate strings or sequences of characters.

Pointers to Characters:
    - A pointer to a character is a variable that stores the memory address of a character.
    - Pointers to characters are used to refer to elements in an array or to strings in C-style string handling.

Relationship Between Character Arrays and Pointers
    - A character array and a pointer to a character are closely related. In fact, when you pass a character array to a function, it is automatically converted to a pointer to the first element of the array.
    - Character arrays store the data directly, whereas pointers store the address of the first element of an array (or string).
    - String literals are usually stored in read-only memory, and when you use a pointer, you can point to these literals. For example, a string literal like "Hello" is actually a pointer to the first character 'H'.
*/

#include <iostream>
using namespace std;

// Function to print characters of a string using a pointer
void print(char* C) {
    while (*C != '\0') {  // Dereference pointer to access the character it points to
        cout << *C;       // Print the character pointed to by C
        C++;              // Increment the pointer to move to the next character
    }
    cout << endl;
}

int main() {
    char C[20] = "Hello";  // Character array to store the string
    //char *C = "Hello"; // String gets stored as compile time constant. We cannot modify the value. i.e C[0] ="h"
    print(C);              
    return 0;
}
