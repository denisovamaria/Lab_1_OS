#include "Employee.h"
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
	Employee employees;
	std::string file_name = argv[1];
	int amount_of_notes = std::stoi(argv[2]);
	std::ofstream file;

	file.open(file_name, std::ios::binary);
	if (file.is_open()) {
		for (int i = 0; i < amount_of_notes; i++)
		{
			std::cout << "Enter employee (example: Number Name Hours) " << i + 1 << ":\n";
			std::cin >> employees.num >> employees.name >> employees.hours;
			file.write((char*)&employees, sizeof(Employee));
		}
	}
	file.close();
	return 0;
}