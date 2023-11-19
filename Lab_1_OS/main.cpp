#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
#include "Employee.h"

using namespace std;

void ReadBinaryFile(const string& binaryName, vector<Employee>& employees) {
    ifstream inputName(binaryName, ios::binary);
    Employee employee;
    if (inputName.is_open()) {
        while (inputName.read((char*)&employee, sizeof(Employee))) {
            employees.push_back(employee);
        }
        employees.pop_back();
        inputName.close();
    } else {
        cerr << "Error opening binary file: " << binaryName << endl;
    }
}

void DisplayEmployeeInfo(const vector<Employee>& employees) {
    cout << "INFO:\nNUMBER\tNAME\tHOURS\n";
    for (const auto& employee : employees) {
        cout << employee.num << "\t" << employee.name << "\t" << employee.hours << "\n";
    }
}

void DisplayReport(const string& txtName) {
    ifstream outputName(txtName);
    if (outputName.is_open()) {
        string temporary;
        while (getline(outputName, temporary)) {
            cout << temporary << "\n";
        }
        outputName.close();
    } else {
        cerr << "Error opening report file: " << txtName << endl;
    }
}

int main() {
    string binaryName, txtName, amountOfNotes, payForHour;
    vector<Employee> employees;

    cout << "Enter name of binary file: ";
    cin >> binaryName;
    cout << "Enter amount of notes: ";
    cin >> amountOfNotes;

    Employee emp;

    string creatorExe = "Creator.exe " + binaryName + " " + amountOfNotes;
    wstring creatorToLpwstr(creatorExe.begin(), creatorExe.end());
    LPWSTR lpszCreatorProcess = &creatorToLpwstr[0];
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, lpszCreatorProcess, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cerr << "The Creator process is not running.\n";
        return GetLastError();
    }
    WaitForSingleObject(pi.hProcess, INFINITE);

    ReadBinaryFile(binaryName, employees);
    DisplayEmployeeInfo(employees);

    cout << "Enter name of the report file: ";
    cin >> txtName;
    cout << "Enter pay per hour: ";
    cin >> payForHour;

    string reporterExe = "Reporter.exe " + binaryName + " " + txtName + " " + payForHour;
    wstring reporterToLpwstr(reporterExe.begin(), reporterExe.end());
    LPWSTR lpszReporterProcess = &reporterToLpwstr[0];

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, lpszReporterProcess, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cerr << "The Reporter process is not running.\n";
        return GetLastError();
    }
    WaitForSingleObject(pi.hProcess, INFINITE);

    DisplayReport(txtName);

    TerminateProcess(pi.hProcess, 1);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    cin.get();  
    return 0;
}
