/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: STACKLL.c                                            **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 16/04/2010                                                    **/
/*******************************************************************/

#include "STACK.h"
#include "LL.h"
#include "extra.h"
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int size;
    list l;
};

void STACKdump(stack s, void (*valDumpFunc)(void*)) {
    printf(" STACK DUMP [[size: %d]]\n", s->size);
    LISTdump(s->l, valDumpFunc);
}
stack STACKinit(int maxN) {
    stack s;
    AUTOMALLOC(s);
    s->l = NULL;
    s->size = 0;
    return s;
}
int STACKempty(stack s) {
    return (s->l == NULL);
}
void STACKpush(stack s, void* val) {
    s->l = LISTaddEnd(s->l, val);
    s->size++;
}
void* STACKpeek(stack s) {
    list p;
    for( p = s->l; p != NULL && LISTnext(p) != NULL; p = LISTnext(p) );
    return LISTval(p);
}
void* STACKpop(stack s) { /* Supondo que a pilha eh nao vazia. */
    list p = s->l, q;
    void *resp;
    if( LISTnext(p) == NULL ) {
        resp = LISTval(p);
        LISTremove(p, doNothing);
        s->l = NULL;
    } else {
        for( q = LISTnext(p); q != NULL && LISTnext(q) != NULL; q = LISTnext(q) )
            p = q;
        resp = LISTval(q);
        LISTremoveNext(p, doNothing);
    }
    s->size--;
    return resp;
}
int STACKsize(stack s) {
    return s->size;
}

void STACKdestroyAUX(void* a) {
    LISTdestroy((list)a, doNothing);
}
int STACKdestroy(stack s) {
    LISTdestroy(s->l, STACKdestroyAUX);
    free(s);
    return 0;
}
