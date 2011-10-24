/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#include "lib/common.h"
#include "lib/trie.h"
#include <stdio.h>

struct Pending {
	int list[8];
	int curBit;
};

/* Dado um ponteiro de um struct Pending, seta todos os elementos do vetor a -1 e zera curBit. */
void nullPending(struct Pending *b) {
	int i;
	b->curBit = 0;
	for(i = 0; i < 8; i++ )
		b->list[i] = -1;
}

/* Escreve o byte armazenado no struct Pending B, apenas se b->curBit >= 8 */
void writeIfPending(FILE* target, struct Pending *b) {
	int i, result = 0;
	if(b->curBit < 8) return;
	for(i = 0; i < 8; i++)
		result += b->list[7-i] << i;
	nullPending(b);
	fwrite(&result, 1, 1, target);
}

/*
 * Escreve o pedaco (ID,BIT) no arquivo TARGET, utilizando-se do struct Pending BITS.
 * MAX_ID eh usado para saber com quantos bits deve-se representar ID.
 */
void fileWrite(FILE* target, int id, int bit, int max_id, struct Pending *bits) {
	int idbits, i;
	for( idbits = 0; (max_id >> idbits) > 0; idbits++ );
	for(i = 0; i < idbits; i++ ) {
		bits->list[bits->curBit++] = GET_BIT(id, idbits - i - 1);
		debugPrint("%d", bits->list[bits->curBit - 1]);
		writeIfPending(target, bits);
	}
	bits->list[bits->curBit++] = bit;
	debugPrint("+%d", bits->list[bits->curBit - 1]);
	writeIfPending(target, bits);
	debugPrint("%s","\n");
}

/* Comprime o arquivo SOURCE em TARGET. */
void compressFile(FILE* source, FILE* target) {
	trie tRoot = trieInit(), prev = NULL, piece = tRoot;
	int i, buff, bit, lastPieceID = 0;
	struct Pending bits;
	nullPending(&bits);
	while(!feof(source)) {
		/* Pega um byte de SOURCE */
		fread(&buff, 1, 1, source);

		/* Para cada bit desse byte, comecando pelo mais significativo */
		for(i = 7; i >= 0; i-- ) {
			bit = GET_BIT(buff, i);
			if( piece == NULL )
				piece = tRoot;

			debugPrint("%d", bit);
			if(piece->link[bit] != NULL) {
				/* Ainda nao achamos o maior pedaco unico. */
				piece = (prev = piece)->link[bit];
			} else {
				/* Achamos o menor pedaco que ainda nao apareceu:
				 * -- Cria um novo no' na trie. */
				piece->link[bit] = trieNewNode(++lastPieceID, NULL, NULL);
				debugPrint("\t-- %2d", piece->val);
				debugPrint(" %d\t", bit);
				debugPrint("[%2d] ",lastPieceID);
				/* Escreve o pedaco no arquivo de saida. */
				fileWrite(target, piece->val, bit, lastPieceID - 1, &bits);
				prev = piece;
				piece = NULL;
				/* Reinicia a busca do inicio. */
			}
		}
	}
	if(piece != NULL) {
		/*
		 * Fim de arquivo, mas estavamos no meio de um pedaco.
		 * Estrategia? Tratar o que achamos ate o momento como um novo pedaco.
		 */
		debugPrint("\t-- %2d", prev->val);
		debugPrint(" %d\t", bit);
		debugPrint("[%2d] ",lastPieceID + 1);
		fileWrite(target, prev->val, bit, lastPieceID, &bits);
		/* Se falta bits para preencher um byte, preenche de digitos 1 */
		while(bits.curBit < 8)
			bits.list[bits.curBit++] = 1;
		writeIfPending(target, &bits);
	}
	trieDestroy(tRoot);
}
