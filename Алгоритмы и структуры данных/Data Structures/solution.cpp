#include<fstream>
#include<queue>
#include<algorithm>
#include<sstream>
#include<iostream>
#include<vector>
#pragma GCC optimaze ("O3")
using namespace std;

void black_box(std::istream& in, std::ostream& out) {
	priority_queue<int> get;
	priority_queue<int,std::vector<int>, std::greater<int>> added;
	int n;//число запросов получить
	int m;//число элементов
	in >> m; in >> n;
	vector<int> elements(m);
	for (int i = 0; i < m; ++i) {
		in >> elements[i];
	}
	int querry;
	in >> querry;
	while (true) {
		int size = get.size() + added.size();
		for (int i = 0; i < querry - size; ++i) {
			if (!get.empty()) {
				if (elements[size + i] < get.top()) {
					get.push(elements[size + i]);
					added.push(get.top());
					get.pop();
				}
				else {
					added.push(elements[size + i]);
				}
			}
			else {
				added.push(elements[size + i]);
			}
		}
		if (in >> querry) {
			out << added.top()<< " ";
		}
		else {
			out << added.top();
			break;
		}
		get.push(added.top());
		added.pop();
	}
}

int main() {
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
	std::ifstream file_in("input.txt");
	std::ofstream file_out("output.txt");
	black_box(file_in, file_out);
	return 0;
}