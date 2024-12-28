#include <iostream>
#include <memory>


int main() {
	std::unique_ptr<char> u_ptr1(new char('a'));
	std::unique_ptr<int> u_ptr2(new int(27));
	std::cout << "\nUnique smart pointers...\n";
	std::cout << "Address of unique ptr 1: " << u_ptr1.get() << std::endl;
	std::cout << "Address of unique ptr 2: " << u_ptr2.get() << std::endl;

	std::cout << "Value of unique ptr 1: " << *u_ptr1 << std::endl;
	std::cout << "Value of unique ptr 2: " << *u_ptr2.get() << std::endl;

	std::shared_ptr<char> s_ptr1 = std::make_shared<char>('s');
	std::shared_ptr<char> s_ptr2(s_ptr1);
	std::shared_ptr<int> s_ptr3 = std::make_shared<int>(10);
	std::shared_ptr<int> s_ptr4(s_ptr3);

	std::weak_ptr<char> w_ptr1(s_ptr1);
	std::cout << "\nCharater shared pointers...\n";
	std::cout << "Address of shrd ptr 1: " << static_cast<void*>(s_ptr1.get()) << std::endl;
	std::cout << "Address of shrd ptr 2: " << s_ptr2.get() << std::endl;
	std::cout << "Address of weak ptr 1: " << w_ptr1.lock() << std::endl;

	std::cout << "Value of shrd ptr 1: " << *s_ptr1.get() << std::endl;
	std::cout << "Value of shrd ptr 2: " << *s_ptr2 << std::endl;
	std::cout << "Value of weak ptr 1: " << *w_ptr1.lock() << std::endl;
	
	std::cout << "\nInteger shared pointers...\n";
	std::cout << "Address of shrd ptr 3: " << s_ptr3.get() << std::endl;
	std::cout << "Address of shrd ptr 4: " << s_ptr4 << std::endl;

	std::cout << "Value of shrd ptr 3: " << *s_ptr3 << std::endl;
	std::cout << "Value of shrd ptr 4: " << *s_ptr4.get() << std::endl;

	//std::cout << "Value of weak ptr 1: " << w_ptr1.lock() << std::endl;

	return 0;
}