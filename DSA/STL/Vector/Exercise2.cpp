// Store Employee Information And Display Using Structured vector

#include <iostream>
#include <string>
#include <vector>

class Employees {
private:
	struct Employee {
		int empID;
		int salary;
		std::string name, department;
	};
	static int employeeID;

	//Employee() : employeeID(1) {}

	std::vector<Employee> employeeList;

	void getEmployee(Employee &emp) {
		std::cout << "Enter name, salary, department of an employee " << employeeID << ": ";
		std::cin >> emp.name >> emp.salary >> emp.department;
		emp.empID = employeeID;
		employeeID++;
	}


public:

	void insertEmployeesAtEnd(int numbers=1) {
		for (int i = 0; i < numbers; i++) {
			Employee emp;
			getEmployee(emp);
			employeeList.push_back(emp);
			std::cout << "\nEmployee added successfully with id: " << emp.empID << std::endl;
			std::cout << "--------------------------------------" << std::endl;
		}
	}

	void insertEmployeesAtPosition(int pos=0) {
		if (getLastEmployeeId() < pos) {
			std::cout << "Index out of bound... Invalid posiiton" << std::endl;
			std::cout << "--------------------------------------" << std::endl;
			return;
		}
		Employee emp;
		getEmployee(emp);
		employeeList.insert(employeeList.begin() + pos, emp);
		std::cout << "\nEmployee added successfully with id: " << emp.empID << std::endl;
		std::cout << "--------------------------------------" << std::endl;

	}

	void deleteEmployeeByEnd() {
		employeeList.pop_back();
		std::cout << "Employee at the end deleted successfully." << std::endl;
		std::cout << "--------------------------------------" << std::endl;
	}



	void displaySize() {
		std::cout << "Total size: " << employeeList.size() << std::endl;;
		std::cout << "--------------------------------------" << std::endl;
	}

	void displayCapacity() {
		std::cout << "Total capacity: " << employeeList.capacity() << std::endl;;
		std::cout << "--------------------------------------" << std::endl;
	}

	void displayMaxCapacity() {
		std::cout << "Max Size: " << employeeList.max_size() << std::endl;
		std::cout << "--------------------------------------" << std::endl;
	}

	int getLastEmployeeId() {
		return employeeID - 1;
	}

	void displayEmployees() {
		if (employeeList.empty()) {
			std::cout << "Employees data list is empty... Try adding some...." << std::endl;
			std::cout << "--------------------------------------" << std::endl;
			return;
		}
		for (auto employee : employeeList) {
			std::cout << "ID          : " << employee.empID << std::endl;
			std::cout << "Name        : " << employee.name << std::endl;
			std::cout << "Salary      : " << employee.salary << std::endl;
			std::cout << "Department  : " << employee.department << std::endl;
			std::cout << "--------------------------------------" << std::endl;
		}
	}
	void displayEmployeesInReverse() {
		if (employeeList.empty()) {
			std::cout << "Employees data list is empty... Try adding some...." << std::endl;
			std::cout << "--------------------------------------" << std::endl;
			return;
		}
		for (auto itr = employeeList.rbegin(); itr != employeeList.rend(); itr++) {
			std::cout << "ID          : " << itr -> empID << std::endl;
			std::cout << "Name        : " << itr -> name << std::endl;
			std::cout << "Salary      : " << itr -> salary << std::endl;
			std::cout << "Department  : " << itr -> department << std::endl;
			std::cout << "--------------------------------------" << std::endl;
		}
	}
};

int Employees::employeeID = 1;

int main() {
	int option, size, position;
	Employees emp;
	while (1) {
		std::cout << "Option 0: Display maximum size of the list" << std::endl;
		std::cout << "Option 1: Add single employee at end" << std::endl;
		std::cout << "Option 2: Add multiple employees at end" << std::endl;
		std::cout << "Option 3: Add employees at specific position" << std::endl;
		std::cout << "Option 4: Delete employee data at end" << std::endl;
		std::cout << "Option 5: Display employees data" << std::endl;
		std::cout << "Option 6: Display employees data in reverse" << std::endl;
		std::cout << "Option 7: Display size of the list" << std::endl;
		std::cout << "Option 8: Display capacity of the list" << std::endl;
		std::cout << "Option 9: Exit" << std::endl;
		std::cout << "--------------------------------------" << std::endl;

		std::cout << "Choose any options from above: ";
		std::cin >> option;
		std::cout << "--------------------------------------" << std::endl;

		switch (option) {
		case 0:
			emp.displayMaxCapacity();
			break;
		case 1:
			emp.insertEmployeesAtEnd();
			break;
		case 2:
			std::cout << "Enter number of employees to be add: ";
			std::cin >> size;
			emp.insertEmployeesAtEnd(size);
			break;
		case 3:
			std::cout << "Enter position: ";
			std::cin >> position;
			emp.insertEmployeesAtPosition(position);
			break;
		case 4:
			emp.deleteEmployeeByEnd();
			break;
		case 5:
			emp.displayEmployees();
			break;
		case 6:
			emp.displayEmployeesInReverse();
			break;
		case 7:
			emp.displaySize();
			break;
		case 8:
			emp.displayCapacity();
			break;
		case 9:
			return 0;
		default:
			std::cout << "Enter valid option!!!" << std::endl;
		}
	}
	return 0;

}