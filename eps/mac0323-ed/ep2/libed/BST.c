/*******************************************************************/
/** BST implementation                                            **/
/** Requires: nothing extra                                       **/
/** Header: BST.h                                                 **/
/**                                                               **/
/** Developed by:                                                 **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#include "extra.h"
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>

struct BSTlink {
  void *val;
  link d[2]; 
};
/********************************************************************
 * Truques com vetor de 2 posicoes para endereco dos filhos:
 *
 * d[0] eh o link esquerdo, e d[1] eh o link direito.
 * d[i] eh um filho, enquanto d[!i] eh o outro.
 * d[ EXPRESSAO BOOLEANA ] aponta para algum dos filhos.
 *
 *Agradeco ao Renan pela ideia de usar um vetor de 2 posicoes na BST
 ********************************************************************/

struct BSTtable {
    link root;
    void (*removeFunc)(void*);
    void (*dumpFunc)(void*);
};

bst BSTinit( void (*removeFunc)(void*), void (*dumpFunc)(void*) ) {
    bst table; AUTOMALLOC(table);
    table->root = NULL;
    table->removeFunc = removeFunc;
    table->dumpFunc = dumpFunc;
    return table;
}

/* Macros para facilitar o desenvolvimento. */
#define BSTval(b)   (b)->val
#define BSTd(b)     (b)->d
#define BSTleft(b)  (b)->d[0]
#define BSTright(b) (b)->d[1]

link BSTnewNode(void *val, link left, link right) {
  link b; AUTOMALLOC(b);
  BSTval(b) = val;
  BSTleft(b) = left;
  BSTright(b) = right;
  return b;
}

void* BSTinsert(bst table, void *val, int (*compareFunc)(void*, void*) ) {
  link *p = &table->root; 
  /* Como p nao possui o endereco do no', mas sim aponta para tal endereco,
  eu posso descer na BST ate que eu ache o local onde o no' que vou inserir
  deveria estar, crio o no' e altero o endereco para o desse novo no'.
   Fazer isso evita muitos casos especiais. */
  int i;
  while( *p != NULL ) {
    i = compareFunc( val, BSTval(*p) );
    if( i == 0 )
      return BSTval(*p);
    p = &BSTd(*p)[i > 0]; 
    /* Quando i > 0, tenho que ir para direita. Nesse caso, (i > 0) vale 1,
    o indice do filho direito no vetor. Conveniente ;) */
  }
  *p = BSTnewNode(val, NULL, NULL);
  return val;
}

void* BSTsearch(bst table, void *key, int (*compareFunc)(void*, void*)) {
  link p = table->root;
  int i;
  while( p != NULL ) {
    i = compareFunc( key, BSTval(p) );
    if( i == 0 ) 
      return BSTval(p);
    p = BSTd(p)[i > 0];
  }
  return NULL;
}

/* Devolve 1 se key nao esta na BST, 0 caso contrario */
int BSTremove(bst table, void *key, int (*compareFunc)(void*, void*)) {
  link q, *p = &table->root;
  int i;
  while( *p != NULL ) {
    i = compareFunc(key, BSTval(*p));
    if( i == 0 ) {
      /* achei o que quero remover! */
      table->removeFunc(BSTval(*p));
      if( !(BSTleft(*p) != NULL && BSTright(*p) != NULL) ) {
        /* entra somente se tem no maximo 1 filho */
      
        q = BSTd(*p)[BSTright(*p) != NULL];
        /* se nao tem filho, q = NULL */
        free(*p);
        *p = q;
        return 0;
      }
      for( q = BSTleft(*p); q != NULL && BSTright(q); q = BSTright(q) );
      BSTright(q) = BSTright(*p);
      /* vai pro filho da esquerda e desce o maximo para a direita, e faz 
    o filho direita desse no' apontar para o filho direito do no' a ser removido */
      
      q = BSTleft(*p);
      free(*p);
      *p = q;
      /* substitiu o no' a ser removido com o seu filho esquerdo, 
      e finalmente remove o no'*/
      return 0;
    }
    p = &BSTd(*p)[i > 0];
  }
  return 1;
}

int BSTrunFuncForNodesR(link r, void (*func)(void*)) {
    if( r == NULL ) return 1;
    BSTrunFuncForNodesR(BSTleft( r), func);
    BSTrunFuncForNodesR(BSTright(r), func);
    func( BSTval(r) );
    return 0;
}
int BSTrunFuncForNodes(bst table, void (*func)(void*)) {
    if( func == NULL ) return 1;
    return BSTrunFuncForNodesR(table->root, func);
}

int BSTdestroyR(bst table, link r) {
    if( r == NULL ) return 1;
    BSTdestroyR(table, BSTleft(r));
    BSTdestroyR(table, BSTright(r));
    table->removeFunc(BSTval(r));
    free(r);
    return 0;
}

int BSTdestroy(bst table) {
    BSTdestroyR(table, table->root);
    free(table);
    return 0;
}

int BSTdumpR(bst table, link b) {
    if( b == NULL ) return 1;
    BSTdumpR(table, BSTleft(b));
    table->dumpFunc(BSTval(b));
    printf("\n");
    BSTdumpR(table, BSTright(b));
    return 0;
}
int BSTdump(bst table) {
    return BSTdumpR(table, table->root);
}
