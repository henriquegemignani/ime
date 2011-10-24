/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Primeiro Exercicio-Programa -- Cruel                          **/
/** Arquivo: CRUEL.h                                              **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 31/03/2010                                                    **/
/*******************************************************************/

#ifndef CRUEL_H_
#define CRUEL_H_

#include "CARD.h"
#include "STACK.h"

#include <stdio.h>

/* Uma jogada do jogo eh definida da seguinte forma:
 Uma carta eh removida da 'pilha de cartas' FROM, e eh movida para a
 - 'pilha de naipes' TO, se SUIT == 0
 - 'pilha de cartas' TO, caso contrario
  */
struct Action {
    unsigned int from, to, suit;
};
typedef struct Action action;
action  ACTIONcreate(unsigned int from, unsigned int to, unsigned int suit);

/* Cria uma jogada que tenta mover o topo de uma pilha de cartas 
    para a sua respectiva pilha de naipes. */
action  ACTIONcreateTargetless(unsigned int from);

/* Verifica se essa jogada possui FROM e TO em intervalos validos.
    Devolve 1 se sim, 0 caso contrario. */
int     ACTIONvalid(action a);

/* Libera a memoria para seja possivel comecar um novo jogo. */
void    CRUELfree();

/* Inicia um novo jogo, embaralhando as cartas. */
void    CRUELstart();

/* Verifica se a jogada a eh valida, no estado atual do jogo.
    Devolve 1 se a jogada e válida, 0 caso contrário.*/
int     CRUELvalid(action a);

/* Tenta realizar a jogada a.  
    Devolve 1 se foi bem sucedida e 0 caso contrario. */
int     CRUELaction(action a);

/* Redistribui as cartas. */
void    CRUELredistribute();

/* Devolve a pontuacao atual. */
int     CRUELscore();

/* Devolve 1 se nao ha jogadas possiveis, 0 caso haja. */
int     CRUELgameover();

/* Devolve quantas cartas restam. */
int     CRUELcardsleft();

/* Analisa o jogo atual e devolve uma jogada. Se a jogada devolvida
for invalida, significa que nao ha mais jogadas possiveis e jogo acabou. */
action  CRUELsugestaction();

/* Imprime na tela o tabuleiro atual. */
void    CRUELprint();

/* Imprime todas as cartas da pilha de:
 cartas i, se i > 0
 naipes -i, se i < 0 */
void    CRUELdebug(int i);

#endif
