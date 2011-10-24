/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#include "lib/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MALLOC_DIE() {
	exit(101);
}

void debugPrintFile(FILE* source) {
	int i = 0,
		curMaxID = 1,
		curPieceID = 1, /* ID do pedaco atual */
		bitsLeft = 1,
		curNumBitsNeeded = 1; /* Quantos bits sao necessarios para ler o pedaco atual */
	unsigned long readBuffer = 0;

	while( !feof(source) ) {
		fread(&readBuffer, 1, 1, source);
		for(i = 7; i >= 0; --i) {
			if(bitsLeft == 1) printf("\t");
			printf("%d", GET_BIT(readBuffer, i));
			if(--bitsLeft == 0) {
				printf("\n");
				if(++curPieceID > curMaxID) {
					curMaxID *= 2;
					++curNumBitsNeeded;
				}
				bitsLeft = curNumBitsNeeded;
			}
		}
	}
	printf("\n");
}

/* Implementada em compress.c */
void compressFile(FILE* source, FILE* target);

/* Implementada em decompress.c */
void decompressFile(FILE* source, FILE* target);

int main(int argc, char *argv[]) {
	int i, mode = COMPRESS;
	char *sourceName = NULL, *outputName = NULL;
	FILE *sourceFile = NULL, *targetFile = NULL;

	/* Leitura de opcoes. Elas devem aparecer todas antes do arquivo.
	 * Possiveis opcoes:
	 * 	-x: decomprimir
	 * 	-d: modo de debug (imprime arquivo em binario. Formata a saida supondo
	 * 		que a entrada esta codificada.
	 * 	-h ou --help: imprime ajuda.
	 */
	for(i = 1; i < argc && argv[i][0] == '-'; i++) {
		switch( argv[i][1] ) {
		case 'x':
			mode = DECOMPRESS;
			break;
		case 'd':
			mode = DEBUG_MODE;
			break;
		case '-':
			if(strcmp(argv[i],"--help") != 0) {
				fprintf(stderr, "Erro: Modo desconhecido: %s\n", argv[i]);
				exit(1);
			}
		case 'h':
			printf("Usage: %s [-x] file\n", argv[0]);
			exit(1);
		default:
			fprintf(stderr, "Erro: Modo desconhecido: %s\n", argv[i]);
			exit(1);
		}
	}
	if(i == argc) {
		fprintf(stderr, "Erro: Nenhum arquivo recebido\n");
		exit(1);
	}
	sourceName = argv[i];

	if(i + 1 != argc) {
		fprintf(stderr, "Erro: Numero nao suportado de parametros\n");
		exit(1);
	}

	if( mode == COMPRESS ) {
		/* Arquivo de saida, caso esteja comprimindo. */
		AUTOMALLOCV(outputName, strlen(sourceName) + 5);
		strcpy(outputName, sourceName);
		strcpy(outputName + strlen(sourceName), ".cod");

	} else if( mode == DECOMPRESS ){
		/* Arquivo de saida, caso esteja decomprimindo. */
		if( strncmp(sourceName + strlen(sourceName) - 4, ".cod", 4) != 0 ) {
			fprintf(stderr, "Erro: Arquivo recebido nao termina com \".cod\"\n");
			exit(1);
		}
		AUTOMALLOCV(outputName, strlen(sourceName) + 1);
		strncpy(outputName, sourceName, strlen(sourceName) - 3);
		strcpy(outputName + strlen(sourceName) - 3, "dec");
	}


	/* abre arquivo de entrada. */
	sourceFile = fopen(sourceName, "rb");
	if(sourceFile == NULL)
		perror("Erro ao abrir arquivo de origem");

	/* abre arquivo de saida, se ele foi determinado */
	if(outputName != NULL) {
		targetFile = fopen(outputName, "wb");
		if( targetFile == NULL )
			perror("Erro ao abrir arquivo de destino");
	}

	/* Se conseguiu abrir ambos os arquivos, comprima ou decomprima o arquivo de entrada. */
	if( sourceFile && targetFile ) {
		if( mode == COMPRESS )
			compressFile(sourceFile, targetFile);
		else
			decompressFile(sourceFile, targetFile);
	} else {
		/* Imprima o caminho dos arquivos, para o usuario poder identificar a origem do erro. */
		printf("Entrada: %s\nSaida:   %s\n", sourceName, outputName);
	}
	/* Condicoes existem para evitar possiveis erros. */
	if( mode == DEBUG_MODE ) debugPrintFile(sourceFile);
	if( sourceFile ) fclose(sourceFile);
	if( targetFile ) fclose(targetFile);
	if( outputName ) free(outputName);
	return 0;
}
