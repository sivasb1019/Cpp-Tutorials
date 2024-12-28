/*
In this example,
    - The integer a is automatically converted to a float when assigned to b. 
    - The conversion is safe because float can hold the integer value without losing any information.
*/

#include <iostream>
using namespace std;

int main() {
    int a = 10;
    float b = a;  // Implicit casting: int to float
    cout << "The value of b: " << b << endl;  // Output: 10.0
    return 0;
}