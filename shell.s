	.file	"shell.c"
	.text
	.section	.rodata
.LC0:
	.string	" \n"
.LC1:
	.string	"Error"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movl	%edi, -84(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -68(%rbp)
	movq	$0, -40(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -32(%rbp)
	movq	$0, -48(%rbp)
.L6:
	movq	stdin(%rip), %rdx
	leaq	-56(%rbp), %rcx
	leaq	-48(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	getline@PLT
	movq	%rax, -40(%rbp)
	cmpq	$-1, -40(%rbp)
	jne	.L2
	movl	$0, %edi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L7
.L2:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	copy_buffer@PLT
	movq	%rax, -24(%rbp)
	movq	-48(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	tokenize@PLT
	movl	%eax, -64(%rbp)
	movl	-64(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L4
	movl	$1, %eax
	jmp	.L7
.L4:
	movl	-64(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	buff_split@PLT
	movq	%rax, -16(%rbp)
	call	fork@PLT
	movl	%eax, -60(%rbp)
	cmpl	$0, -60(%rbp)
	jne	.L5
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-104(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	execve@PLT
	movl	%eax, -68(%rbp)
	cmpl	$-1, -68(%rbp)
	jne	.L5
	leaq	.LC1(%rip), %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L7
.L5:
	movl	$0, %edi
	call	wait@PLT
	cmpq	$-1, -40(%rbp)
	jne	.L6
	movl	$0, %eax
.L7:
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L8
	call	__stack_chk_fail@PLT
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
