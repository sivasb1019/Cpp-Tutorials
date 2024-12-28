/*
const_cast<type>(expression)
This is used to add or remove the const qualifier from a variable. You can change a const object to a non-const object or vice versa.
*/

#include <iostream>
using namespace std;

void changeValue(const int& val) {
    int& nonConstVal = const_cast<int&>(val);  // Removing const
    nonConstVal = 10;
}

int main() {
    const int x = 5;
    changeValue(x);
    cout << "x after change: " << x << endl;  // Output: 10 (this is undefined behavior)
    return 0;
}