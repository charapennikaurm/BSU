#include <iostream>

using namespace std;

int _declspec (naked) up_triangle(int* array, const int n, const int m)
{
	__asm
	{
		//пролог
		push ebp
		mov ebp,esp
		push ebx
		push esi
		push edi
		//
		mov ebx, n
		imul ebx, m
		cmp ebx, 1
		je end1
		cmp ebx,0
		je end1
		xor eax,eax//переменная для результата
		xor esi,esi//адресная переменная
		mov edx,1//номер строки
		mov ebx,array
		while_begin:
		cmp edx,n
		jg while_end //мы прошли по всем строкам
		add esi,edx //esi на первом в строке элементе который нужно суммировать
		mov ecx,m
		sub ecx,edx
		cmp ecx,0
		jle while_end;//если в последующих строках не будет элементов для суммирования
		sumir:
		add eax,[ebx][esi*4]
		inc esi
		loop sumir
		add edx,1
		jmp while_begin
		end1: 
		 mov eax,0
		while_end:
			 //эпилог
			 pop edi
			 pop esi
			 pop ebx
			 pop ebp
			 ret
	}
}

int u_trian(int* array, const int n, const int m)
{
	__asm
	{
		push m
		push n
		push array
		call up_triangle

		add esp, 0Ch
	}
}

int main()
{
	setlocale(0, "rus");
	cout << "Введите размеры массива n,m: ";
	int n, m;
	cin >> n >> m;
	int* array = new int[n * m];
	int array_size = n * m;
	//ввод матрицы
	for (int i = 0; i < n * m; ++i)
	{
		if (i == 0) { cout << "1 строка: "; }
		cin >> array[i];
		if ((i + 1) % m == 0 && i + 1 != n * m)
		{
			cout << ((i+1)/m)+1<< " строка: ";
		}
	}
	//matrix output
	cout << "==========================================" << endl;
	for (int i = 0; i < n * m; ++i)
	{
		cout << array[i]<< "     ";
		if ((i + 1) % m == 0)
			cout << endl;
	}
	cout << "==========================================";
	cout <<endl<<"Result: "<< u_trian(array, n, m);
}