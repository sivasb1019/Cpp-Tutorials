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
