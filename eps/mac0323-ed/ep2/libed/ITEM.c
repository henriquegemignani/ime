/*******************************************************************/
/** ITEM implementation                                           **/
/** Requires: nothing extra                                       **/
/** Header: ITEM.h                                                **/
/**                                                               **/
/** Developed by:                                                 **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/*******************************************************************/

#include "extra.h"
#include "ITEM.h"
#include <stdio.h>
#include <stdlib.h>

/* Key: bookRef
   Val: linha */
struct Item {
  int key, val;
};

item ITEMcreate(int key, int val ) {
  item it; AUTOMALLOC(it);
  it->key = key;
  it->val = val;
  return it;
}

int ITEMkey(item it) {
  return it->key;
}

int ITEMval(item it) {
  return it->val;
}

int ITEMdestroy(item it) {
  free(it);
  return 0;
}

void ITEMdump(item it) {
  printf("(%d,%d)", it->key, it->val);
}

/* Void pointer functions */
int ITEMcmpVOID(void* a, void* b ) {
  int i = ITEMkey((item)a) - ITEMkey((item)b);
  if( i == 0 )
    i = ITEMval((item)a) - ITEMval((item)b);
  return i;
}

void ITEMdumpVOID(void* a) {
    ITEMdump((item)a);
}

void ITEMdestroyVOID(void* a) {
    ITEMdestroy((item)a);
}
