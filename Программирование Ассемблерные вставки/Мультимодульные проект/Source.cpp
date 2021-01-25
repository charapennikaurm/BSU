#include <iostream>

using namespace std;

extern "C" int AsmModule(int* array, const int n, const int m);

int main()
{
	setlocale(0, "rus");
	cout << "¬ведите размеры матрицы n,m: ";
	int n, m;
	cin >> n >> m;
	int* array = new int[n * m];
	int array_size = n * m;
	for (int i = 0; i < n * m; ++i)
	{
		if (i == 0) { cout << "1 строка: "; }
		cin >> array[i];
		if ((i + 1) % m == 0 && i + 1 != n * m)
		{
			cout << ((i + 1) / m) + 1 << " строка: ";
		}
	}
	cout << "==========================================" << endl;
	for (int i = 0; i < n * m; ++i)
	{
		cout << array[i] << "     ";
		if ((i + 1) % m == 0)
			cout << endl;
	}
	cout << "==========================================";
	int x = AsmModule(array, n, m);
	cout << endl << "–езультат: " << x;
}
