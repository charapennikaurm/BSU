.386
.model flat
.data
.code
PUBLIC _AsmModule
_AsmModule PROC
push ebp
mov ebp,esp

push ebx
		push esi
		push edi
		
		mov ebx,[ebp+16]   ;� ebx ���������� ��������
		imul ebx,[ebp+12]
		cmp ebx, 1
		je end1
		cmp ebx,0
		je end1
		xor eax,eax         ;���������� ��� ����������
		xor esi,esi         ;�������� ����������
		mov edx,1           ;����� ������
		mov ebx,[ebp+8]
		while_begin:
		cmp edx,[ebp+12]
		jg while_end        ;�� ������ �� ���� �������
		add esi,edx         ;esi �� ������ � ������ �������� ������� ����� �����������
		mov ecx,[ebp+16]
		sub ecx,edx
		cmp ecx,0
		jle while_end       ;���� � ����������� ������� �� ����� ��������� ��� ������������
		sumir:
		add eax,[ebx][esi*4]
		inc esi
		loop sumir
		add edx,1
		jmp while_begin
		end1: 
		 mov eax,0
		while_end:
			 pop edi
			 pop esi
			 pop ebx
			 mov esp,ebp
			 pop ebp

ret
_AsmModule endp

end