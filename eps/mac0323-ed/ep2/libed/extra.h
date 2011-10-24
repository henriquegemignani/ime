/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Arquivo: extra.h                                              **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 15/04/2010                                                    **/
/*******************************************************************/

/* Funcoes e macros que simplificam o codigo e facilitam o
 desenvolvimento. 
 Tambem possui todas as funcoes para manipular 
 */

#ifndef extra_H_
#define extra_H_

#define AUTOMALLOC(p) p=malloc(sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCV(p,n) p=malloc((n)*sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCADV(p,s) p=malloc(s);if(!p)MALLOC_DIE()

/* Imprime um erro padrao para erro com malloc e encerra a execucao
 do programa, devolvendo o erro 1. */
void MALLOC_DIE();

/* forEVER eh mais legal que for(;;) */
#define EVER (;;)

void doNothing(void* a);

#endif
