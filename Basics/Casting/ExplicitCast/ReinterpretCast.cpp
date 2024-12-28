#include <iostream>
using namespace std;

int main() {
    int x = 10;
    char* p = reinterpret_cast<char*>(&x);  // Reinterpret pointer type
    cout << "Reinterpreted value: " << *p << endl;  // Output will be a byte representation
    return 0;
}