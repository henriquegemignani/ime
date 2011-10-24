/*******************************************************************/
/** BST interface definition                                      **/
/** Requires: nothing                                             **/
/** Implementation: BST.c                                         **/
/**                                                               **/
/** Developed by:                                                 **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#ifndef BST_H_
#define BST_H_

typedef struct BSTlink *link;
typedef struct BSTtable *bst;

  bst BSTinit( void (*removeFunc)(void*), void (*dumpFunc)(void*) );
  link BSTnewNode(void *val, link left, link right);

/* Adiciona o valor val na bst root, localizando a posicao correta com compareFunc.
 Se um no' para o qual compareFunc devolve 0, a funcao devolve o valor desse no'.
 Caso contrario, cria-se um novo no' com valor val e devolve val. */
void* BSTinsert(bst table, void *val, int (*compareFunc)(void*, void*) );

/* Busca na bst TABLE por um no' para o qual 
 compareFunc( no'->val, key ) == 0, e devolve o valor desse no'.
 Devolve NULL se nao existe. */
void* BSTsearch(bst table, void *key, int (*compareFunc)(void*, void*));

/* Remove o no' para o qual compareFunc devolve 0, chamando a funcao de remocao
 da tabela. */
  int BSTremove(bst table, void *key, int (*compareFunc)(void*, void*));

/* Executa func para cada no' da BST. */
  int BSTrunFuncForNodes(bst table, void (*func)(void*));
    
/* Remove todos os no's da BST.. */
  int BSTdestroy(bst table);

/* Imprime a bst root ordenadamente chamando dumpFunc para imprimir o no'. */
  int BSTdump(bst table);

#endif
