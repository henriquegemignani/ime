; leitura.asm -- programa para testar a leitura de arquivos 
;                em linguagem de montagem compativel com o NASM.
;
; M.S.Reis, 21.mar.2010.

segment .data

; Mensagem de erro
err     db      "Erro ao abrir arquivo!",0xa
len_err     equ     $ - err

; Alguns modos de abertura de arquivo
O_RDONLY equ 	00
O_WRONLY equ	01
O_CREAT  equ  0100

; File descriptors (fd)
STDIN    equ     0  ; codigo do fd da entrada padrao
STDOUT   equ     1  ; codigo do fd da saida padrao

; Nome do arquivo
arquivo db "teste.txt", 0x0

segment .bss

; Um bufferzinho pra ler o arquivo
buf     resb   256

segment .text
global _start
_start:

    ; Abre o arquivo para leitura
    mov    ebx, arquivo   ; apontador para onde esta o nome do arquivo
    mov    ecx, O_RDONLY  ; abre o arquivo pra leitura
    mov    edx, 0         ; indiferente neste caso
    mov    eax, 5
    int    0x80
    cmp    eax, 1         ; se o arquivo nao foi aberto, exibe erro
    jge    leitura
    mov    edx, len_err
    mov    ecx, err
    mov    ebx, STDOUT    ; escreve msg de erro em stdout
    mov    eax, 4
    int    0x80
    jmp fim       ; vai para o fim do programa

leitura:
    ; Le do arquivo (1 de 2)
    push   eax            ; guardo o fd
    mov    edx, 5          ; numero de bytes que eu quero
    mov    ecx, buf        ; ptr do inicio de buf
    mov    ebx, eax        ;
    mov    eax, 3
    int    0x80
    ; Imprime na tela (1 de 2)
    mov    edx, eax         ; tamanho da mensagem
    mov    ecx, buf         ; endereco inicial da mensagem
    mov    ebx, STDOUT      ; 
    mov    eax, 4
    int    0x80

    ; Le do arquivo (2 de 2)
    pop    eax             ; restauro o fd
    mov    edx, 9          ; numero de bytes que eu quero
    mov    ecx, buf        ; ptr do inicio de buf
    mov    ebx, eax        ;
    mov    eax, 3
    int    0x80
    ; Imprime na tela (2 de 2)
    mov    edx, eax         ; tamanho da mensagem
    mov    ecx, buf         ; endereco inicial da mensagem
    mov    ebx, STDOUT      ; 
    mov    eax, 4
    int    0x80

fim:
    ; Retorna ao sistema
    mov    ebx, 0
    mov    eax, 1
    int    0x80
