/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: FILEMANAGER.h                                        **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 15/04/2010                                                    **/
/*******************************************************************/

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include "BD.h"
#include "libed/BST.h"
#include "libed/LL.h"
typedef struct FileManager *fmgr;

/* Cria um FMGR do arquivo FILENAME com o bookRef dado. Devolve NULL
caso nao seja possivel abrir o arquivo FILENAME, cc o FMGR criado. */
   fmgr FMcreate(bookRef id, char *filename);
   
/* Inicializa o FMGR dado, lendo todas as palavras do arquivo e 
 inserindo-as no indice invertido. */
    int FMinit(fmgr);
    
/* Devolve o bookRef do FMGR dado. */
bookRef FMbookRef(fmgr);

/* Devolve o FILENAME do arquivo correspondente ao FMGR dado. */
  char* FMfilename(fmgr);
  
/* Imprime a linha LINE do arquivo correspondente ao FMGR dado. */
   void FMprintline(fmgr, int line);
   
/* Finaliza o FMGR dado. */
    int FMdestroy(fmgr);

    
/* A e B sao FMGR. Devolve bookRef(A) - bookRef(B). */
int FMcmpVOID(void* a, void* b);
void FMdestroyVOID(void* a);
	
#endif
