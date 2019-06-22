	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movl	$0, -4(%rbp)
	movq	$1, -16(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpq	$100000, -16(%rbp)      ## imm = 0x186A0
	jge	LBB0_7
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	addq	$100, %rax
	cvtsi2sdq	%rax, %xmm0
	sqrtsd	%xmm0, %xmm0
	cvttsd2si	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	addq	$268, %rax              ## imm = 0x10C
	cvtsi2sdq	%rax, %xmm0
	sqrtsd	%xmm0, %xmm0
	cvttsd2si	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rax
	imulq	-24(%rbp), %rax
	movq	-16(%rbp), %rcx
	addq	$100, %rcx
	cmpq	%rcx, %rax
	jne	LBB0_5
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rax
	imulq	-32(%rbp), %rax
	movq	-16(%rbp), %rcx
	addq	$268, %rcx              ## imm = 0x10C
	cmpq	%rcx, %rax
	jne	LBB0_5
## BB#4:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	L_.str(%rip), %rdi
	movq	-16(%rbp), %rsi
	movb	$0, %al
	callq	_printf
	movl	%eax, -36(%rbp)         ## 4-byte Spill
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_6
LBB0_6:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -16(%rbp)
	jmp	LBB0_1
LBB0_7:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"\n%ld\n"


.subsections_via_symbols
