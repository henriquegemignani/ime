/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#ifndef _TRIE_H_
#define _TRIE_H_

typedef struct Trie {
	int val;
	struct Trie *link[2];
} *trie;

trie trieInit();
trie trieNewNode(int val, trie left, trie right);
void trieDestroy(trie t);

#endif /* _TRIE_H_ */
