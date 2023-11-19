#include "Employee.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

int main(int argc, char* argv[]) {
	Employee emp;
	std::string input_name = argv[1];
	std::string output_name = argv[2];
	int salary_for_hour = std::stoi(argv[3]);
	std::ifstream file_input;
	std::ofstream file_output;
	std::vector<Employee> employees;

	file_input.open(input_name, std::ios::binary);
	if (file_input.is_open()) {
		while (!file_input.eof()) {
			file_input.read((char*)&emp, sizeof(Employee));
			employees.push_back(emp);
		}
		employees.pop_back();
	}
	file_input.close();

	file_output.open(output_name);
	if (file_output.is_open()) {

		file_output << "NUMBER\tNAME\tHOURS\tSALARY\n";
		for (int i = 0; i < employees.size(); i++)
		{
			file_output << employees[i].num << "\t" << employees[i].name << "\t" << employees[i].hours
				<< "\t" << salary_for_hour * employees[i].hours << "\n";
		}
	}
	file_output.close();
	Sleep(100);
	return 0;
}