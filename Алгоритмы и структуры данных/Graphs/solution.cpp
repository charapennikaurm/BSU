#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>
#include<queue>
#include<sstream>

using namespace std;

void graph_matrix(vector<vector<int>>& ms, ifstream& in) {
	int n = ms.size();
	for (int i = 0; i < n; ++i) {
		string str;
		getline(in, str);
		istringstream istr(str);
		int a;
		while (istr >> a) {
			if (a == 0) {
				break;
			}
			ms[i][a - 1] = 1;
		}
	}
}

vector<int> connected_parts(vector<vector<int>> ms) {
	int n = ms.size();
	vector<int> result;
	queue<int> q;
	vector<bool> visited(n, false);
	for (int k = 0; k < ms.size(); ++k) {
		if (visited[k]) {
			continue;
		}
		result.push_back(k);
		q.push(k);
		while (!q.empty()) {
			int i = q.front();
			q.pop();
			for (int j = 0; j < ms.size(); ++j) {
				if (ms[i][j] == 1 && !visited[j]) {
					visited[j] = true;
					q.push(j);
				}
			}
		}
	}
	return result;
}

pair<bool, int> is_bipartite(vector<vector<int>> ms, int start) {
	queue<int> q;
	vector<int> colors(ms.size(), -1);
	colors[start] = 0;
	int part1_size = 1;
	int part2_size = 0;
	q.push(start);
	while (!q.empty()) {
		int i = q.front();
		q.pop();
		for (int j = 0; j < ms.size(); ++j) {
			if (ms[i][j] == 1) {
				if (colors[j] == -1) {
					colors[j] = (colors[i] + 1) % 2;
					if (colors[j] == 0) { part1_size++; }
					else { part2_size++; }
					q.push(j);
				}
				else if(colors[j] == colors[i]){
					return pair<bool, int>(false, 1);
				}
			}
		}
	}
	return pair<bool, int>(true, max(part1_size, part2_size));
}

void odd_even_highway(ifstream& in, ofstream& out) {
	int n;
	in >> n;
	in.ignore();
	vector<vector<int>> ms(n, vector<int>(n, 0));
	graph_matrix(ms, in);
	vector<int> parts = connected_parts(ms);
	if (parts.size() == 1) {
		pair<bool, int> p = is_bipartite(ms, 0);
		if (p.first) {
			out << "NO\n";
			out << p.second;
			return;
		}
		else {
			out << "YES";
			return;
		}
	}
	int answer = 0;
	for (int i : parts) {
		answer += is_bipartite(ms, i).second;
	}
	out << "NO\n";
	out << answer;
}

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	odd_even_highway(in, out);
}