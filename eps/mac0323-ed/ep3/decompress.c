/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#include "lib/common.h"
#include "lib/LL.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* Funcao auxiliar para verificar se um numero eh uma potencia de 2. */
int checkIfPowderOf2(int val) {
	/*
	 * Em binario, uma potencia de 2 eh descrita por um digito "1" seguido
	 * de zero ou mais digitos "0"
	 */
	while(val > 1) {
		if(val & 1)
			return 0;
		val = val >> 1;
	}
	return val;
}

/* Descomprime o arquivo SOURCE em TARGET. */
void decompressFile(FILE* source, FILE* target) {
	list *lVect, aux, stack;
	int i = 0,
		curPiece = 0, /* Armazena o pedaco atual inteiro */
		printAux = 0, /* Auxiliar para debug. */
		tVectSize = 2, /* Tamanho do vetor de pedacos */
		curPieceID = 0, /* ID do pedaco atual */
		readBufferSize = 0, /* Quantos bits nosso buffer de leitura armazena atualmente */
		writeBufferSize = 0, /* Idem para o buffer de escrita */
		curNumBitsNeeded = 1, /* Quantos bits sao necessarios para ler o pedaco atual */
		readValue = 0; /* Usado para armazenar o valor lido do arquivo, temporariamente */
	unsigned long readBuffer = 0, writeBuffer = 0;

	/* Inicializando variaveis. */
	stackInit(stack);
	AUTOMALLOCV(lVect, tVectSize);
	lVect[0] = listInit();

	while(!feof(source)) {
		/*
		 * Se o pedaco anterior era uma potencia de 2, significa que a quantidade de bits necessaria
		 * para descrever um ID aumentou em 1.
		 */
		if(checkIfPowderOf2(curPieceID))
			++curNumBitsNeeded;

		if(++curPieceID >= tVectSize) {
			/* Vetor de pedacos nao suporta mais um pedaco. */
			tVectSize *= 2;
			lVect = realloc(lVect, tVectSize * sizeof(*lVect));
			if(lVect == NULL)
				MALLOC_DIE();
		}

		/* Garante que o buffer possua pelo menos um pedaco, lendo do arquivo se for necessario. */
		while( !feof(source) && readBufferSize < curNumBitsNeeded ) {
			fread(&readValue, 1, 1, source);
			readBuffer = (readBuffer << 8) + readValue;
			readBufferSize += 8;
		}
		if(readBufferSize < curNumBitsNeeded) {
			/* Arquivo acabou antes de achar mais um pedaco! */
			--curPieceID; /* Para evitar problemas na liberacao de memoria. */
			break;
		}

		/* Arranca do buffer um pedaco e coloca em curPiece. */
		readBufferSize -= curNumBitsNeeded;
		curPiece = readBuffer >> readBufferSize;
		readBuffer &= (1 << readBufferSize) - 1;


		/* Debug: imprime o que foi lido. */
		debugPrint("[%2d] ", curPieceID);
		for(i = curNumBitsNeeded; i < 6; ++i)
			debugPrint("%c", ' ');
		for(i = curNumBitsNeeded - 1; i >=0; --i) {
			if(i == 0) debugPrint("%c", '\t');
			debugPrint("%d", GET_BIT(curPiece, i));
		}
		debugPrint(" {%2d} -- ", (curPiece >> 1));

		/* Tratar o pedaco atual, pegando o ID do pedaco anterior... */
		i = (curPiece >> 1);
		if(i >= curPieceID)
			break; /* Pedaco atual na verdade eh um EOF. */

		curPiece = curPiece & 1; /* ... e o bit extra! */

		/* Armazena em lVect um LL com o bit novo e apontando para a LL correspondente `a dependencia! */
		lVect[curPieceID] = listNewNode(curPiece, lVect[i]);

		/* Passa pela lista ligada, empilhando os bits. */
		for(aux = lVect[curPieceID]; aux != NULL; aux = aux->prev) {
			/* empilhar aux->val para decodificar o pedaco atual */
			stackPush(stack, aux->val);
		}

		/* pegar os valores empilhados e escrever */
		while(!stackEmpty(stack)) {
			while(writeBufferSize >= 8) {
				/* Escreve os 8 bits mais a esquerda de writeBuffer */
				fwrite(&writeBuffer, 1, 1, target);

				/* Remove tais bits de writeBuffer */
				writeBufferSize -= 8;
				writeBuffer &= (1 << writeBufferSize) - 1;
			}
			printAux = stackPop(stack);
			writeBuffer = (writeBuffer << 1) + printAux;
			debugPrint("%d", printAux);
			++writeBufferSize;
		}
		debugPrint("%c",'\n');
		/* escrever no arquivo enquanto tiver bytes inteiros para escrever */
	}
	debugPrint("%c",'\n');
	/* Liberando memoria. */
	for(i = 0; i < curPieceID; ++i)
		listRemove(lVect[i]);
	free(lVect);
	stackRemove(stack);
}

