/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Primeiro Exercicio-Programa -- Cruel                          **/
/** Arquivo: main.h                                               **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 02/04/2010                                                    **/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "STACK.h"
#include "CRUEL.h"
#include <string.h>
#include <time.h>

short int gameMode;

#define NUM_COMMAND 8
#define COMMAND_DEBUG   0
#define COMMAND_DISPLAY 1
#define COMMAND_DIST    2
#define COMMAND_EXIT    3
#define COMMAND_HELP    4
#define COMMAND_MOVE    5
#define COMMAND_NEWGAME 6
#define COMMAND_SUGEST  7
char * commandList[NUM_COMMAND] = {
    "debug",
    "display",
    "dist",
    "exit",
    "help",
    "move",
    "newgame",
    "sugest"
};
/* Devolve o indice do comando (referente ao vetor commandList).
 commandList esta ordenado em ordem alfabetica, logo busca binaria funciona. */
int commandMatch( char * in ) {
    int left = 0, right = NUM_COMMAND - 1, i = (left + right)/2, c = 0;
    while( left <= right ) {
        if( c > 1 && ( commandList[i][c] == '\0' && (in[c] == '\0' || in[c] == ' ' ) )
            && ( commandList[i][c - 1] == in[c - 1] ) )
            return i;
        else if( commandList[i][c] > in[c] )
            right = i - 1;
        else if( commandList[i][c] < in[c] )
            left = i + 1;
        else {
            c++;
        }
        i = (left + right)/2;
    }
    return -1;
}

/* O comando 'help' tem uma funcao propria por ser muito extenso. */
void printHelp( int command ) {
    int i;
    if( command == -1 ) {
        printf("Utilize 'help cmd' para saber mais sobre o comando 'cmd'.\n  ");
        for( i = 0; i < NUM_COMMAND; i++ )
            printf("%s ", commandList[i] );
        printf("\n");
        return;
    }
    switch( command ) {
        case COMMAND_DEBUG:
            printf("debug:  debug A\n\tImprime a pilha de cartas A inteira. Se A for negativo, imprime a pilha de naipes -A inteira.\n\tTopo --...--> Fundo\n");
            if( gameMode < 3 )
                printf("Essa funcao esta desativada devido ao modo de jogo selecionado.\n");
            return;
        case COMMAND_DIST:
            printf("dist:  dist\n\tRedistribui as cartas.\n");
            return;
        case COMMAND_DISPLAY:
            printf("display:  display\n\tExibe o estado atual do jogo.\n");
            return;
        case COMMAND_EXIT:
            printf("exit:  exit\n\tTermina a execucao do jogo.\n");
            return;
        case COMMAND_HELP:
            printf("help:  help [cmd]\n\tAjuda do cruel. Lista todos os comandos disponiveis, ou uma ajuda sobre o comando 'cmd'.\n");
            return;
        case COMMAND_MOVE:
            printf("move:  move A [B]\n\tSe apenas A eh fornecido, tenta mover o topo da pilha\n\tde cartas A para a pilha de seu correspondente naipe.\n\n\tCaso B seja fornecido, tenta-se mover para a pilha de\n\tcartas B ao inves disso.\n");
            printf("\nTabela de valores das pilhas de cartas:\n  01 02 03 04\n  05 06 07 08\n  09 10 11 12\n");
            return;
        case COMMAND_NEWGAME:
            printf("newgame:  newgame [mode]\n\tInicia um novo jogo, desistindo do atual. Se mode foi passado, muda o modo de jogo para o fornecido.\n");
            printf("Modos conhecidos: \n1: Usuario   2: CPU     3: Usuario com Ajuda    4: Debug\n");
            return;
        case COMMAND_SUGEST:
            printf("sugest:  sugest\n\tRecomenda uma jogada para o usuario.\n");
            if( gameMode == 0 )
                printf("Essa funcao esta desativada devido ao modo de jogo selecionado.\n");
            return;
        default:
            printf("Nao ha ajuda sobre o comando solicitado.\n");
    }
}

/* Interpreta a sintaxe do comando 'move', e o executa. */
int executeMove( char * input ) {
    char str[40];
    int i, from, to = 0;
    action a;
    i = strlen( input );
    if( i < 3 ) {
        from = atoi(input);
        if( from < 0 || from > 12 )
            return 0;
        a = ACTIONcreateTargetless( from - 1 );
        if( !CRUELvalid( a ) )
            return 0;
        return CRUELaction(a);
    }
    strncpy( str, input, 2 );
    str[2] = '\0';
    input = strchr( input, ' ' );
    from = atoi(str);
    to = atoi(input);
    a = ACTIONcreate( from - 1, to - 1, 1 );
    if( !ACTIONvalid( a ) ) {
        return 0;
    }
    if( !CRUELvalid( a ) ) {
        return 0;
    }
    return CRUELaction(a);
}

int doCommand( int command, char * input ) {
    int i;
    action a;
    switch( command ) {
        case COMMAND_DEBUG:
            if( gameMode < 3 ) {
                printf("Essa funcao esta desativada devido ao modo de jogo selecionado.\n");
            } else {
                i = strlen(commandList[COMMAND_DEBUG]) + 1;
                if( strlen( input ) <= i ) {
                    printf("Erro na sintaxe do comando 'debug'. Utilize 'help debug' para maiores informacoes.\n");
                    return 0;
                }
                i = atoi( input + i );
                CRUELdebug(i);
            }
            return 0;
            
        case COMMAND_DIST:
            CRUELredistribute();
            return 1;
            
        case COMMAND_DISPLAY:
            return 1;
            
        case COMMAND_EXIT:
            exit(0);
            return 0;
            
        case COMMAND_HELP:
            i = strlen(commandList[COMMAND_HELP]) + 1;
            printHelp( commandMatch( input + i ) );
            return 0;
            
        case COMMAND_MOVE:
            i = strlen(commandList[COMMAND_MOVE]) + 1;
            if( strlen( input ) <= i ) {
                printf("Erro na sintaxe do comando 'move'. Utilize 'help move' para maiores informacoes.\n");
                return 0;
            }
            i = executeMove( input + i );
            if( i == 0 )
                printf("Movimento invalido.\n");
            return i;
            
        case COMMAND_NEWGAME:
            i = strlen(commandList[COMMAND_MOVE]) + 1;
            if( strlen( input ) > i + 2 ) {
                i = atoi( input + i + 2 );
                if( i < 1 || 4 < i ) {
                    printf("Modo de jogo desconhecido. Utilize 'help newgame' para maiores informacoes.\n");
                    return 0;
                }
                gameMode = i - 1;
            }
            CRUELfree();
            CRUELstart();
            return 1;
            
        case COMMAND_SUGEST:
            if( gameMode == 0 ) {
                printf("Essa funcao esta desativada devido ao modo de jogo selecionado.\n");
            } else {
                a = CRUELsugestaction();
                if( a.suit == 0 )
                    printf("Mova da pilha de cartas %d para a sua respectiva pilha de naipes.\n", a.from + 1 );
                else if( ACTIONvalid( a ) )
                    printf("Mova da pilha de cartas %d para a pilha de cartas %d.\n", a.from + 1, a.to + 1 );
                else
                    printf("Redistribua.\n");
            }
            return 0;
            
        default:
            printf("Comando desconhecido. Utilize 'help' para ver a lista de comandos.\n");
            return 0;
    }
}

/* Interface text-based para o jogo. Tem um sistema de ajuda completo, logo
 nao eh necessario ler o codigo fonte para conseguir usar. Espero que goste :) */
int main(int argc, char ** argv) {
    char input[50];
    action a;
    
    printf("Cruel Modo-Texto. Selecione o modo do jogo:\n1: Usuario   2: CPU     3: Usuario com Ajuda    4: Debug\n");
    gameMode = 4;
    while( gameMode > 3 ) {
        printf("> ");
        fgets( input, 50, stdin );
        gameMode = input[0] - '1';
        if( gameMode > 3 ) {
            printf("Modo de jogo desconhecido.");
            printf("Modos conhecidos: \n1: Usuario   2: CPU     3: Usuario com Ajuda    4: Debug\n");
        }
    }
    srand( time(NULL) );
    
    CRUELstart();
    CRUELprint();
    
    printf("Jogo inciado com sucesso. Digite 'help' para mais comandos.\n");
    for(;;) {
        printf("> ");
        if( gameMode != 1 ) {
            fgets( input, 50, stdin );
            input[ strlen( input ) - 1 ] = '\0';
            
            if( strlen( input ) <= 1 ) /* Nao teve nenhum comando. */
                continue;
            
            if( doCommand( commandMatch( input ), input ) )
                CRUELprint();
        } else {
            /* computer game */
            a = CRUELsugestaction();
            if( ACTIONvalid(a) ) {
                if( a.suit == 0 )
                    printf("move %d\n", a.from );
                else
                    printf("move %d %d\n", a.from, a.to );
                CRUELaction(a);
            } else {
                printf("dist\n");
                CRUELredistribute();
                CRUELprint();
            }
        }
        if( CRUELgameover() ) {
            printf("Fim de jogo. Score final: %d\n", CRUELscore() );
            
            if( gameMode == 1 ) {
                printf("> ");
                fgets( input, 50, stdin );
                input[ strlen( input ) - 1 ] = '\0';
                if( commandMatch( input ) == COMMAND_NEWGAME )
                    doCommand( COMMAND_NEWGAME, input );
            }
        }
    }
    return 0;
}
