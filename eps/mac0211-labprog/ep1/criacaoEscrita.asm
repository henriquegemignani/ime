; criacaoEscrita.asm -- programa para testar criacao/escrita de arquivos 
;                       em linguagem de montagem compativel com o NASM.
;
; M.S.Reis, 21.mar.2010.

segment .data

; Mensagem para escrever no arquivo
frase    db      "Hello, world!",0xa     ; Frase classica
len     equ     $ - frase                 

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

segment .text
global _start
_start:

   ; Criacao do arquivo, se ele non ecxista
    mov    ebx, arquivo  ;
    mov    ecx, O_CREAT  ; cria arquivo se ele nao existe
    mov	   edx, 0o755    ; setamos as flags para permissoes de leitura/escrita/execucao
    mov    eax, 5
    int    0x80
    cmp    eax, 1        ; verifica se o arquivo existe e/ou foi criado com sucesso
    jl    erro

    ; Abre o arquivo de saida para escrita
    mov    ebx, arquivo   ; apontador para onde esta o nome do arquivo
    mov    ecx, O_WRONLY  ; abre o arquivo pra escrita
    mov    edx, 0         ; indiferente neste caso
    mov    eax, 5
    int    0x80
    cmp    eax, 1         ; se o arquivo nao foi aberto, exibe erro
    jl     erro

    ; Escreve no arquivo
    mov    edx, len      ; tamanho da mensagem
    mov    ecx, frase    ; endereco inicial da mensagem
    mov    ebx, eax      ; guarda o fd (file descriptor)
    mov    eax, 4
    int    0x80

    ; Fecha o arquivo
    mov	   ebx, eax      ; ebx ja' contem o fd
    mov    eax, 6
    int    0x80

fim:
    ; Retorna ao sistema
    mov    ebx, 0
    mov    eax, 1
    int    0x80

erro:
    ; Exibe uma msg de erro e termina o programa
    mov    edx, len_err
    mov    ecx, err
    mov    ebx, STDOUT      ; escreve msg de erro em stdout
    mov    eax, 4
    int    0x80
    jmp    fim              ; vai para o fim do programa
