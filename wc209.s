	.file	"wc209.c"
	.comm	state,4,4
	.section	.rodata
.LC0:
	.string	"wc209.c"
.LC1:
	.string	"0"
	.align 8
.LC2:
	.string	"Error: line %d: unterminated comment\n"
.LC3:
	.string	"%d %d %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -36(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -20(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, state(%rip)
	jmp	.L2
.L7:
	movl	state(%rip), %eax
	cmpl	$1, %eax
	je	.L4
	cmpl	$1, %eax
	jb	.L5
	cmpl	$2, %eax
	je	.L6
	jmp	.L12
.L5:
	leaq	-16(%rbp), %r9
	leaq	-28(%rbp), %r8
	leaq	-32(%rbp), %rcx
	leaq	-36(%rbp), %rdx
	leaq	-20(%rbp), %rsi
	leaq	-24(%rbp), %rax
	subq	$8, %rsp
	leaq	-12(%rbp), %rdi
	pushq	%rdi
	movq	%rax, %rdi
	call	DFA_SPACE
	addq	$16, %rsp
	jmp	.L2
.L4:
	leaq	-16(%rbp), %r9
	leaq	-28(%rbp), %r8
	leaq	-32(%rbp), %rcx
	leaq	-36(%rbp), %rdx
	leaq	-20(%rbp), %rsi
	leaq	-24(%rbp), %rax
	subq	$8, %rsp
	leaq	-12(%rbp), %rdi
	pushq	%rdi
	movq	%rax, %rdi
	call	DFA_WRD
	addq	$16, %rsp
	jmp	.L2
.L6:
	leaq	-16(%rbp), %r9
	leaq	-28(%rbp), %r8
	leaq	-32(%rbp), %rcx
	leaq	-36(%rbp), %rdx
	leaq	-20(%rbp), %rsi
	leaq	-24(%rbp), %rax
	subq	$8, %rsp
	leaq	-12(%rbp), %rdi
	pushq	%rdi
	movq	%rax, %rdi
	call	DFA_CMNT
	addq	$16, %rsp
	jmp	.L2
.L12:
	movl	$__PRETTY_FUNCTION__.2270, %ecx
	movl	$81, %edx
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	__assert_fail
.L2:
	call	getchar
	movl	%eax, -24(%rbp)
	movl	-24(%rbp), %eax
	cmpl	$-1, %eax
	jne	.L7
	movl	state(%rip), %eax
	cmpl	$2, %eax
	jne	.L8
	movl	-12(%rbp), %eax
	leal	1(%rax), %edx
	movq	stderr(%rip), %rax
	movl	$.LC2, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	fprintf
	movl	$1, %edi
	call	exit
.L8:
	movl	-36(%rbp), %eax
	testl	%eax, %eax
	jne	.L9
	movl	$-1, -28(%rbp)
.L9:
	movl	-36(%rbp), %edx
	movl	-32(%rbp), %eax
	movl	-28(%rbp), %ecx
	leal	1(%rcx), %esi
	movl	%edx, %ecx
	movl	%eax, %edx
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L11
	call	__stack_chk_fail
.L11:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	DFA_SPACE
	.type	DFA_SPACE, @function
DFA_SPACE:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	call	__ctype_b_loc
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cltq
	addq	%rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L14
	movl	$0, state(%rip)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$10, %eax
	jne	.L16
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	jmp	.L16
.L14:
	movl	$1, state(%rip)
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-32(%rbp), %rax
	movl	%edx, (%rax)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-48(%rbp), %rax
	movl	$1, (%rax)
.L16:
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	DFA_SPACE, .-DFA_SPACE
	.globl	DFA_WRD
	.type	DFA_WRD, @function
DFA_WRD:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	call	__ctype_b_loc
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cltq
	addq	%rax, %rax
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	andl	$8192, %eax
	testl	%eax, %eax
	je	.L18
	movl	$0, state(%rip)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-48(%rbp), %rax
	movl	$0, (%rax)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$10, %eax
	jne	.L20
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	jmp	.L20
.L18:
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$42, %eax
	jne	.L21
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$47, %eax
	jne	.L21
	movl	$2, state(%rip)
	movq	-40(%rbp), %rax
	movl	(%rax), %edx
	movq	16(%rbp), %rax
	movl	%edx, (%rax)
	jmp	.L20
.L21:
	movl	$1, state(%rip)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	movq	-48(%rbp), %rax
	movl	$0, (%rax)
.L20:
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	DFA_WRD, .-DFA_WRD
	.globl	DFA_CMNT
	.type	DFA_CMNT, @function
DFA_CMNT:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	movq	%r8, -40(%rbp)
	movq	%r9, -48(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$47, %eax
	jne	.L23
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$42, %eax
	jne	.L23
	movl	$0, state(%rip)
	movq	-48(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	je	.L25
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	leal	-1(%rax), %edx
	movq	-32(%rbp), %rax
	movl	%edx, (%rax)
	movq	-48(%rbp), %rax
	movl	$0, (%rax)
	jmp	.L25
.L23:
	movl	$2, state(%rip)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$10, %eax
	jne	.L25
	movq	-40(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.L25:
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movq	-16(%rbp), %rax
	movl	%edx, (%rax)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	DFA_CMNT, .-DFA_CMNT
	.section	.rodata
	.type	__PRETTY_FUNCTION__.2270, @object
	.size	__PRETTY_FUNCTION__.2270, 5
__PRETTY_FUNCTION__.2270:
	.string	"main"
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
