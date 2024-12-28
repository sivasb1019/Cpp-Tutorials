#include <iostream>
using namespace std;

int main() {
    double pi = 3.14159;
    int pi_int = static_cast<int>(pi);  // Explicit casting using static_cast
    cout << "The value of pi_int: " << pi_int << endl;  // Output: 3
    return 0;
}