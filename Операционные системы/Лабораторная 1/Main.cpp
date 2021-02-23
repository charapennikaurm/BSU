#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "..//Creator/employee.h"

using namespace std;


void start_creator(string binary_file_name, int number_of_employees) {
	const char* app_name = "Creator.exe";
	string arguments = binary_file_name + " " + to_string(number_of_employees);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	CreateProcess(app_name, (char*)arguments.c_str(), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void start_reporter(string binary_file_name, string report_file_name, double salary_per_hour) {
	const char* app_name = "Reporter.exe";
	string arguments = binary_file_name + " " + report_file_name + " " + to_string(salary_per_hour);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	CreateProcess(app_name,// имя исполняемого модуля
		(char*)arguments.c_str(),// комадная строка
		NULL,// защита процесса
		NULL,// защита потока
		FALSE,// признак наследования дескриптора
		CREATE_NEW_CONSOLE,// флаги создания процесса
		NULL,// блок новой среды окружения
		NULL,// текущий католог
		&si,// вид главного окна
		&pi// информация о процессе
	);

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

int main() {
	string binary_file_name, report_file_name;
	int number_of_employees;
	double salary_per_hour;
	cout << "Enter binary file name: ";
	cin >> binary_file_name;
	cout << "Enter number of employees: ";
	cin >> number_of_employees;
	cout << endl;
	start_creator(binary_file_name, number_of_employees);
	ifstream in(binary_file_name, ios::binary);
	employee e;
	while (in.read((char*)&e, sizeof(employee))) {
		cout << e.num << " " << e.name << " " << e.hours << endl;
	}
	cout << endl;
	in.close();
	cout << "Enter report file name: ";
	cin >> report_file_name;
	cout << "Enter slary per hour:";
	cin >> salary_per_hour;
	cout << endl;
	start_reporter(binary_file_name, report_file_name, salary_per_hour);
	string info;
	in.open(report_file_name);
	while (getline(in,info)) {
		cout << info << endl;
	}
	system("pause");
	return 0;
}