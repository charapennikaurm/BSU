#include <iostream>

using namespace std;

int FWord(char* s)
{
	_asm
	{
		//вычисляем длину строки
		cld
		mov edi, s
		mov esi, edi
		mov ecx, 0ffffffffh// максимальное целое 32 битное число
		xor al, al
		repne scasb
		sub edi, esi
		dec edi
		mov ecx, edi//размер строки в ecx
		xor edx, edx
		xor ebx, ebx
		mov edi, s
		cmp ecx,0
		je _end
		loop1 :
		lodsb
			cmp al, ' '
			je probel
			cmp edx, 0
			jne end_if
			inc ebx
			mov edx, 1
			jmp end_if
			probel : mov edx, 0
			end_if :
			loop loop1;
		mov eax, ebx
		jmp end1
		_end: mov eax,0
		end1:
	}
}

int main()
{
	char str[256];
	cin.getline(str, 256);
	cout << "Result: " << FWord(str) << endl;
}