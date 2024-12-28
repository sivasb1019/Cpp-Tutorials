// C++ program to demonstrate the working of shared_ptr
// Here both smart pointer P1 and P2 are pointing to the
// object Addition to which they both maintain a reference
// of the object
#include <iostream>
using namespace std;
// Dynamic Memory management library
#include <memory>

class Rectangle {
    int length;
    int breadth;

public:
    Rectangle(int l, int b)
    {
        length = l;
        breadth = b;
    }

    int area() { return length * breadth; }
};

int main()
{
    //---\/ Smart Pointer
    shared_ptr<Rectangle> P1(new Rectangle(10, 5));
    // This'll print 50
    cout << P1->area() << endl;
    if (1) {
        shared_ptr<Rectangle> P2;
        P2 = P1;

        // This'll print 50
        cout << P2->area() << endl;

        // This'll now not give an error,
        cout << P1->area() << endl;

        // This'll also print 50 now
        // This'll print 2 as Reference Counter is 2
        cout << P1.use_count() << endl;
    }
    cout << P1.use_count() << endl;

    
    return 0;
}

/*
#include <iostream>
#include <memory>
#include <typeinfo>

class Sample
{
public:
	void PrintMemoryAddress(const std::shared_ptr<Sample>& smp)
	{
		std::cout << "Memory address" << smp << std::endl;
		std::cout << "Hi This is Print from Sample" << std::endl;
	}
};
int main()
{
	std::shared_ptr<int> shd_ptr = std::make_shared<int>(10);
	std::shared_ptr<int> another_shd_ptr(shd_ptr);


	//shd_ptr->PrintMemoryAddress(shd_ptr);
	std::cout << *shd_ptr; *
		std::cout << another_shd_ptr;

	int i = 1;
	const type_info& ti1 = typeid(i);

	std::cout << "TypeId " << ti1 << std::endl;


	return 0;
}
*/