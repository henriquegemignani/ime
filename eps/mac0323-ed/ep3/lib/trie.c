/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#include "trie.h"
#include "common.h"
#include <stdlib.h>

trie trieInit() {
	return trieNewNode(0, NULL, NULL);
}

trie trieNewNode(int val, trie left, trie right) {
	trie t;
	AUTOMALLOC(t);
	t->val = val;
	t->link[0] = left;
	t->link[1] = right;
	return t;
}

void trieDestroy(trie t) {
	if( t != NULL ) {
		trieDestroy(t->link[0]);
		trieDestroy(t->link[1]);
		free(t);
	}
}
