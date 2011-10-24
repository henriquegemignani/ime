/*******************************************************************/
/** ITEM interface definition                                     **/
/** Requires: nothing                                             **/
/** Implementation: ITEM.c                                        **/
/**                                                               **/
/** Developed by:                                                 **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#ifndef ITEM_H_
#define ITEM_H_

typedef struct Item *item;

 item ITEMcreate(int key, int val);
  int ITEMkey(item);
  int ITEMval(item);
  int ITEMdestroy(item);
 void ITEMdump(item);

/* Void pointer functions. */
/* A e B sao *ITEM. Devolve Key(A) - Key(B) se for != 0.
   Caso contrario, devolve Val(A) - Val(B). */
int ITEMcmpVOID(void* a, void* b );

/* A eh *ITEM. */
void ITEMdumpVOID(void* a);

/* A eh *ITEM. */
void ITEMdestroyVOID(void* a);

#endif
