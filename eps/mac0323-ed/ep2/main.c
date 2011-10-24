/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/**                                                               **/
/** Arquivo: main.c                                               **/
/** Objetivos:                                                    **/
/**  - Implementar o metodo main                                  **/
/**  - Inicializar BD.                                            **/
/**  - Realizar um prompt para que o usuario possa interagir      **/
/**      com o programa, realizando buscas e abrindo arquivos.    **/
/*******************************************************************/

#include "libed/extra.h"
#include "BD.h"
#include "RPN.h"
#include "libed/STACK.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack wordList;

void programQuit() {
    STACKdestroy(wordList);
    BDdestroy();
    exit(0);
}

void runCommand( char *cmd ) {
    void* aux;
    int i, length = strlen(cmd);
    bookRef ref;
    if( length <= 0 ) return;
    switch( cmd[0] ) { /* Verifica o primeiro caracter. */
        case '+':
            i = RPNunion(wordList);
            switch( i ) {
                case 2: 
                    printf("Nao ha resultados empilhados o suficente para realizar uma uniao.\n");
                    return;
                 default:
                    printf("Uniao realizada com sucesso.\n");
                    return;
            }
        case '-':
            i = RPNintersection(wordList);
            switch( i ) {
                case 1:
                    printf("Intesecao inexistente.\n");
                    return;
                case 2:                
                    printf("Nao ha resultados empilhados o suficente para realizar uma intersecao.\n");
                    return;
                default:
                    printf("Intersecao realizada com sucesso.\n");
                    return;
            }
        case '\\':
            i = RPNdifference(wordList);
            switch( i ) {
                case 1:
                    printf("Diferenca inexistente.\n");
                    return;
                case 2:   
                    printf("Nao ha resultados empilhados o suficente para realizar uma diferenca.\n");
                    return;
                default:
                    printf("Diferenca realizada com sucesso.\n");
                    return;
            }
        case '.': /* executar um comando. */
            if( length == 1 ) {
                printf("Sintaxe: .COMMANDO\n");
                return;
            }
            /* Verifica se algum dos comandos com mais de um caracter */
            if( strcmp(cmd + 1, "quit") == 0 || strcmp(cmd + 1, "q") == 0 )
                programQuit();
            if( strcmp(cmd + 1, "NP") == 0 ) {
                printf("%d resultados empilhados.\n", STACKsize(wordList));
                return;
            }
            /* Verifica os comandos de varios caracteres. */
            switch( cmd[1] ) {
                case 'p':
                    if( STACKempty(wordList) ) {
                        printf("Nao ha resultados empilhados.\n");
                        return;
                    }
                    BDprint((list) STACKpeek(wordList));
                    return;
                case 'D':
                    if( STACKempty(wordList) ) {
                        printf("Nao ha resultados empilhados.\n");
                        return;
                    }
                    LISTdestroy(STACKpop(wordList), doNothing);
                    printf("Resultado desempilhado com sucesso.\n");
                    return;
                case '+':
                    if( length == 2 ) {
                        printf("Sintaxe: .+ARQUIVO\n");
                        return;
                    }
                    if( !BDinsert(cmd + 2) )
                        printf("Erro ao abrir livro.\n");
                    return;
                case '-':
                    if( length == 2 ) {
                        printf("Sintaxe: .-ARQUIVO\n");
                        return;
                    }
                    ref = BDgetRef(cmd + 2);
                    if( ref == 0 )
                        printf("Erro: esse livro nao esta aberto.\n");
                    else if( BDremove(ref) )
                        printf("Erro: impossivel fechar tal livro.\n");
                    else
                        printf("Livro fechado com sucesso.\n");
                    return;
                default:
                    printf("\nComando desconhecido.\n");
            }
            return;
        default:
            /* uma palavra normal, para realizar uma busca. */
            aux = BDsearch(cmd);
            if( aux == NULL )
                printf("Nenhuma ocorrencia de \"%s\" encontrada.\n", cmd);
            else {
                STACKpush( wordList, aux );
                printf("Busca por \"%s\" realizada com sucesso.\n", cmd);
            }
    }
}

void readInput() {
    int i = 0, c;
    char cmd[500];
    for EVER {
        c = getchar();
        if( (c == '\n') || (c == '\0') || (c == EOF) ) {
            cmd[i] = '\0';
            runCommand(cmd);
            return;
            
        } else if( (i == 0) && ( c == '+' || c == '-' || c == '\\' ) ) {
            cmd[0] = c;
            cmd[1] = '\0';
            runCommand(cmd);
            i = 0;
            
        } else
            cmd[i++] = c;
    }
}

/* Dado um FILE, chama BDinsert com o valor de cada linha do arquivo. */
void addAllFromFile( FILE *f ) {
    char c, filename[512]; /* Tamanho rasoavel para o path de um arquivo. */
    int j;
    while( !feof(f) ) {
        j = 0;
        while( j > -1 ) {
            c = fgetc(f);
            if( c == '\n' || c == '\0' || feof(f) || j == 511 ) {
                filename[j] = '\0';
                j = -1;
            } else {
                filename[j] = c;
                j++;
            }
        }
        if( filename[0] != '\0' )
            if( !BDinsert(filename) )
                printf("Erro ao abrir livro.\n");
    }
}

int main( int argc, char** argv ) {
    int i = 1;
    FILE *f;
    if( argc == 1 ) {
        printf("Usage: %s [-fLISTA1] [param1] [-fLISTA2] [param2] ...\n"
            "Abre todos os arquivos passados por parametros.\n"
            "-f recebe uma lista de arquivos, separado por quebra de linha.\n", argv[0]);
        exit(2);
    }
    BDinit();
    for( i = 1; i < argc; i++ ) {
        if( strncmp( argv[i], "-f", 2 ) == 0 ) {
            /* modo -f */
            f = fopen( strlen(argv[i]) > 2 ? argv[i] + 2 : argv[++i], "r" );
            if(!f) {
                perror("Impossivel abrir lista de arquivos");
            } else {
                addAllFromFile(f);
                fclose(f);
            }
        } else {
            if( !BDinsert(argv[i]) )
                printf("Erro ao abrir livro.\n");
        }
    }
    /* wordList eh uma variavel global, declarada nesse arquivo por volta da linha 22. */
    wordList = STACKinit(16); /* "STACKinit(int maxN);" mas maxN nao eh usado... */
    for EVER {
        printf("%s > ", argv[0]);
        readInput();
    }
    return 0;
}
