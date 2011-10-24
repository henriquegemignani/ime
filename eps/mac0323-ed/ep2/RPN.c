/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: RPN.c                                                **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 16/04/2010                                                    **/
/*******************************************************************/

#include "libed/extra.h"
#include "RPN.h"
#include "libed/LL.h"
#include "libed/ITEM.h"
#include <stdlib.h>
int RPNunion(stack s) {
    list p, q;
    if( STACKsize(s) < 2 )
        return 2;
    p = STACKpop(s);
    q = STACKpop(s);
    STACKpush(s, LISTcreateMergeOrdered(p, q, ITEMcmpVOID));
    LISTdestroy(p, doNothing);
    LISTdestroy(q, doNothing);
    return 0;
}
int RPNintersection(stack s) {
    list p, q, t;
    if( STACKsize(s) < 2 )
        return 2;
    p = STACKpop(s);
    q = STACKpop(s);
    t = LISTcreateIntersection(p, q, ITEMcmpVOID);
    if( t != NULL ) STACKpush(s, t); /* Evitar empilhar resultados vazios. */
    LISTdestroy(p, doNothing);
    LISTdestroy(q, doNothing);
    return t == NULL;
}
int RPNdifference(stack s) {
    list p, q, t;
    if( STACKsize(s) < 2 )
        return 2;
    p = STACKpop(s);
    q = STACKpop(s);
    t = LISTcreateDifference(p, q, ITEMcmpVOID);
    if( t != NULL ) STACKpush(s, t); /* Evitar empilhar resultados vazios. */
    LISTdestroy(p, doNothing);
    LISTdestroy(q, doNothing);
    return t == NULL;
}
