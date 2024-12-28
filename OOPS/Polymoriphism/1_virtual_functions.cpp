/*
Important Points to Remember:
    - Only the Base class Method's declaration needs the Virtual Keyword, not the definition.
    - If a function is declared as virtual in the base class, it will be virtual in all its derived classes.
    - The address of the virtual Function is placed in the VTABLE and the compiler uses VPTR(vpointer) to point to the Virtual Function.

Why can't we create Object of an Abstract Class?
    - When we create a pure virtual function in Abstract class, we reserve a slot for a function in the VTABLE(studied in last topic), but doesn't put any address in that slot. Hence the VTABLE will be incomplete.
    - As the VTABLE for Abstract class is incomplete, hence the compiler will not let the creation of object for such class and will display an errror message whenever you try to do so.
*/

#include <iostream>
#include <string>
using namespace std;

class Departments{
public:
    int id;
    string name;
    string dept;
    Departments(int id, string name, string dept): id(id), name(name), dept(dept){}

    virtual void print()=0;
        //cout << "It is printing function from Departments" <<endl;

};

class HR: public Departments{
    string role;
public:
    HR(int id, string name, string dept, string role): role(role), Departments(id, name, dept){}

    void print(){
        cout << "HR Department" << endl;
        cout << "Id: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << dept << endl;
        cout << "Role: " << role << endl;
    }
};

class Admin: public Departments{
    string role;
public:
    Admin(int id, string name, string dept, string role): role(role), Departments(id, name, dept){}

    void print(){
        cout << "Admin Department" << endl;
        cout << "Id: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << dept << endl;
        cout << "Role: " << role << endl;
    }
};

int main(){
    Admin a(1, "SB", "Development", "SD");
    Departments *dept = &a;
    dept->print();

    HR hr(1, "SB", "HR", "Jr. H");
    Departments *d;

    d = & hr;
    d -> print();
    return 0;
}
