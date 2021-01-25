//===============================================
//3.Определить статический массив, размер 
//которого равен сумме элементов другого массива.
//===============================================

#include <iostream>

using namespace std;

template<int N>
constexpr int array_sum(const int(&a)[N])
{
	int c = 0;
	for (int i = 0; i < N; ++i)
		 c += a[i];
	return c;
}

int main()
{
	constexpr int a[] = { 1,2,3,4,12,18};
	int arr[array_sum(a)];
	cout << _countof(arr);
	return 0;
}