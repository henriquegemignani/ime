/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Terceiro Exercicio-Programa -- Tries                          **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#define COMPRESS	1
#define DECOMPRESS	2
#define DEBUG_MODE	3

/* #define DEBUG */

#ifdef DEBUG
#define debugPrint(str, val) printf(str, val);
#else
#define debugPrint(str, val) {/* BLANK(str,val) */}
#endif

#define LN2		0.693147180559

/* Devolve o BIT-esimo bit de var, do menos significativo para o mais significativo. */
#define GET_BIT(var, bit) ((var) & (1 << (bit)) ? 1 : 0)
/* Define o BIT-esimo bit de var, do menos significativo para o mais significativo, como 1. */
#define SET_BIT(var, bit) (var = (var) | (1 << (bit)))
/* Define o BIT-esimo bit de var, do menos significativo para o mais significativo, como 0. */
#define UNSET_BIT(var, bit) (var = (var) & (-1 - (1 << (bit))))

#define AUTOMALLOC(p) p=malloc(sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCV(p,n) p=malloc((n)*sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCADV(p,s) p=malloc(s);if(!p)MALLOC_DIE()
void MALLOC_DIE();

#endif /* _COMMON_H_ */
