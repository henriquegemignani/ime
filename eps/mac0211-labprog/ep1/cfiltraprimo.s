	.file	"cfiltraprimo.c"
	.text
	.p2align 4,,15
.globl verifica_primo
	.type	verifica_primo, @function
verifica_primo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movzwl	8(%ebp), %eax
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	cmpw	$1, %ax
	jbe	.L2
	movzwl	%ax, %ebx
	testb	$1, %bl
	je	.L2
	cmpw	$2, %ax
	je	.L3
	cmpl	$8, %ebx
	.p2align 4,,3
	.p2align 3
	jle	.L3
	movl	$1431655766, %edx
	movl	%ebx, %eax
	imull	%edx
	movl	$3, %edi
	movl	$9, %ecx
	leal	(%edx,%edx,2), %edx
	cmpl	%edx, %ebx
	jne	.L4
	jmp	.L2
	.p2align 4,,7
	.p2align 3
.L5:
	movl	%ebx, %edx
	movl	%ebx, %eax
	sarl	$31, %edx
	idivl	%edi
	testl	%edx, %edx
	je	.L2
.L4:
	addl	$2, %edi
	leal	(%ecx,%edi,2), %ecx
	cmpl	%ecx, %ebx
	jge	.L5
.L3:
	movl	$1, %eax
	jmp	.L6
	.p2align 4,,7
	.p2align 3
.L2:
	xorl	%eax, %eax
.L6:
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	8(%esp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.size	verifica_primo, .-verifica_primo
	.p2align 4,,15
.globl le_numero
	.type	le_numero, @function
le_numero:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	xorl	%ebx, %ebx
	subl	$16, %esp
	movl	8(%ebp), %esi
	jmp	.L10
	.p2align 4,,7
	.p2align 3
.L14:
	cmpl	$57, %eax
	jg	.L11
	movzwl	%bx, %eax
	leal	(%eax,%eax,4), %eax
	leal	-48(%edx,%eax,2), %ebx
.L10:
	movl	%esi, (%esp)
	call	fgetc
	cmpl	$47, %eax
	movl	%eax, %edx
	jg	.L14
.L11:
	addl	$16, %esp
	movl	%ebx, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	le_numero, .-le_numero
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"r"
.LC1:
	.string	"w"
.LC2:
	.string	"%hu "
	.text
	.p2align 4,,15
.globl filtra_os_primos
	.type	filtra_os_primos, @function
filtra_os_primos:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movzwl	8(%ebp), %eax
	movl	$.LC0, 4(%esp)
	movw	%ax, -22(%ebp)
	movzwl	12(%ebp), %eax
	movw	%ax, -24(%ebp)
	movl	16(%ebp), %eax
	movl	%eax, (%esp)
	call	fopen
	movl	$.LC1, 4(%esp)
	movl	%eax, %esi
	movl	20(%ebp), %eax
	movl	%eax, (%esp)
	call	fopen
	movl	$0, -16(%ebp)
	movl	%eax, -20(%ebp)
	.p2align 4,,7
	.p2align 3
.L27:
	movl	%esi, (%esp)
	call	feof
	testl	%eax, %eax
	jne	.L22
.L29:
	xorl	%ebx, %ebx
	jmp	.L23
	.p2align 4,,7
	.p2align 3
.L28:
	cmpl	$57, %eax
	.p2align 4,,5
	.p2align 3
	jg	.L17
	movzwl	%bx, %eax
	leal	(%eax,%eax,4), %eax
	leal	-48(%edx,%eax,2), %ebx
.L23:
	movl	%esi, (%esp)
	call	fgetc
	cmpl	$47, %eax
	movl	%eax, %edx
	jg	.L28
.L17:
	cmpw	%bx, -22(%ebp)
	ja	.L27
	cmpw	%bx, -24(%ebp)
	.p2align 4,,3
	.p2align 3
	jb	.L27
	cmpw	$1, %bx
	.p2align 4,,5
	.p2align 3
	jbe	.L27
	movzwl	%bx, %edi
	testl	$1, %edi
	.p2align 4,,3
	.p2align 3
	je	.L27
	cmpw	$2, %bx
	.p2align 4,,3
	.p2align 3
	je	.L19
	cmpl	$8, %edi
	.p2align 4,,3
	.p2align 3
	jle	.L19
	movl	$1431655766, %eax
	movl	$9, %ecx
	imull	%edi
	movl	$3, -28(%ebp)
	leal	(%edx,%edx,2), %edx
	cmpl	%edx, %edi
	jne	.L20
	jmp	.L27
	.p2align 4,,7
	.p2align 3
.L21:
	movl	%edi, %edx
	movl	%edi, %eax
	sarl	$31, %edx
	idivl	-28(%ebp)
	testl	%edx, %edx
	je	.L27
.L20:
	addl	$2, -28(%ebp)
	movl	-28(%ebp), %eax
	leal	(%ecx,%eax,2), %ecx
	cmpl	%ecx, %edi
	jge	.L21
.L19:
	movl	-20(%ebp), %eax
	movl	%edi, 8(%esp)
	movl	$.LC2, 4(%esp)
	movl	%eax, (%esp)
	call	fprintf
	addl	$1, -16(%ebp)
	movl	%esi, (%esp)
	call	feof
	testl	%eax, %eax
	je	.L29
.L22:
	movl	%esi, (%esp)
	call	fclose
	movl	-20(%ebp), %eax
	movl	%eax, (%esp)
	call	fclose
	movl	-16(%ebp), %eax
	addl	$28, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	filtra_os_primos, .-filtra_os_primos
	.ident	"GCC: (Debian 4.3.2-1.1) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
