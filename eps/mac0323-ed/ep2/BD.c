/*******************************************************************/
/** IME-USP -- MAC0323-2010 - Estrutura de Dados                  **/
/** Segundo Exercicio-Programa -- BST                             **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/**                                                               **/
/** Arquivo: BD.c  -- Header: BD.h                                **/
/** Objetivos:                                                    **/
/**  - Implementar a estrutura Book Database.                     **/
/**  - Gerenciar todos os livros abertos, incluindo abertura      **/
/**     de mais e remocao.                                        **/
/**  - Gerenciar o indice invertido, incluindo insercao, busca,   **/
/**     e remocao de palavras.                                    **/
/*******************************************************************/

#include "libed/extra.h"
#include "BD.h"
#include "libed/BST.h"
#include "libed/WORD.h"
#include "libed/ITEM.h"
#include "libed/LL.h"
#include "FILEMANAGER.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BD {
    bst index, files;
    unsigned int openBooks;
    bookRef lastRef;
};
static bookDatabase bd;
static bookRef removalAux;

int BDinit() {
    AUTOMALLOC(bd);
    bd->index = BSTinit(WORDdestroyVOID, WORDdumpVOID);
    bd->files = BSTinit(FMdestroyVOID, doNothing);
    bd->lastRef = 1;
    bd->openBooks = 0;
    return 0;
}

bookRef BDinsert(char *filename) {
    bookRef ref;
    fmgr fm;
    ref = bd->lastRef;
    printf("Abrindo livro \"%s\"... ", filename);
	fflush(stdout); /* Forca imprimir na tela a msg acima no exato momento. */
    fm = FMcreate(ref, filename);
    if( fm == NULL ) return 0;
    bd->lastRef++;
    bd->openBooks++;
    if( BSTinsert(bd->files, fm, FMcmpVOID) != fm )
        /* Programacao defensiva. So chega aqui caso fm ja esteja na BST (o que eh impossivel) */
        return 0;
    FMinit(fm);
    printf("Livro aberto com sucesso. (Ref == %d)\n", ref);
    return ref;
}

/**********************/
int FMsearchByBookRef(void* a, void* b) {
    return *(int*)a - FMbookRef((fmgr)b);
}
void BDremoveAUXword(void* a) {
    WORDremoveOccurenceByRef((word)a, removalAux);
}
int BDremove(bookRef ref) {
    if( ref == 0 ) return 1;
    if( BSTremove(bd->files, &ref, FMsearchByBookRef) )
        return 1;
    bd->openBooks--;
    
    removalAux = ref;
    /* Para cada no' na bst, remover da lista ligada desse no todas as ocorrencias de removalAux */
    BSTrunFuncForNodes(bd->index, BDremoveAUXword);
    return 0;
}

int BDdestroy() {
    BSTdestroy(bd->index);
    BSTdestroy(bd->files);
    free(bd);
    bd = NULL;
    return 0;
}

/**********************/
int getRefAUX(void *a, void *b) {
    return strcmp( (char*)a, FMfilename((fmgr)b) );
}
bookRef BDgetRef(char *filename) {
    fmgr fm = (fmgr) BSTsearch(bd->files, filename, getRefAUX);
    return fm != NULL ? FMbookRef(fm) : 0;
}

int BDsearchAUX(void* a, void* b) {
    return strcmp((char*)a, WORDkey((word)b));
}
list BDsearch(char *str) {
    word w = (word)BSTsearch(bd->index, str, BDsearchAUX);
    list l, resp;
    if( w == NULL ) return NULL;
    l = WORDval(w);
    if( l == NULL ) return NULL;
    resp = LISTcopy(l);
    /* na BST indice, a lista de ocorrencias eh armazenada ordenada decrescente. */
    LISTinvertOrder(&resp);
    return resp;
}


int BDaddWord(char *str, item it) {
	word w = WORDcreate(NULL, LISTaddNext(LISTinit(), it)), x;
	WORDset(w, str);
    x = BSTinsert(bd->index, w, WORDcmpKeyVOID);
    if( x != w )
        WORDmerge(x, w);
	else /* nao havia str na lista */
		WORDsetcpy(w, str);
    return 0;
}

void BDprint(list l) {
    list p;
    item it;
    fmgr fm = NULL;
    bookRef ref = 0;
    for( p = l; p != NULL; p = LISTnext(p) ) {
        it = LISTval(p);
        if( it == NULL ) continue;
        if( ITEMkey(it) != ref ) {
            /* Mudou de livro, necessario imprimir linha dizendo isso. E achar o novo FM. */
            ref = ITEMkey(it);
            fm = (fmgr) BSTsearch(bd->files, &ref, FMsearchByBookRef);
            if( fm )
                printf("In \"%s\":\n", FMfilename(fm));
        }
        if( fm == NULL ) continue;
        FMprintline(fm, ITEMval(it));
    }
}
