/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: WORD.h                                               **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 22/04/2010                                                    **/
/*******************************************************************/

#ifndef WORD_H_
#define WORD_H_

#include "LL.h"
#include "ITEM.h"
typedef struct Word *word;

 word WORDcreate(char *str, list l);
char* WORDkey(word);
 list WORDval(word);
 void WORDset(word w, char *str);
 void WORDsetcpy(word w, char *str);
 void WORDremove(word w);
  int WORDdestroy(word);
 void WORDdump(word);
 
  int WORDremoveOccurenceByRef(word, int ref);
 void WORDmerge(word w, word x);

/* Void pointer functions. */

/* A e B sao *ITEM. Compara a key dos 2. Devolve um numero:
 >0 se Key(A) > Key(B)
 =0 se Key(A) = Key(B)
 <0 se Key(A) < Key(B) */
int WORDcmpKeyVOID(void* a, void* b );

/* A eh *ITEM. */
void WORDdumpVOID(void* a);

void WORDdestroyVOID(void* a);

#endif
