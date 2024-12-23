/*
When the pointer variable point to a const value :
Syntax: const data_type* var_name;

Explanation: 
    - Here in the above case, i and j are two pointer variables that are pointing to a memory location const int-type 
      and char-type, but the value stored at these corresponding locations can be changed as we have done above.

Otherwise, the following error will appear: If we try to modify the value of the const variable.
*/

#include <iostream>
using namespace std;

// Driver Code
int main()
{
    int x{ 10 };
    int y{ 27 };
    cout << "x: " << x << " y: " << y << endl;

    const int* i = &x;
    const int* j = &y;
    cout << "i: " << *i << " j: " << *j << endl;

    // Value of x and y can be altered,
    // they are not constant variables
    x = 12;
    y = 30;
    cout << "x: " << x << " y: " << y << endl;

    // Can't change of constant values because,
    // i and j are pointing to const-int
    // & const-char type value
    // *i = 6;
    // *j = 7;
    i = &y;
    j = &x;
    cout <<"i: " << *i << " j: " << *j << endl;
}