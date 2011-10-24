;/*******************************************************************/
;/** MAC0211 - Laboratorio de Programacao                          **/
;/** IME-USP - Primeiro Semestre de 2010                           **/
;/**                                                               **/
;/** Primeiro Exercicio-Programa -- Linguagem de Montagem          **/
;/** Arquivo: filtra.asm                                           **/
;/**                                                               **/
;/** Henrique Gemignani Passos Lima         nUSP: 6879634          **/
;/** Renan Teruo Carneiro                   nUSP: 6514157          **/
;/** 31/03/2010                                                    **/
;/*******************************************************************/

segment .bss
buf     resb  6 		;buffer

section .text 			; SECTION DO LE NUMERO

le_numero:
	;; push no que vai estragar
	push	edx
	push	ecx

	;; eax == RESULT, e zera
	xor	eax, eax

looplenumero:
	call	limpabuf
	push 	eax

	;; chamando SYS_READ, o que ler vai para buf
	mov 	edx, 1
	mov	ecx, buf
	mov	eax, 3		;ebx ja vai estar certo, OR ELSE!
	int 	0x80

	mov	ecx, eax 	;POG
	pop	eax

	or	ecx, ecx	; verifica se leu alguma coisa
	jz	retornafim	; acabou o arquivo
	
	mov 	ecx, [buf]
	sub	ecx, '0'        ; colocando em EAX o caracter lido e ajustando para o valor numerico

	cmp	ecx, 9
	ja	retornanumero	; non e numero


	mov	edx, 10
	mul	edx
	add	eax, ecx

	jmp	looplenumero
	
retornanumero:
	pop 	ecx
	pop 	edx

	ret

retornafim:
	or	eax, eax
	jnz	retornanumero
	pop 	ecx	
	pop 	edx
	mov 	eax, -1
	;; 	neg	eax         ; devolve ultimo numero sendo negativo
	ret



section .bss
temp	resb	4		; variavel temporaria

section .text
	
verifica_primo:
	push	ebx
	push 	ecx		; guarda o que vamos estragar
	push	edx

	mov	[temp], eax	; guarda na RAM o numero que estamos verificando

	cmp	eax, 2
	jb	verifica_naoeh	; 0 e 1 nao sao primos

	cmp	eax, 3
	jbe	verifica_eh	; 2 ou 3 eh primo!

	test	eax, 1
	jz	verifica_naoeh

	mov	ebx, 3		; B = 3
	mov	ecx, 9		; C = B*B = 9
	xor	dx, dx		; div usa DX:AX para dividir por 16 bits. Isso so atrapalha a vida.

verifica_loop:
	;; for B = 3; B*B <= A; B += 2
	;;   if( A % B == 0 ) nao eh primo
	;; terminando o for, A eh primo
	div	bx
	and	dx, dx
	jz	verifica_naoeh

	inc	ebx
	add	ecx, ebx	; C = B*B = (B1+2)*(B1+2)
	add	ecx, ebx	; C = B*B + 4*( B1 + 1 )
	add	ecx, ebx
	add	ecx, ebx
	inc	ebx		; B = B + 2

	cmp	ecx, [temp]
	ja	verifica_eh 	; B*B > A

	mov	eax, [temp]
	
	jmp	verifica_loop

verifica_eh:
	pop	edx
	pop	ecx
	pop	ebx
	mov	eax, [temp]
	jmp 	numero_e_primo

verifica_naoeh:
	;; numero nao eh primo, pop geral e pega mais numero
	pop	edx
	pop	ecx
	pop	ebx
	jmp	lendo_num_loop
	
segment .data
O_RDONLY equ 	00
O_WRONLY equ	01
O_CREAT  equ  0100

section .data
	msg	db	"FUDEU!!!",0xa
	len	equ	$ - msg

section .text

limpabuf:
	push	ecx
	push	ebx
	mov	ecx, 6
looplimpa:
	and	ecx, ecx
	jz	fimlimpa
	mov	ebx, 0
	mov	[buf+ecx], ebx
	dec 	ecx
	jmp	looplimpa
fimlimpa:
	pop	ebx
	pop	ecx
	ret

	
fudeu:
	mov	edx, len
	mov	ecx, msg
	mov	ebx, 1		; stdout
	mov	eax, 4		; sys_write
	int	0x80
	jmp	vaza_do_programa
	

	global filtra_os_primos	
filtra_os_primos:
	push	ebp		; empilha a antiga base da pilha
	mov	ebp, esp	; base da pilha = topo da pilha

	;; abrir arquivo de entrada
	mov	eax, 5		; sys_open
	mov	ebx, [EBP + 16]	; 16 == 4 (Valor de EBP) + 4 (Valor de Retorno) + 8 (Primeiros 2 argumentos)
	mov	ecx, 0		; O_RDONLY, defined in fcntl.h
	int	0x80		; chamando o sistema

	test	eax, eax
	js	fudeu		; deu erro... vaza do progama e devolve EAX como valor de saida

	push	eax		; armazena apontador para arquivo de saida


	;; cria arquivo de saida
	mov	ebx, [EBP + 20]	; 20 == 4(EBP) + 4(Retorno) + 12(3 primeiros ARG)
	mov  	ecx, O_CREAT 	; cria arquivo se ele nao existe
	mov	edx, 0o755   	; setamos as flags para permissoes de leitura/escrita/execucao
	mov 	eax, 5
	int   	0x80
	
	cmp  	eax, 1        	; verifica se o arquivo existe e/ou foi criado com sucesso
	jl   	fudeu

	;; abre arquivo de saida
	;; EBX ja tem o valor desejado (syscall nao altera)
	mov	ecx, O_WRONLY  	; abre o arquivo pra escrita
	mov 	edx, 0         	; indiferente neste caso
	mov 	eax, 5
	int	0x80
	
	cmp	eax, 1		; se o arquivo nao foi aberto, exibe erro
	jl	fudeu

	pop	ebx		; bota apontador do ENTRADA.TXT no EBX (pro le numero)
	push 	eax		; apontador para a saida

	xor	ecx, ecx	; nosso contador de primos
	
lendo_num_loop:
	call 	le_numero	; bota no EAX o numero lido
	cmp	eax, -1
	je	filtra_end

	cmp	eax, [EBP + 8]
	jb	lendo_num_loop	; EAX < primeiro ARG

	cmp	eax, [EBP + 12]
	ja	lendo_num_loop	; EAX > segundo ARG

	jmp	verifica_primo	; isso pula para lendo_num_loop se nao eh primo
numero_e_primo:
	;; EAX contem um numero primo

	;; TODO: escrever EAX no arquivo SAIDA.TXT
	inc	ecx		; temos mais um primo!!!e1o1ne1oexclamationmark1eE!e1oen1!!

	pop	edx		; apontador de saida
	;; push	ebx		; guardando apontador de entrada
	;; push ecx		; guardando contador

	;; botar no nosso querido buffer o EAX
	;; mov	ebx, edx
	;; mov	ecx, 10
	;; mov	edx, 15
	;; SYSCALL DE ESCRITA AQUI
	 call lolprint

	;; pop	ecx		; recuperando contador
	;; pop	ebx		; recuperando apontador de entrada
	push	edx		; guardando apontador de saida

	;; proximo numero (looping!)
	jmp	lendo_num_loop
		
filtra_end:
	mov	esp, ebp	; esvazia a pilha
	pop	ebp		; recupera a pilha antiga
	mov	eax, ecx	; valor de DEBUG
	ret

lolprint:
	call	limpabuf
	push 	ebx
	push 	ecx
	push 	edx
	
	xor	edx, edx
	xor	ecx, ecx
	;; mov	ax, bx
	mov	bx, 10000
	div	bx
	or	ax, ax
	jz	step2
	add	ax, '0'
	mov	[buf], ax
	inc 	ecx
step2:
	mov	ax, dx
	xor	dx, dx
	mov 	bx, 1000
	div 	bx
	or	ax, ax
	jz	prestep3
	add	ax, '0'
	mov	[buf+ecx], ax
	inc 	ecx
	jmp	step3
prestep3:
	or	ecx, ecx
	jz	step3
	add	ax, '0'
	mov	[buf+ecx], ax
	inc 	ecx
step3:
	mov	ax, dx
	xor	dx, dx
	mov 	bx, 100
	div 	bx
	or	ax, ax
	jz	prestep4
	add	ax, '0'
	mov	[buf+ecx], ax
	inc 	ecx
	jmp	step4
prestep4:
	or	ecx, ecx
	jz	step4
	add	ax, '0'
	mov	[buf+ecx], ax
	inc 	ecx
step4:
	mov	ax, dx
	xor	dx, dx
	mov 	bx, 10
	div 	bx
	or	ax, ax
	jz	prestep5
	add	ax, '0'
	mov	[buf+ecx], ax
	inc 	ecx
	jmp	step5
prestep5:
	or	ecx, ecx
	jz	step5
	add	ax, '0'
	mov	[buf+ecx], ax
	inc 	ecx
step5:
	mov	ax, dx
	add	ax, '0'
	mov	[buf+ecx], ax
	inc 	ecx
	mov	ebx, ' '
	mov	[buf+ecx], ebx
	inc 	ecx
	
	mov	edx, ecx
	mov	ecx, buf
	pop     ebx
	;; mov	ebx, 1
	mov	eax, 4
	int	0x80

	mov	edx, ebx
	pop	ecx
	pop	ebx
	ret

vaza_do_programa:	
	mov	ebx, eax	; valor de saida
	mov	eax, 1		; sys_exit
	int	0x80
