/*
When the const pointer variable point to the value :
Syntax: data_type* const var_name;

Explanation:
-The values that are stored in the corresponding pointer variable iand j are modifiable, but the locations that are
pointed out by const - pointer variables where the corresponding values of x and y are stored aren’t modifiable.

Otherwise, the following error will appear :
-The pointer variables are constand pointing to the locations where the xand y are stored if we try to change the
address location then we’ll face the error.
*/
 
#include <iostream>
using namespace std;

// Driver Code
int main()
{
    // x and z non-const var
    int x = 5;
    int z = 6;

    // y and p non-const var
    char y = 'A';
    char p = 'C';

    // const pointer(i) pointing
    // to the var x's location
    int* const i = &x;

    // const pointer(j) pointing
    // to the var y's location
    char* const j = &y;

    // The values that is stored at the memory location can
    // modified even if we modify it through the pointer
    // itself No CTE error
    *i = 10;
    *j = 'D';

    // CTE because pointer variable
    // is const type so the address
    // pointed by the pointer variables
    // can't be changed
    // i = &z;
    // j = &p;

    cout << *i << " and " << *j << endl;
    cout << i << " and " << j;

    return 0;
}