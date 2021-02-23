#include <iostream>
#include <fstream>
#include <string>
#include "../Creator/employee.h"

using namespace std;

int main(int argc, char* argv[]) {
	ifstream in(argv[0],ios::binary);
	ofstream out(argv[1]);
	out << argv[0] << endl;
	out << "Employee number, employee name, hours, salary" << endl;;
	float salary_per_hour = atof(argv[2]);
	employee e;
	while (in.read((char*)&e, sizeof(employee))) {
		out << e.num << " " << e.name << " " << e.hours << " " << e.hours * salary_per_hour<<endl;
	}
	in.close();
	out.close();
	return 0;
}