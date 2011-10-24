/*******************************************************************/
/** Book Database interface definition                            **/
/** Requires: nothing                                             **/
/** Implementation: BD.c                                          **/
/**                                                               **/
/** Developed by:                                                 **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#ifndef BD_H_
#define BD_H_

#include "libed/ITEM.h"
#include "libed/LL.h"
typedef unsigned int bookRef;
typedef struct BD   *bookDatabase;

/* Inicializa o BD. */
    int BDinit();
    
/* Abre um novo FILEMANAGER do arquivo filename e adiciona a bst
 indice todas as palavras desse arquivo. 
 Devolve o bookRef gerado e 0 em caso de erro. */
bookRef BDinsert(char *filename);

/* Fecha o FILEMANAGER do bookRef dado e devolve 0 em sucesso.
 Caso nao exista tal FILEMANAGER, devolve 1. */
    int BDremove(bookRef);
    
/* Fecha todos os FILEMANAGER e desmonta a bst INDICE. */
    int BDdestroy();

/* Devolve o bookRef do primeiro FILEMANAGER aberto de filename.
 0 caso nao exista. */
bookRef BDgetRef(char *filename);

/* Devolve uma LIST de ITEM de todas as ocorrencias da palavra STR.*/
   list BDsearch(char *str);
   
/* Adiciona uma nova ocorrencia IT da palavra STR na bst INDICE. */
    int BDaddWord(char *str, item it);
    
/* Imprime todas as linhas o qual uma LIST de ITEM se refere. */
   void BDprint( list);
   
#endif
