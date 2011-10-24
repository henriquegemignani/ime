/*******************************************************************/
/** MAC0323 - Estrutura de Dados                                  **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Primeiro Exercicio-Programa -- Cruel                          **/
/** Arquivo: CRUEL.c                                              **/
/**                                                               **/
/** Henrique Gemignani Passos Lima      nUSP: ???????             **/
/** 31/03/2010                                                    **/
/*******************************************************************/

#include "CARD.h"
#include "STACK.h"
#include "CRUEL.h"
#include "LL.h"

#include <stdio.h>
#include <stdlib.h>

/* As pilhas de cartas. */
stack suitStack[4];
stack cardStack[12];
int cardLeft;
int suitPosition[4];
int movedSinceDist;
action lastSugest;

action ACTIONcreate(unsigned int from, unsigned int to, unsigned int suit) {
    action a;
    a.from = from;
    a.to = to;
    a.suit = suit;
    return a;
}

action ACTIONcreateTargetless(unsigned int from) {
    /* A posicao de uma pilha de naipes eh aleatoria, mas foi 
        armazenada no vetor suitPosition. */
    return ACTIONcreate( from, suitPosition[ CARDsuit( STACKpeek( cardStack[from] ) ) ], 0 );
}

int ACTIONvalid(action a) {
    if( a.from > 12 )
        return 0;
    if( (a.suit == 0 && a.to > 4) || a.to > 12 )
        return 0;
    return 1;
}

void CRUELfree() {
    int i;
    for( i = 0; i < 4; i++ )
        while( !STACKempty(suitStack[i]) )
            CARDremove( STACKpop( &(suitStack[i]) ) );
            
    for( i = 0; i < 12; i++ )
        while( !STACKempty(cardStack[i]) )
            CARDremove( STACKpop( &(cardStack[i]) ) );
            
    /* Como funciona:
        Para cada pilha, de naipe e de carta, desempilha 
          uma carta e a remove. */
}

void CRUELstart() {
    int i, j, k;
    list ll = LISTinit(), q;
    /* inicializa as 4 pilhas de naipes */
    for( i = 0; i < 4; i++ ) {
        suitStack[i] = STACKinit( 13 );
        LISTaddStart( ll, CARDcreate( i, 1 ) ); 
    }
    /* aleatoriza a ordem das 4 pilhas de naipes */
    for( i = 0; i < 4; i++ ) {
        k = rand() % (4 - i);
        q = LISTgetNterm( ll, k );
        STACKpush( &suitStack[i], LISTgetVal(q) );
        suitPosition[ CARDsuit(LISTgetVal(q)) ] = i;
        LISTremove(q);

    }
    
    /* inicializa as 12 pilhas de cartas */
    for( i = 0; i < 12; i++ )
        cardStack[i] = STACKinit( 26 );
        
    /* coloca as 48 cartas na lista ligada */
    for( j = 0; j < 4; j++ ) {
        for( i = 2; i <= 13; i++ ) {
            LISTaddStart( ll, CARDcreate( j, i ) );
        }
    }
    
    /* preechemos as 12 pilhas de cartas linearmente, mas com
        cartas escolhidas aleatoriamente */
    for( i = 0; i < 12; i++ ) {
        for( j = 0; j < 4; j++ ) {
            k = rand() % (48 - (4 * i + j) );
            q = LISTgetNterm( ll, k );
            STACKpush( &cardStack[i], LISTgetVal(q) );
            LISTremove(q);
        }
    }
    LISTdestroy(ll);
    
    /* Selecionar uma carta aleatoria. Como funciona:
        Coloca-se todas as cartas numa LL.
        Sempre que precisar de uma carta aleatoria, fazer 
          k = rand() % TOTAL_DE_CARTAS_NA_LL e pegar a 
          k-esima carta da LL, removendo-a da lista. */
    
    cardLeft = 48;
    movedSinceDist = 0;
    lastSugest = ACTIONcreate(-1,-1,-1);
}

int CRUELvalid(action a) {
    stack from, to;
    from = cardStack[a.from];
    to = ( a.suit == 0 ) ? suitStack[a.to] : cardStack[a.to];
    if( STACKempty(from) || STACKempty(to) ) return 0; /* Pilhas vazias nao sao validas. */
    if( CARDsuit( STACKpeek(from) ) != CARDsuit( STACKpeek(to) ) ) return 0;
    
    if( a.suit == 0 )
        /* Para mover para a pilha de naipe, a carta tem que ter um valor 1 maior. */
        return ( CARDval( STACKpeek(from) ) - 1 == CARDval( STACKpeek(to) ) );
    else
        /* Para mover para outra pilha de cartas, a carta tem que ter um valor 1 menor. */
        return ( CARDval( STACKpeek(from) ) + 1 == CARDval( STACKpeek(to) ) );
}

int CRUELaction(action a) {
    card c;
    stack 
        *from = &(cardStack[a.from]), 
        *to   = ( a.suit == 0 ) ? &(suitStack[a.to]) : &(cardStack[a.to]);
    c = STACKpop( from );
    STACKpush(to, c);
    if( a.suit == 0 ) cardLeft--;
    movedSinceDist = 1;
    lastSugest = ACTIONcreate(-1,-1,-1);
    return 1;
}

void CRUELredistribute() {
    list ll = LISTinit(), q;
    int j = 0, i = 0;
    while( i < 12 ) {
        if( STACKempty( cardStack[i] ) )
            i++;
        else
            LISTaddEnd( ll, STACKpop( &cardStack[i] ) );
    }
    i = 0;
    while( !LISTempty( ll ) ) {
        if( j >= 4 ) {
            j = 0;
            i++;
        }
        q = LISTgetNterm( ll, 3 - j );
        if( q ) {
            STACKpush( &cardStack[i], LISTgetVal( q ) );
            LISTremove(q);
        }
        j++;
    }
    LISTdestroy(ll);
    movedSinceDist = 0;
    lastSugest = ACTIONcreate(-1,-1,-1);
}

int CRUELscore() {
    return 52 - cardLeft;
    /* A pontuacao eh a quantidade de cartas nas pilhas de naipes. 
        Ou seja, comeca em 4 e aumenta em 1 para cada carta que voce move para
        la, atingindo 52 quando mover todas. */
}

int CRUELgameover() {
    /* CRUELsugestaction devolve (-1,-1,-1) quando nao 
        ha mais jogadas a serem feitas. */
    return (movedSinceDist == 0) && !ACTIONvalid( CRUELsugestaction() );
}

int CRUELcardsleft() {
    return cardLeft;
}

/* Analisa o jogo atual e devolve uma jogada. Se a jogada devolvida
for invalida, significa que nao ha mais jogadas possiveis. */
action CRUELsugestaction() {
    card c;
    int suitVal[4], i, k;
    if( lastSugest.to != -1 )
        return lastSugest;
    
    for( i = 0; i < 4; i++ ) {
        c = STACKpeek( suitStack[suitPosition[i]] );
        suitVal[i] = CARDval(c);
    }
    /* primeiro verifica se da pra mover alguma carta para uma 
        pilha de naipes, iniciando de uma pilha qualquer. */
    for( k = rand(), i = 0; i < 12; i++, k++ ) {
        k = k % 12;
        if( STACKempty( cardStack[k] ) )
            continue;
        c = STACKpeek( cardStack[k] );
        if( CARDval(c) == suitVal[CARDsuit(c)] + 1 ) {
            return lastSugest = ACTIONcreateTargetless(k);
        }
    }
    
    for( i = 0; i < 11; i++ ) {
        if( STACKempty( cardStack[i] ) )
            continue;
        c = STACKpeek( cardStack[i] );
        for( k = i + 1; k < 12; k++ ) {
            if( STACKempty( cardStack[k] ) )
                continue;
            if( CARDsuit(c) == CARDsuit( STACKpeek( cardStack[k] ) )
                && CARDval(c) == CARDval( STACKpeek( cardStack[k] ) ) - 1 )
                return lastSugest = ACTIONcreate( i, k, 1 );
        }
    }
    return ACTIONcreate( -1, -1, -1 );
}

/* Imprime na tela o tabuleiro atual. */
void CRUELprint() {
    int i;
    for( i = 0; i < 4; i++ ) {
        if( STACKempty(suitStack[i]) )
            printf("     ");
        else
            CARDprint(STACKpeek(suitStack[i]));
    }
    printf("\n------------------\n");
    for( i = 0; i < 12; i++ ) {
        if( STACKempty(cardStack[i]) )
            printf("     ");
        else
            CARDprint(STACKpeek(cardStack[i]));
        if( i % 4 == 3 )
            printf("\n");
    }
}

void CRUELdebug(int i) {
    if( i > 0 ) {
        STACKdump(cardStack[ i - 1]);
    } else if( i < 0 ) {
        STACKdump(suitStack[-i - 1]);
    }
}
