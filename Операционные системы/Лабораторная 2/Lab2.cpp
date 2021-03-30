#include <iostream>
#include <Windows.h>

struct array {
	array(int* arr, int size) :arr(arr), size(size) {};
	int* arr;
	int min = 0;
	int max = 0;
	int average = 0;
	int size;
};

DWORD WINAPI min_max_element(LPVOID arguments) {
	array* pArr = (array*)arguments;
	pArr->max = pArr->min = pArr->arr[0];
	for (int i = 1; i < pArr->size; ++i) {
		if (pArr->max < pArr->arr[i]) {
			pArr->max = pArr->arr[i];
		}
		Sleep(7);
		if (pArr->min > pArr->arr[i]) {
			pArr->min = pArr->arr[i];
		}
		Sleep(7);
	}
	std::cout << "Max element of array: " << pArr->max << "\n";
	std::cout << "Min element of array: " << pArr->min << "\n";
	return 0;
}

DWORD WINAPI average(LPVOID arguments) {
	array* pArr = (array*)arguments;
	for (int i = 0; i < pArr->size; ++i) {
		pArr->average += pArr->arr[i];
		Sleep(12);
	}
	pArr->average = pArr->average / pArr->size;
	std::cout << "Array average: " << pArr->average << "\n";
	return 0;
}

void replace(array* pArr) {
	for (int i = 0; i < pArr->size; ++i) {
		if (pArr->arr[i] == pArr->max || pArr->arr[i] == pArr->min) { pArr->arr[i] = pArr->average; }
	}
}

void print(array* pArr) {
	for (int i = 0; i < pArr->size; ++i) {
		std::cout << pArr->arr[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	int size;
	std::cout << "Enter array size:"; std::cin >> size;
	int* arr = new int[size];
	std::cout << "Enter array elements:";
	for (int i = 0; i < size; ++i) { std::cin >> arr[i]; }

	array* array_struct = new array(arr, size);

	HANDLE hThread_min_max, hThread_average;

	hThread_min_max = CreateThread(NULL, 0, min_max_element, LPVOID(array_struct), NULL, NULL);
	hThread_average = CreateThread(NULL, 0, average, LPVOID(array_struct), NULL, NULL);
	if (hThread_min_max == NULL || hThread_average == NULL) {
		return GetLastError();
	}

	WaitForSingleObject(hThread_min_max, INFINITE); WaitForSingleObject(hThread_average, INFINITE);
	CloseHandle(hThread_min_max); CloseHandle(hThread_average);

	std::cout << std::endl;

	replace(array_struct);
	print(array_struct);

	delete[] arr;
	delete array_struct;

	return 0;
}