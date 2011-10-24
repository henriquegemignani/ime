/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Lista de Exercicios 3: Conjuntos                              **/
/** Arquivo: conjuntos.c                                          **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: 6879634             **/
/** 11/04/2010                                                    **/
/*******************************************************************/

#include "../libed/LL.h"
#include <stdio.h>
#include <stdlib.h>

int pertence(list a, item x) {
    list p;
    
    for( p = a; !LISTempty(p); p = LISTgetNterm(p, 1) )
        if( x == LISTgetVal(p) )
            return 1;
    return 0;
}

list uniao(list a, list b) {
    list p, resp = LISTinit();
    for( p = a; !LISTempty(p); p = LISTgetNterm(p, 1) )
        resp = LISTaddEnd( resp, LISTgetVal(p) );
    for( p = b; !LISTempty(p); p = LISTgetNterm(p, 1) )
        if( !pertence( resp, LISTgetVal(p) ) )
            resp = LISTaddEnd( resp, LISTgetVal(p) );
    return resp;
}

list interseccao(list a, list b) {
    list p, resp = LISTinit();
    for( p = a; !LISTempty(p); p = LISTgetNterm(p, 1) )
        if( pertence( b, LISTgetVal(p) ) )
            resp = LISTaddEnd( resp, LISTgetVal(p) );
    return resp;
}

list diferenca(list a, list b) {
    list p, resp = LISTinit();
    for( p = a; !LISTempty(p); p = LISTgetNterm(p, 1) )
        if( !pertence( b, LISTgetVal(p) ) )
            resp = LISTaddEnd( resp, LISTgetVal(p) );
    return resp;
}

int main(int argc, char ** argv) {
    list a, b, r;
    int i, j;
    FILE *f;
    if( argc != 3 )
        return 2;
    a = LISTinit();
    b = LISTinit();
    
    f = fopen( argv[1], "r" );
    do {
        fscanf( f, "%d ", &i );
        
        if( i >= 0 ) {
            if( !pertence( a, i ) )
                a = LISTaddEnd( a, i );
        }
    } while( i >= 0 );
    fclose(f);
       
    f = fopen( argv[2], "r" );
    do {
        fscanf( f, "%d ", &i );
        if( i >= 0 ) 
            if( !pertence( b, i ) )
                b = LISTaddEnd( b, i );
    } while( i >= 0 );
    fclose(f);
       
    for(;;) {
        scanf("%d %d", &i, &j );
        switch(i) {
            case 1:
                LISTdump(a);
                LISTdump(b);
                break;
            case 2:
                printf("%d\n", j > 0 ? pertence(a,j) : pertence(b,-j) );
                break;
            case 3:
                r = uniao(a,b);
                LISTdump(r);
                LISTdestroy(r);
                break;
            case 4:
                r = interseccao(a,b);
                LISTdump(r);
                LISTdestroy(r);
                break;
            case 5:
                r = j > 0 ? diferenca(a,b) : diferenca(b,a);
                LISTdump(r);
                LISTdestroy(r);
                break;
            default:
                exit(0);
        }
    }
    return 0;
}
