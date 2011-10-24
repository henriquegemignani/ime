/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: WORD.c                                               **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 22/04/2010                                                    **/
/*******************************************************************/

#include "extra.h"
#include "WORD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Word {
  char *str;
  list l;
};

word WORDcreate(char *in, list l) {
    word w; AUTOMALLOC(w);
    if( in != NULL )
        WORDsetcpy(w, in);
    w->l = l;
    return w;
}
char* WORDkey(word w) {
    return w->str;
}
list WORDval(word w) {
    return w->l;
}
void WORDset(word w, char *str) {
    w->str = str;
}
void WORDsetcpy(word w, char *str) {
    int j = strlen(str);
    AUTOMALLOCV(w->str,j + 1);
    strncpy(w->str, str, j);
    w->str[j] = '\0';
}
void WORDremove(word w) {
    free(w->str);
}
int WORDdestroy(word w) {
    free(w->str);
    LISTdestroy(w->l, ITEMdestroyVOID);
    free(w);
    return 0;
}
void WORDdump(word w) {
    printf("\"%s\": ", w->str);
    LISTdump(w->l, ITEMdumpVOID);
}

list removeByRefR(list l, int ref) {
    list q;
    if( l == NULL ) return NULL;
    q = removeByRefR(LISTnext(l), ref);
    if( ITEMkey((item)LISTval(l)) == ref ) {
        LISTremove(l, ITEMdestroyVOID);
        l = q;
    } else LISTsetNext(l, q);
    return l;
}
int WORDremoveOccurenceByRef(word w, int ref) {
    w->l = removeByRefR(w->l, ref);
    return 0;
}

void WORDmerge(word w, word x) {
    /* supondo que x soh tem um unico valor na lista. */
    LISTsetNext(x->l, w->l);
    w->l = x->l;
    /* supondo que b tem uma palavra estatica que nao foi alocada */
    free(x);
}

/* Void pointer functions */
int WORDcmpKeyVOID(void* a, void* b ) {
    return strcmp(WORDkey((word)a), WORDkey((word)b));
}

void WORDdumpVOID(void* a) {
    WORDdump((word)a);
}

void WORDdestroyVOID(void* a) {
	WORDdestroy((word)a);
}
