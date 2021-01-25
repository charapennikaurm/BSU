#include <iostream>

using namespace std;

void merge(int a[], int start_index, int end_index)
{
	int size = end_index - start_index + 1;
	int* b = new int[size];
	int mid_index = (start_index + end_index) / 2;
	int k = 0;
	int i = start_index;
	int j = mid_index + 1;
	while (k < size)
	{
		while ((i <= mid_index) && (j <= end_index))
		{
			if (a[i] < a[j]) { b[k++] = a[i++]; }
			else { b[k++] = a[j++]; }
		}
		while (i <= mid_index) { b[k++] = a[i++]; }
		while (j <= end_index) { b[k++] = a[j++]; }
	}
	for (k = 0; k < size; k++)
	{
		a[start_index + k] = b[k];
	}

	delete[]b;


}

void merge_sort(int a[], int start_index, int end_index)
{
	if (start_index == end_index) { return; }
	int mid_index = (start_index + end_index) / 2;
	merge_sort(a, start_index, mid_index);
	merge_sort(a, mid_index + 1, end_index);
	merge(a, start_index, end_index);
}

int main()
{
	setlocale(0, "rus");
	cout << "Введите число элементов массива: ";
	int n;
	cin >> n;
	int* a = new int[n];
	cout << "Введите элементы массива: ";
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	cout << endl << "Неотосортированный массив: " << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl << "Oтcортированный массив: " << endl;
	merge_sort(a, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " ";
	}
	delete[] a;
	return 0;
}
