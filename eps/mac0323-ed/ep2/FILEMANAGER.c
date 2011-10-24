/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: FILEMANAGER.c                                        **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 15/04/2010                                                    **/
/*******************************************************************/

#include "libed/extra.h"
#include "FILEMANAGER.h"
#include "libed/ITEM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FileManager {
    bookRef id;
    char *filename;
    unsigned int lineCount;
    long int *lineOffset;
};

fmgr FMcreate(bookRef id, char *filename) {
    fmgr fm;
    int j;
    FILE *f = fopen(filename, "r");
    if(!f) { /* Verifica se o livro existe. */
        perror(NULL);
        return NULL;
    }
    fclose(f);
    AUTOMALLOC(fm);
    fm->id = id;
    
    /* Aloca memoria para a string, e a copia. */
    j = strlen(filename);
    AUTOMALLOCV(fm->filename,j + 1);
    strncpy(fm->filename, filename, j);
    fm->filename[j] = '\0';
    
    fm->lineCount = 0;
    fm->lineOffset = NULL;
    return fm;
}
int FMinit(fmgr fm) {
    FILE *f = fopen(fm->filename, "r");
    int aux, lineEnd, curLine = 0, curSize = 100;
    char c, tmpword[100]; /* Nenhuma palavra tem mais do que 100 letras. */
    long int *tmpVect;
    AUTOMALLOCV(fm->lineOffset,curSize);
    while( !feof(f) ) { /* Loop externo: lendo linhas do arquivo. */
        if( curLine == curSize ) {
            /* realloc fm->lineOffset */
            curSize *= 2;
            tmpVect = realloc(fm->lineOffset, curSize * sizeof(tmpVect));
            if( !tmpVect ) {
                free(fm->lineOffset);
                return 1;
            }
            fm->lineOffset = tmpVect;
        }
        fm->lineOffset[curLine] = ftell(f); /* Armazena a posicao do stream no qual a
                                                    linha atual se encontra. */
        lineEnd = 0;
        while( !lineEnd ) { /* Loop do meio: lendo palavras de uma linha. */
            aux = 0;
            while( aux >= 0 ) { /* Loop interno: lendo caracteres de uma palavra. */
                c = fgetc(f);
                if( ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') ) {
                    tmpword[aux] = c;
                    aux++;
                } else {
                    /* Fim da palavra, terminar string e sair do loop interno. */
                    tmpword[aux] = '\0';
                    if( c == '\n' || c == '\0' || feof(f) )
                        lineEnd = 1; /* Fim da linha tambem, sair do loop do meio tambem. */
                    aux = -1;
                }
            } /* Fim do loop interno. */
            if( tmpword[0] != '\0' ) { 
                /* Se sair de do loop interno sem ler nenhuma palavra, nao adicionar nada na BST. */
                BDaddWord(tmpword, ITEMcreate(fm->id, curLine));
            }
        } /* Fim do loop do meio. */
        curLine++;
    } /* Fim do loop externo. */
    fm->lineCount = curLine;
    fclose(f);
    return 0;
}
bookRef FMbookRef(fmgr fm) {
    return fm->id;
}
char* FMfilename(fmgr fm) {
    return fm->filename;
}
void FMprintline(fmgr fm, int line) {
  FILE *f;
  char l[500];
  if( line >= fm->lineCount )
    return;
  f = fopen(fm->filename, "r");
  
  /* Move a posicao atual do stream para a posicao da linha desejada. */
  fseek(f, fm->lineOffset[line], SEEK_SET);
  
  /* Pega a linha inteira, e armazena. */
  fgets(l, 500, f);
  
  /* Remove a quebra de linha do final, se existir. */
  if(l[strlen(l)-1] == '\n')
    l[strlen(l)-1] = '\0';
  printf("%6u: %s\n", line + 1, l);
  fclose(f);
}
int FMdestroy(fmgr fm) {
    free(fm->filename);
    free(fm->lineOffset);
    free(fm);
    return 0;
}


void FMdestroyVOID(void* a) {
	FMdestroy((fmgr)a);
}
int FMcmpVOID(void* a, void* b) {
	return FMbookRef((fmgr)a) - FMbookRef((fmgr)b);
}
