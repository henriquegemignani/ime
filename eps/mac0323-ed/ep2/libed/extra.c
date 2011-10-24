/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: extra.c                                              **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 15/04/2010                                                    **/
/*******************************************************************/

#include "extra.h"
#include "ITEM.h"
#include "LL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MALLOC_DIE() {
    printf("Erro: Falta de memoria.\n");
    exit(1);
}

/* Dava para evitar essa funcao, mas o codigo fica muito mais legivel com ela. */
void doNothing(void* a){}
