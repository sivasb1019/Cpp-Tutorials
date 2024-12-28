/*
In this example, The double value pi is explicitly cast to an int, which truncates the fractional part and only stores the integer portion.
*/

#include <iostream>
using namespace std;

int main() {
    double pi = 3.14159;
    int pi_int = (int)pi;  // Explicit casting: double to int
    cout << "The value of pi_int: " << pi_int << endl;  // Output: 3
    return 0;
}