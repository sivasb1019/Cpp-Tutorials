// Store Employee Information And Display Using Structure array

#include <iostream>
#include <string>

class Employees{
private:
	struct Employee {
		int empID, salary;
		std::string name, department;
		//int salary;
		//std::string dept
	};

	Employee *employeeList;
	int size;
	int capacity;


public:
	Employees(int maxCapacity) {
		size = 0;
		capacity = maxCapacity;
		employeeList = new Employee[capacity];
	}
	~Employees() {
		delete[] employeeList;
	}

	void addEmployees(int empId, std::string name, int salary, std::string dept) {
		if (size >= capacity) {
			std::cout << "Error: Maximum amount of employees are stored already..." << std::endl;
			return;
		}
		Employee emp;
		employeeList[size].empID = empId;
		employeeList[size].name = name;
		employeeList[size].salary = salary;
		employeeList[size].department = dept;

		size++;
	}

	void displayEmployees(int arraySize) {
		std::cout << "Displaying all the employees....";
		std::cout << "--------------------------------------" << std::endl;
		for (int i=0; i < arraySize; i++) {
			std::cout << "ID          : " << employeeList[i].empID << std::endl;
			std::cout << "Name        : " << employeeList[i].name << std::endl;
			std::cout << "Salary      : " << employeeList[i].salary << std::endl;
			std::cout << "Department  : " << employeeList[i].department << std::endl;
			std::cout << "--------------------------------------" << std::endl;
		}
	}
};

int main() {
	int arraySize;
	std::cout << "Enter number of employees to be stored: ";
	std::cin >> arraySize;
	Employees employees(arraySize);

	for (int i = 0; i < arraySize; i++) {
		int id, salary;
		std::string name, department;
		std::cout << "Enter id, name, salary, department of employee " << i + 1 << ": " << std::endl;
		std::cin >> id >> name >> salary >> department;
		employees.addEmployees(id, name, salary, department);
	}
	employees.displayEmployees(arraySize);
	return 0;
}