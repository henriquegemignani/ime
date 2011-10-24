/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Lista de Exercicios 2: 8 Rainhas                              **/
/** Arquivo: rainhas.c                                            **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: 6879634             **/
/** 11/04/2010                                                    **/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../libed/ITEM.h"
#include "../libed/STACK.h"

stack resp;
item * queen;
int N, curX, curY;

#define QUEEN_CONFLICT(a,b) ( (ITEMval(a) == ITEMval(b)) || (ITEMkey(a) == ITEMkey(b)) \
    || (ITEMval(a) - ITEMkey(a) == ITEMval(b) - ITEMkey(b) ) || (ITEMval(a) + ITEMkey(a) == ITEMval(b) + ITEMkey(b) ) )

int main(int argc, char ** argv) {
    item it;
    int i, s;
    short **tab;
    if( argc != 2 )
        return 2;
    N = atoi(argv[1]);
    resp = STACKinit(N);
    queen = malloc( N * sizeof(*queen) );
    if( !queen ) exit(1);
    
    curX = curY = 0;
    printf("Hello there, and welcome to another backtracking program! I hope you enjoy your stay!\n"
        "We'll be trying to fit %d queens in a %dx%d board.\n", N, N, N);
    
    while( STACKsize( resp ) < N ) {   
        s = STACKsize( resp );
        it = ITEMcreate(curX, curY);
        /*printf("Queens: %d | Pos = ", STACKsize( resp ) );
        ITEMprint(it);
        printf("| ");
        STACKdump( resp );*/
        
        for(i = 0; i < s && !QUEEN_CONFLICT( queen[i], it ); i++);
        if( i == s ) {
            /* achou mais uma rainha */
            queen[i] = it;
            STACKpush( resp, it );
            curX = curY = 0;
            s++;
            
        } else {
            /* posicao invalida */
            invalid:
            curX++;
            if( curX == N ) {
                curX = 0;
                curY++;
                if( curY == N ) {
                    /* FUCK, BACKTRACK! */
                    if( STACKempty( resp ) ) {
                        break;
                        /* tabuleiro imposivel! */
                    } else if( s < N ){
                        it = STACKpop( resp );
                        s--;
                        curX = ITEMkey(it);
                        curY = ITEMval(it);
                        goto invalid;
                    }
                }
            }
        }
    }
    if( s < N ) {
        printf("We're deeply sorry, but it's impossible to fit %d queens in a %dx%d board.\n", N, N, N);
    } else {
        tab = malloc( N * sizeof( *tab ) );
        if( !tab ) exit(1);
        for( i = 0; i < N; i++ ) {
            tab[i] = malloc( N * sizeof( **tab ) );
            if( !tab[i] ) exit(1);
            for( s = 0; s < N; s++ ) tab[i][s] = 0;
        }
        while( !STACKempty( resp ) ) {
            it = STACKpop( resp );
            tab[ITEMkey(it)][ITEMval(it)] = 1;
        }
        printf("\n");
        for( s = 0; s < N; s++ ) {
            for( i = 0; i < N; i++ )
                printf("%c ", tab[i][s] + '0');
            printf("\n");
        }
    }
    
    return 0;
}

