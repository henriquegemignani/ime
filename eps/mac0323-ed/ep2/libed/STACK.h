/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: STACK.h                                              **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 16/04/2010                                                    **/
/*******************************************************************/

#ifndef STACK_H_
#define STACK_H_

typedef struct Stack *stack;
 void STACKdump(stack, void (*valDumpFunc)(void*));
stack STACKinit(int maxN);
  int STACKempty(stack);
 void STACKpush(stack, void*);
void* STACKpeek(stack);
void* STACKpop( stack);
  int STACKsize(stack);
  int STACKdestroy(stack);

#endif
