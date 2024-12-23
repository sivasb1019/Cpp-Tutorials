/*
General requirements for deep copy:

	- A normal constructor.
	- A destructor to delete the dynamically allocated memory.
	- A copy constructor to make a copy of the dynamically allocated memory.
	- An overloaded assignment operator.
*/

#include<iostream>
#include<cstring>
using namespace std;
class CopyConstructor
{
    char* s_copy;
public:
    CopyConstructor(const char* str)
    {
        s_copy = new char[16]; //Dynamic memory allocation
        strcpy(s_copy, str);
    }
    /* concatenate method */
    void concatenate(const char* str)
    {
        strcat(s_copy, str); //Concatenating two strings
    }

    /* copy constructor */
    CopyConstructor(CopyConstructor &obj) {
        cout << "Copy constructor called..." << endl;
        s_copy = new char[16];
        strcpy(s_copy, obj.s_copy);
    }

    /* Operator Overloading */
    /*CopyConstructor operator=() {
        delete[] obj.s_copy;

    }*/

    ~CopyConstructor()
    {
        delete[] s_copy;
    }
    void display()
    {
        cout << s_copy << endl;
    }
};
/* main function */
int main()
{
    CopyConstructor c1("Software");
    CopyConstructor c2 = c1; //Copy constructor
    c1.display();
    c2.display();
    c1.concatenate("Developer");    //c1 is invoking concatenate()
    c1.display();
    c2.display();
    return 0;
}