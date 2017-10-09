	.file	"cgcd.c"
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.rodata
.LC0:
	.string	"Bad Number.\n"
	.text
.globl getInt
	.type	getInt, @function
getInt:
.LFB0:
	.file 1 "cgcd.c"
	.loc 1 7 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 8 0
	movl	$1, -24(%ebp)
	.loc 1 9 0
	movl	$0, -20(%ebp)
	.loc 1 10 0
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	.loc 1 11 0
	jmp	.L2
.L3:
	addl	$1, -16(%ebp)
.L2:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$10, %al
	jne	.L3
	.loc 1 12 0
	subl	$1, -16(%ebp)
	.loc 1 13 0
	jmp	.L4
.L9:
	.loc 1 14 0
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$32, %al
	je	.L11
.L5:
	.loc 1 15 0
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$47, %al
	jle	.L7
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$57, %al
	jle	.L8
.L7:
.LBB2:
	.loc 1 16 0
	movl	$.LC0, -12(%ebp)
	.loc 1 17 0
	movl	$12, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	write
	.loc 1 18 0
	movl	$0, (%esp)
	call	exit
.L8:
.LBE2:
	.loc 1 22 0
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$48, %eax
	imull	-24(%ebp), %eax
	addl	%eax, -20(%ebp)
	.loc 1 23 0
	movl	-24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -24(%ebp)
	.loc 1 24 0
	subl	$1, -16(%ebp)
.L4:
	.loc 1 13 0
	movl	-16(%ebp), %eax
	cmpl	8(%ebp), %eax
	jae	.L9
	jmp	.L6
.L11:
	.loc 1 14 0
	nop
.L6:
	.loc 1 26 0
	movl	-20(%ebp), %eax
	.loc 1 27 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	getInt, .-getInt
.globl makeDecimal
	.type	makeDecimal, @function
makeDecimal:
.LFB1:
	.loc 1 29 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	.loc 1 32 0
	movl	8(%ebp), %ecx
	movl	$-858993459, %edx
	movl	%ecx, %eax
	mull	%edx
	shrl	$3, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%ecx, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%ebp)
	.loc 1 33 0
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	$-858993459, %edx
	movl	-28(%ebp), %eax
	mull	%edx
	movl	%edx, %eax
	shrl	$3, %eax
	movl	%eax, -12(%ebp)
	.loc 1 34 0
	cmpl	$0, -12(%ebp)
	je	.L13
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	makeDecimal
.L13:
	.loc 1 35 0
	movl	-16(%ebp), %eax
	addl	$48, %eax
	movb	%al, -17(%ebp)
	.loc 1 36 0
	movl	$1, 8(%esp)
	leal	-17(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	write
	.loc 1 37 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	makeDecimal, .-makeDecimal
	.section	.rodata
.LC1:
	.string	"Enter a positive integer: "
	.text
.globl readNumber
	.type	readNumber, @function
readNumber:
.LFB2:
	.loc 1 39 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$56, %esp
	.loc 1 41 0
	movl	$.LC1, -12(%ebp)
	.loc 1 42 0
	movl	$26, 8(%esp)
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	write
	.loc 1 43 0
	movl	$20, 8(%esp)
	leal	-32(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	read
	.loc 1 44 0
	leal	-32(%ebp), %eax
	movl	%eax, (%esp)
	call	getInt
	.loc 1 45 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	readNumber, .-readNumber
.globl gcd
	.type	gcd, @function
gcd:
.LFB3:
	.loc 1 47 0
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	.loc 1 48 0
	movl	8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jbe	.L18
	.loc 1 49 0
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	subl	%eax, %edx
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	gcd
	jmp	.L19
.L18:
	.loc 1 50 0
	movl	8(%ebp), %eax
	cmpl	12(%ebp), %eax
	jae	.L20
	.loc 1 51 0
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	gcd
	jmp	.L19
.L20:
	.loc 1 52 0
	movl	8(%ebp), %eax
.L19:
	.loc 1 53 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	gcd, .-gcd
.Letext0:
	.section	.debug_info
	.long	0x1a6
	.value	0x3
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF21
	.byte	0xc
	.long	.LASF22
	.long	.LASF23
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF0
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF1
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF8
	.uleb128 0x4
	.byte	0x4
	.long	0x71
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x5
	.byte	0x1
	.long	.LASF24
	.byte	0x1
	.byte	0x7
	.byte	0x1
	.long	0x33
	.long	.LFB0
	.long	.LFE0
	.byte	0x1
	.byte	0x9c
	.long	0xe4
	.uleb128 0x6
	.long	.LASF14
	.byte	0x1
	.byte	0x7
	.long	0x6b
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x7
	.long	.LASF10
	.byte	0x1
	.byte	0x8
	.long	0x33
	.byte	0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x7
	.long	.LASF11
	.byte	0x1
	.byte	0x9
	.long	0x33
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0x7
	.long	.LASF12
	.byte	0x1
	.byte	0xa
	.long	0x6b
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x8
	.long	.LBB2
	.long	.LBE2
	.uleb128 0x7
	.long	.LASF13
	.byte	0x1
	.byte	0x10
	.long	0x6b
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.byte	0x1
	.long	.LASF17
	.byte	0x1
	.byte	0x1d
	.byte	0x1
	.long	.LFB1
	.long	.LFE1
	.byte	0x1
	.byte	0x9c
	.long	0x132
	.uleb128 0xa
	.string	"n"
	.byte	0x1
	.byte	0x1d
	.long	0x33
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0x20
	.long	0x33
	.byte	0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x7
	.long	.LASF16
	.byte	0x1
	.byte	0x21
	.long	0x33
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x7
	.long	.LASF12
	.byte	0x1
	.byte	0x23
	.long	0x71
	.byte	0x2
	.byte	0x91
	.sleb128 -25
	.byte	0x0
	.uleb128 0xb
	.byte	0x1
	.long	.LASF18
	.byte	0x1
	.byte	0x27
	.long	0x4f
	.long	.LFB2
	.long	.LFE2
	.byte	0x1
	.byte	0x9c
	.long	0x169
	.uleb128 0x7
	.long	.LASF19
	.byte	0x1
	.byte	0x28
	.long	0x169
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x7
	.long	.LASF20
	.byte	0x1
	.byte	0x29
	.long	0x6b
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0x0
	.uleb128 0xc
	.long	0x71
	.long	0x179
	.uleb128 0xd
	.long	0x33
	.byte	0x13
	.byte	0x0
	.uleb128 0xe
	.byte	0x1
	.string	"gcd"
	.byte	0x1
	.byte	0x2f
	.byte	0x1
	.long	0x33
	.long	.LFB3
	.long	.LFE3
	.byte	0x1
	.byte	0x9c
	.uleb128 0xa
	.string	"n"
	.byte	0x1
	.byte	0x2f
	.long	0x33
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xa
	.string	"m"
	.byte	0x1
	.byte	0x2f
	.long	0x33
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.byte	0x0
	.byte	0x0
	.section	.debug_abbrev
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0x6
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x7
	.uleb128 0x34
	.byte	0x0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x8
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0x0
	.byte	0x0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0xb
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0x0
	.byte	0x0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0x0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0x0
	.byte	0x0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,"",@progbits
	.long	0x40
	.value	0x2
	.long	.Ldebug_info0
	.long	0x1aa
	.long	0x78
	.string	"getInt"
	.long	0xe4
	.string	"makeDecimal"
	.long	0x132
	.string	"readNumber"
	.long	0x179
	.string	"gcd"
	.long	0x0
	.section	.debug_pubtypes,"",@progbits
	.long	0xe
	.value	0x2
	.long	.Ldebug_info0
	.long	0x1aa
	.long	0x0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.value	0x0
	.value	0x0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0x0
	.long	0x0
	.section	.debug_str,"MS",@progbits,1
.LASF14:
	.string	"string"
.LASF2:
	.string	"unsigned int"
.LASF0:
	.string	"unsigned char"
.LASF10:
	.string	"digitValue"
.LASF21:
	.string	"GNU C 4.4.7 20120313 (Red Hat 4.4.7-17)"
.LASF22:
	.string	"cgcd.c"
.LASF20:
	.string	"prompt"
.LASF3:
	.string	"long unsigned int"
.LASF15:
	.string	"remainder"
.LASF7:
	.string	"long long unsigned int"
.LASF19:
	.string	"data"
.LASF13:
	.string	"errorMessage"
.LASF23:
	.string	"/Network/Servers/fs.labs.encs/Volumes/raid2/users_b/woobear/Desktop/SchoolStuff/currAss/Gcd"
.LASF9:
	.string	"char"
.LASF18:
	.string	"readNumber"
.LASF11:
	.string	"result"
.LASF8:
	.string	"long int"
.LASF5:
	.string	"short int"
.LASF6:
	.string	"long long int"
.LASF1:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF12:
	.string	"digit"
.LASF24:
	.string	"getInt"
.LASF17:
	.string	"makeDecimal"
.LASF16:
	.string	"quotient"
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-17)"
	.section	.note.GNU-stack,"",@progbits
