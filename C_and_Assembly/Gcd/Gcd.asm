;Robert Wooner
;Final Project
;CS 261
; main and puts functions were given to us by Dr. Dick Lang 
section     .data
    pmpt:   db "Enter positive integer: "
    plen:   equ $-pmpt

    outpt: db "Greatest common divisor: "
    outlen: equ $-outpt
		
		error:  db "These are bad Numbers"
		erlen:	equ $-error

    newln:  db 10
section  .bss
		inbuff: resd 20
		remain: resd 1
section     .text
    global      _start
		global			getInt
    global      readNumber
    global      gcd
    global      makeDecimal

; ***************** 
;puts(string address, char count) 
; *****************
puts:   
    push    ebp
    mov     ebp, esp
    push    eax
    push    ebx
    push    ecx
    push    edx
    
    mov     ecx, [ebp+8]
    mov     edx, [ebp+12]
    mov     eax, 4
    mov     ebx, 1
    int     80H

    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    mov     esp, ebp
    pop     ebp
    ret

; ************** 
;  gcd()
; **************


gcd:
		push	ebp
		mov		ebp, esp
		push	ecx
		push	edx
		mov		ecx, [ebp+8] ; this is n
		mov		edx, [ebp+12] ; this is m
		jmp		gcdStart

gcdStart: 
		cld
		cmp		ecx, edx
		ja		one
		jb		two
		mov		eax, ecx
		jmp   Base

one:
		sub		ecx, edx  ;n-m
		push	edx
		push	ecx
		call	gcd			;restart
		add		esp, 8
		jmp		Base

two:
		sub		edx, ecx  ;m-n
		push	edx
		push	ecx
		call	gcd			;restart
		add		esp, 8
		jmp		Base

Base:
		pop		edx
		pop		ecx
		pop		ebx
		mov		esp, ebp
		pop		ebp
		ret

; ************** 
;  readNumber()
; **************

readNumber:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    ecx
    push    edx
    
    mov     eax, 4 ;writes
    mov     ebx, 1 
    mov     ecx, pmpt
    mov     edx, plen
    int     80H

    mov     eax, 3		;reads
    mov     ebx, 0 
    mov     ecx, inbuff
    mov     edx, 21
    int     80H
		
		push		inbuff   ;pushes input
		call		getInt		; calls getInt on the input
		add			esp, 4

    pop     edx
    pop     ecx
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret
	
		
; **************************
;  getInt(char* string)
; **************************
getInt:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    ecx
    push    edx
    push    esi
		push		edi

		
		mov			ebx, 1
		mov			edx, 0
		mov			esi, [ebp+8]
		mov			edi, [ebp+8]
	
firstLoop:
	
		mov			al, byte [esi]    ; counts how many digits there are in the string 
		cmp			al, 10
		je			calc							; jumps to calc if its the end 
		inc			esi
		jmp			firstLoop        ;jumps back til the end of the string 

calc:
		dec			esi							;counts backwards for the amount of numbers in the sting 
		movzx		eax, byte [esi]   ;moves the byte into eax while filling the rest with zeros
		cmp			esi, edi				; compares to see if its the first position
		jb			Last
		cmp			al, 32					; sees if its a space
		je			Last
		cmp			al, 48					;sees if its less than '0'
		jl			errorM
		cmp			al, 57					;sees if its greater '9'
		jg			errorM
		sub		  al, '0'
		imul		eax, ebx
		add			edx, eax
		imul		ebx, 10
		jmp		  calc

errorM:
		mov     eax, 4		;writes error message
		mov     ebx, 1 
		mov     ecx, error
		mov     edx, erlen
		int     80H

		mov     eax, 4		;writes new line
		mov     ebx, 1 
		mov     ecx, newln
		mov     edx, 10
		int     80H
		
		add			esp, 8
		mov			eax, 1
		mov			ebx, 0
		int			80H

Last:
		mov			eax, edx 
		pop		  edi
		pop			esi
    pop     ecx
    pop     ebx
    mov     esp, ebp
    pop     ebp
    ret


; **************************
;  MakeDecimal(unsigned int)
; **************************

makeDecimal:

    push    ebp
    mov     ebp, esp
    push    eax
    push    edx
		push		ecx
		
		mov			ecx, 10		; moves 10 into eax
		mov			eax, [ebp+8]   ;moves the unsigned int into edx
		mov			edx, 0				;sets edx to 0
		div			dword ecx            ; divides ecx by eax
		cmp			eax, 0				;compares eax (qotient with zero
		ja			recurse				;if greater then zero jump to recurse function
		jmp			End

End:		
		add			edx, '0'      ; adds '0' to edx (remainder)
		mov			[remain], edx
		push		dword 1				;push room for on the stack
		push		dword remain			;push the number on the stack
		call		puts					;call put which writes the number
		add			esp, 8				;clear the stack
		pop			ecx						
		pop			edx
		pop			eax
		mov			esp, ebp 
		pop			ebp
		ret

recurse:
		push	 eax
		call	 makeDecimal	
		pop		 eax
		jmp		 End


; ************** 
; main program 
; **************

_start: 
    call    readNumber
    mov     esi, eax 
    call    readNumber
    push    eax
    push    esi
    call    gcd
    add     esp, 8
    push    dword outlen
    push    dword outpt
    call    puts

    push    eax
    call    makeDecimal
    add     esp, 4
    push    dword 1
    push    dword newln
    call    puts
    add     esp, 8
    mov     eax, 1
    mov     ebx, 0
    int     80H
