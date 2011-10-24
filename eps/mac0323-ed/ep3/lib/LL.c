/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#include "LL.h"
#include "common.h"
#include <stdlib.h>

list listNewNode(int val, list prev) {
	list l;
	AUTOMALLOC(l);
	l->val = val;
	l->prev = prev;
	return l;
}

void listRemove(list l) {
	free(l);
}
void listDestroyRecursive(list l) {
	if(l != NULL) {
		listDestroyRecursive(l->prev);
	}
}

/* Essa funcao existe para simplificar a macro de stackPop e evitar maiores problemas. */
int stackPop_FUNC(list *stack) {
	list aux = *stack;
	int val = aux->val;
	*stack = aux->prev;
	listRemove(aux);
	return val;
}
