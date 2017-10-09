;Robert Wooner
;Assignment 8
;CS261

section .text

global	strgt

strgt:
		push ebp
		mov ebp, esp
		push ecx
		push esi
		push edi
		mov ecx, 31
		mov esi, [ebp+8]
		mov edi, [ebp+12]
		mov ecx, 31
		mov eax, 0

top:
		mov bh, [esi+eax]		;index of the string
		mov bl, [edi+eax]		;index of the string
		cmp bh,bl		;(a-b)
		ja true			;if the above statement returns >0 jummp to true
		jb false		;if statement returns <0 jump false
		cmp bh, 10	;checking for new line
		jz false		;jump if new line
		inc eax			;increment counter
		loop  top		;loops back to top and decrements ecx (cl) until 0 
true:
		mov	eax, 1			
		jmp exit

false:
		mov	eax, 0			
		jmp exit

exit:
		pop ecx
		pop edi
		pop	esi
		mov esp, ebp
		pop ebp
		ret


