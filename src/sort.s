	.file	"sort.c"
	.text
	.globl	sort
	.type	sort, @function
sort:
.LFB0:
	.cfi_startproc
	endbr64
	leaq	-8(%rsi), %rax
	cmpq	%rdi, %rax
	jbe	.L18
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsi, %rbp
	movq	%rsi, %rdx
	subq	%rdi, %rdx
	movq	%rdx, %rcx
	sarq	$3, %rcx
	shrq	$63, %rdx
	addq	%rcx, %rdx
	sarq	%rdx
	movq	(%rdi,%rdx,8), %rcx
	movq	%rdi, %rbx
	jmp	.L7
.L11:
	movq	%rsi, (%rbx)
	movq	%rdx, (%rax)
	addq	$8, %rbx
	subq	$8, %rax
	jmp	.L7
.L8:
	leaq	8(%rax), %rsi
	call	sort
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	sort
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L21:
	.cfi_restore_state
	movq	(%rax), %rsi
	cmpq	%rsi, %rcx
	jge	.L11
.L6:
	subq	$8, %rax
	movq	(%rax), %rsi
	cmpq	%rcx, %rsi
	jg	.L6
.L5:
	cmpq	%rbx, %rax
	jnb	.L11
.L7:
	cmpq	%rax, %rbx
	ja	.L8
	movq	(%rbx), %rdx
	cmpq	%rdx, %rcx
	jle	.L21
.L4:
	addq	$8, %rbx
	movq	(%rbx), %rdx
	cmpq	%rcx, %rdx
	jl	.L4
	movq	(%rax), %rsi
	cmpq	%rsi, %rcx
	jl	.L6
	jmp	.L5
.L18:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	.cfi_restore 6
	ret
	.cfi_endproc
.LFE0:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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
