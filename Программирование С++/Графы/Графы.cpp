/*
				STL простые задачи на графе
	15.	Граф задан набором ориентированных дуг и набором вершин. 
  Найти все вершины, для  которых число исходящих дуг не равно 1
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct edge // дуга графа
{
	edge() :begin(0), end(0) {}
	edge(int _b, int _e) :begin(_b), end(_e) {  }
	friend istream& operator >>( istream& is ,edge& e)
	{
		return is >> e.begin >> e.end;
	}
	int begin;
	int end;
};

struct vertex
{

	vertex() :num(0) {}
	vertex(int _n) :num(_n) {}
	friend istream& operator>>(istream& is, vertex& v)
	{
		return is >> v.num;
	}

	int num;
};

int main()
{
	setlocale(LC_ALL, "rus");
	//вершины считываются из файла "in_vertex.txt", а дуги из "in_edge.txt"
	//результат выводится на консоль
	ifstream inv("in_vertex.txt");
	ifstream ine("in_edge.txt");
	if (!inv) { cout << "Невозможно открыть файл in_vertex.txt"; return 0; }
	if (!ine) { cout << "Невозможно открыть файл in_edge.txt"; return 0; }

	map<int, set<int>> m;
	vector<edge> ev;
	vector<vertex> vv;

	copy(istream_iterator<vertex>(inv), istream_iterator<vertex>(), back_inserter(vv));
	copy(istream_iterator<edge>(ine), istream_iterator<edge>(), back_inserter(ev));

	for_each(ev.begin(), ev.end(), [&m](edge const& e)
		{m[e.begin].insert(e.end); });

	cout << "Вершины, для  которых число исходящих дуг не равно 1:" << endl;;

	for_each(vv.begin(), vv.end(),
		[&m](vertex const& v)
		{
			if (m.find(v.num) == m.end())
				cout << v.num << endl;
			else if (m.find(v.num)->second.size() != 1)
				cout << v.num<< endl;
		}
	);

	return 0;
}