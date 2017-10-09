;Robert Wooner
;Assignment 7
;CS261

; This code is an ISBN Calculater using 11 digits instead of 10.
;this program ranks each number in the numbers (1-10) multiplies each rank by their digit and adds them together
;then divides them by 11 and compares it to ten and as long as its not zero it will add a new digit 
;if it is zero then it will add an "X" 
SECTION	.data

prompt:	db		"Enter 10 digits: "
plen:	equ		$-prompt

SECTION	.bss
	
digits:	equ		10
inbuf:	resb	digits + 2

SECTION	.text

global	_start

_start:
		nop
		mov		eax, 4			; write
		mov		ebx, 1			; to standard output
		mov		ecx, prompt		; the prompt string
		mov		edx, plen		; of length plen
		int 	80H				; interrupt with the syscall

		mov		eax, 3			; read
		mov		ebx, 0			; from standard input
		mov		ecx, inbuf		; into the input buffer
		mov		edx, digits+1		; upto digits + 1 bytes
		int 	80H				; interrupt with the syscall

		cld  ; clear direction flag (df =0) increments loop
		mov     esi, inbuf  ;moves inbuf to source index register(pointer register)
		mov     ecx, digits ; moves 10  counter register (loop indexes)
		mov     dx, 0 ;set dx register (16 bit) to 0
top:
<<<<<<< HEAD:currAss/asm2/mystery.asm
		lodsb     ; load string byte 
		sub     al, '0' ;subtracts 0(ascii value)  from al
		mul	cl     ;multiplies al and cl and places it in ax
		add	dx, ax  ;adds ax to dx 
		loop    top  ; loops back to top and decrements ecx until 0 
		mov     ax, dx ;moves contents of dx to ax
		mov     cl, 11 ; sets cl to 11
		div     cl    ;divides ax by cl
		mov     al, ah ;moves ah to al 
		cmp	al, 10     ; compares al and 10 (al - 10)
		jnz	makeDigit ;jumps to make "makeDigit" if the result of cmp is not zero
		mov	al, 'X' ; moves X to al 
		jmp	storeDigit  ;jump to "storeDigit"
makeDigit:	add	al, '0'  ;adds 0 to al register
storeDigit:	mov	[inbuf+10], al ;stores the new digit
		mov	byte	[inbuf+11], 10 ;10 on the end
=======
		lodsb			 ; load string byte 
		sub     al, '0'	 ;subtracts 0(ascii value)  from al
		mul	cl			 ;multiplies al and cl and places it in ax
		add	dx, ax	 ;adds ax to dx 
		loop    top		 ; loops back to top and decrements ecx (cl) until 0 
		mov     ax, dx	;moves contents of dx to ax
		mov     cl, 11	; sets cl to 11
		div     cl			;divides ax by cl
		mov     al, ah	;moves ah to al 
		cmp	al, 10			; compares al and 10 (al - 10)
		jnz	makeDigit		;jumps to make "makeDigit" if the result of cmp is not zero
		mov	al, 'X'		; moves X to al 
		jmp	storeDigit	 ;jump to "storeDigit"
makeDigit:	add	al, '0'	  ;adds 0 to al register
storeDigit:	mov	[inbuf+10], al	;stores the new digit
		mov	byte	[inbuf+11], 10	;10 on the end
>>>>>>> 2f93262cad837a7e1bcb91c6389d5b3ff1b5ed24:pastAss/asm2/mystery.asm

		mov	eax, 4				; write
		mov	ebx, 1				; to standard output
		mov	ecx, inbuf			; the string in the buffer
		mov	edx, digits+2			; of length digits+2
		int 	80H				; interrupt with the syscall

		mov eax, 1				; set up process exit
		mov ebx, 0				; and
		int	80H				; terminate


