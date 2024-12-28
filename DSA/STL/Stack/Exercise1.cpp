/*

You have an empty sequence, and you will be given N queries. Each query is one of these three types:
1 -> x -Push the element x into the stack.
2 -> Delete the element present at the top of the stack.
3 -> Print the maximum element in the stack.
*/

#include <iostream>
#include<stack>


template <class T> 
class Stack {
private:
	std::stack<T> stackList;

public:

	void pushElement(T& element) {
		stackList.push(elements);
		std::cout << "\nElement deleted successfully at the top." << std::endl;
		std::cout << "---------------------------------" << std::endl;
	}

	void deleteElement() {
		stackList.pop;
		std::cout << "\nElement deleted successfully at the top." << std::endl;
		std::cout << "---------------------------------" << std::endl;
	}


};