/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#ifndef _LL_H_
#define _LL_H_

typedef struct List {
	int val;
	struct List *prev;
} *list;

#define listInit()	NULL
list listNewNode(int val, list prev);

void listRemove(list l);
void listDestroyRecursive(list l);

int stackPop_FUNC(list *stack);

/*
 * Utilizando esta interface de LL, eh possivel simular uma pilha.
 * Logo os defines a seguir foram escritos para descrever uma interface de pilha.
 */
#define stackInit(stack) 		stack = NULL
#define stackEmpty(stack)		(stack == NULL)
#define stackPush(stack, val)	stack = listNewNode(val, stack)
#define stackPop(stack)			(stackPop_FUNC(&stack))
#define stackRemove(stack)		listDestroyRecursive(stack)

#endif /* _LL_H_ */
