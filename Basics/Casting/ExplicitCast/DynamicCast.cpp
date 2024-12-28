// Downcasting with polymorphism

#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { cout << "Base class" << endl; }
};

class Derived : public Base {
public:
    void show() override { cout << "Derived class" << endl; }
};

int main() {
    Base* basePtr = new Derived();
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);  // Safe downcasting
    if (derivedPtr) {
        derivedPtr->show();  // Output: Derived class
    }
    return 0;
}