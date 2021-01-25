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
		
		mov ebx,[ebp+16]   ;в ebx количество столбцов
		imul ebx,[ebp+12]
		cmp ebx, 1
		je end1
		cmp ebx,0
		je end1
		xor eax,eax         ;переменная для результата
		xor esi,esi         ;адресная переменная
		mov edx,1           ;номер строки
		mov ebx,[ebp+8]
		while_begin:
		cmp edx,[ebp+12]
		jg while_end        ;мы прошли по всем строкам
		add esi,edx         ;esi на первом в строке элементе который нужно суммировать
		mov ecx,[ebp+16]
		sub ecx,edx
		cmp ecx,0
		jle while_end       ;если в последующих строках не будет элементов для суммирования
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