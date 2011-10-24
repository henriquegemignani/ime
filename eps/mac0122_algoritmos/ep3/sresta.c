/*******************************************************************/
/** MAC 122 - Principios de Desenvolvimento de Algoritmos         **/
/** IME-USP - Segundo Semestre de 2009                            **/
/**                                                               **/
/** Terceiro Exercocio-Programa -- Resta Um                       **/
/** Arquivo: sresta.c                                             **/                                             
/**                                                               **/
/** Henrique Gemignani Passos Lima    nº USP: ???????             **/
/**                                                               **/
/** 22/08/2009                                                    **/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>

/************************************************************************************************************************
  O programa ira primeiro ler dois inteiros de 1 a 64, que representam o tamanho X e Y do tabuleiro, respetivamente.
  Depois, o programa lera Y linhas de X numeros representando o tabuleiro.
	Utilize 1 para a presenca de uma peca, 0 para de um buraco e qualquer outra coisa para indicar que esse
	  ponto nao existe.


 Cada ponto possui uma coordenada X e Y, com ambos no intervalo [1,64].
 Portanto, para armazenar cada uma das coordenadas, eh necessario
  apenas 6 bits (2^6 = 64).
 A direcao pode ser armazenada em 2 bits (2^2 = 4 = Numero de direcoes),
  levando a um total de 14 bits para cada terna (X,Y,DIR), o que torna
  possivel armazenar tal terna em apenas um SHORT INT (16 bits).
  
 Dado um short int TERNA que possui informacoes de uma jogada (X,Y,DIR),
  as informacoes podem ser adquiridas de tal forma:
 coordX = (TERNA >> 2 ) & 0000000000111111 -> coordX = (TERNA >> 2) & 63
 coordY = (TERNA >> 8 ) & 0000000000111111 -> coordY = (TERNA >> 8) & 63
 dir    = (TERNA >> 0 ) & 0000000000000011 -> dir    = (TERNA     ) &  3
  0000000100000000
****************int i;*********************************************************************************************************/
#define _TERNA_X(   TERNA ) ( ((TERNA) >> 2 ) & 63 )
#define _TERNA_Y(   TERNA ) ( ((TERNA) >> 8 ) & 63 )
#define _TERNA_DIR( TERNA ) ( (TERNA) & 3 )

char valorEm( char tab[64][64], short terna ) {
	return tab[ _TERNA_Y( terna ) ][ _TERNA_X( terna ) ];
}

void masterError( char* str ) {
	printf("%s\n",str);
	exit(1);
}

#define CIMA		3
#define DIREITA		0
#define ESQUERDA	1
#define BAIXO		2

#define BURACO	0
#define PECA	1

short tamX, tamY, numBuraco = 0, numPeca = 0, pilha[4096], topo = 0;
char tab[64][64];

void imprimeTabuleiro() {
	int x, y;
	for( y = 0; y < tamY; y++ ) {
		for( x = 0; x < tamX; x++ ) {
			printf("%c ", tab[y][x] == PECA ? 'X' :	tab[y][x] == BURACO ? '*' : ' ' );
		}
		printf("\n");
	}
}

/* Empilha uma jogada. A pilha eh global. */
void empilha( short terna ) {
	if( topo >= 4096 ) masterError("Pilha com tamanho anormal.");
	pilha[topo] = terna;
	topo++;
}

/* Devolve a ultima jogada empilhada. */
short topoDaPilha(void) {
	return ( topo > 0 ? pilha[ topo - 1 ] : 0 );
}

/* 1 se a pilha esta vazia, 0 caso contrario. */
char pilhaVazia(void) {
	return ( topo == 0 );
}

/* Desempilha a ultima jogada. */
void desempilha(void) {
	topo--;
}

/* Devolve a (i+1)-esima letra do alfabeto. */
#define letra( i ) ( 'A' + (i) )

/* Devolve uma terna da forma ( x, y, dir ). */
short criaTerna( short x, short y, char dir ) {
	return ( (y << 8) + (x << 2) + dir );
}

/* Devolve a terna do destino de terna. */
short destinoJogada( short terna ) {
	char dir = _TERNA_DIR( terna );
	switch( dir ) {
		case CIMA:		return ( terna - 512 );
		case DIREITA:	return ( terna +   8 );
		case ESQUERDA:	return ( terna -   8 );
		case BAIXO:		return ( terna + 512 );
	}
	return -1;
}

/* A terna da forma ( X(terna), Y(terna), dir ) eh uma jogada valida. */
char jogadaValida( short terna, char dir ) {
	switch( dir ) {
		case CIMA:
			return( ( _TERNA_Y( terna ) >= 2 )
				&& ( valorEm( tab, terna - 256 ) == PECA   )     /* 256 == 00 000001 000000 00 */
				&& ( valorEm( tab, terna - 512 ) == BURACO ) );  /* 512 == 00 000010 000000 00 */
		case DIREITA:
			return( ( _TERNA_X( terna ) < tamX - 2 )
				&& ( valorEm( tab, terna +   4 ) == PECA   )     /*   4 == 00 000000 000001 00 */
				&& ( valorEm( tab, terna +   8 ) == BURACO ) );  /*   8 == 00 000000 000010 00 */
		case ESQUERDA:
			return( ( _TERNA_X( terna ) >= 2 )
				&& ( valorEm( tab, terna -   4 ) == PECA   )     /*   4 == 00 000000 000001 00 */
				&& ( valorEm( tab, terna -   8 ) == BURACO ) );  /*   8 == 00 000000 000010 00 */
		case BAIXO:
			return( ( _TERNA_Y( terna ) < tamY - 2 )
				&& ( valorEm( tab, terna + 256 ) == PECA   )     /* 256 == 00 000001 000000 00 */
				&& ( valorEm( tab, terna + 512 ) == BURACO ) );  /* 512 == 00 000010 000000 00 */
	}
	return 0;
}

/* Altera o tabuleiro realizando a jogada ( X(terna), Y(terna), dir ). */
void realizaJogada( short terna, char dir ) {
	short x = _TERNA_X( terna ), y = _TERNA_Y( terna );
	numPeca--;
	numBuraco++;
	switch( dir ) {
		case CIMA:
			tab[ y     ][ x ] = BURACO;
			tab[ y - 1 ][ x ] = BURACO;
			tab[ y - 2 ][ x ] = PECA;
			break;

		case DIREITA:
			tab[ y ][ x     ] = BURACO;
			tab[ y ][ x + 1 ] = BURACO;
			tab[ y ][ x + 2 ] = PECA;
			break;

		case ESQUERDA:
			tab[ y ][ x     ] = BURACO;
			tab[ y ][ x - 1 ] = BURACO;
			tab[ y ][ x - 2 ] = PECA;
			break;

		case BAIXO:
			tab[ y     ][ x ] = BURACO;
			tab[ y + 1 ][ x ] = BURACO;
			tab[ y + 2 ][ x ] = PECA;
			break;
	}
}

/* Altera o tabuleiro desfazendo a jogada ( X(terna), Y(terna), dir ). */
void desfazJogada( short terna, char dir ) {
	short x = _TERNA_X( terna ), y = _TERNA_Y( terna );
	numPeca++;
	numBuraco--;
	switch( dir ) {
		case CIMA:
			tab[ y     ][ x ] = PECA;
			tab[ y - 1 ][ x ] = PECA;
			tab[ y - 2 ][ x ] = BURACO;
			break;


		case DIREITA:
			tab[ y ][ x     ] = PECA;
			tab[ y ][ x + 1 ] = PECA;
			tab[ y ][ x + 2 ] = BURACO;
			break;

		case ESQUERDA:
			tab[ y ][ x     ] = PECA;
			tab[ y ][ x - 1 ] = PECA;
			tab[ y ][ x - 2 ] = BURACO;
			break;

		case BAIXO:
			tab[ y     ][ x ] = PECA;
			tab[ y + 1 ][ x ] = PECA;
			tab[ y + 2 ][ x ] = BURACO;
			break;
	}
}

int main( int argc, const char* argv[] ) {
	short x, y, atual = 0, alvo, meio;
	unsigned long numBacktrack = 0;
	char dir, *direcoes[4];
	direcoes[CIMA]     = "CIMA    ";
	direcoes[DIREITA]  = "DIREITA ";
	direcoes[ESQUERDA] = "ESQUERDA";
	direcoes[BAIXO]    = "BAIXO   ";

	scanf(" %hd %hd", &tamY, &tamX );
	for( y = 0; y < tamY; y++ ) {
		for( x = 0; x < tamX; x++ ) {
			scanf(" %hd", (short int*) &tab[y][x] );
			if( tab[y][x] == BURACO )
				numBuraco++;
			else if( tab[y][x] == PECA )
				numPeca++;
		}
	}
	
	imprimeTabuleiro();
	while( numPeca > 1 ) {
		if( valorEm( tab, atual ) == PECA ) {
			dir = _TERNA_DIR( atual );
			atual -= dir;
			for( ; dir < 4; dir++ ) {
				if( jogadaValida( atual, dir ) /*&& !jogadaErrada( atual, dir ) */ )
					break;
			}
			if( dir < 4 ) {
				/* achei uma terna valida! */
				empilha( atual + dir );
				realizaJogada( atual, dir );
				atual = 0;
				continue;
			}
		}
		atual += 4; /* 4 == 00 000000 000001 00 */
		if( _TERNA_X( atual ) >= tamX ) {
			/* fim da linha, ir para a proxima */
			atual += 256;   /*   256 == 00 000001 000000 00 */
			atual &= 32515; /* 32515 == 01 111111 000000 11 */
		}
		if( _TERNA_Y( atual ) >= tamY || (atual >> 14) ) {
			/* fim da ultima linha. BACKTRACKZ! */
			if( pilhaVazia() ) {
				printf("IMPOSSIVEL\n");
				exit(0);
			}
			atual = topoDaPilha();
			desempilha();
			desfazJogada( atual, _TERNA_DIR( atual ) );
			atual++;
			numBacktrack++;
			if( numBacktrack % 2000 == 0 ) /* pog anti-spam */
				printf("Desfaz( %d, %d, %s ); Resta %d\n", _TERNA_X( atual ) + 1, _TERNA_Y( atual ) + 1, direcoes[ _TERNA_DIR( atual ) ], numPeca );
		}
	}
	printf("Solucao:\n");
	for( x = 0; x < topo; x++ ) {
		alvo = destinoJogada( pilha[x] );
		meio = criaTerna( ( _TERNA_X( pilha[x] ) + _TERNA_X( alvo ) ) / 2, ( _TERNA_Y( pilha[x] ) + _TERNA_Y( alvo ) ) / 2, 0 );
		printf("(%c%d, %c%d, %c%d)\n", 
			letra( _TERNA_X( pilha[x] ) ), _TERNA_Y( pilha[x] ),
			letra( _TERNA_X( meio )     ), _TERNA_Y( meio ),
			letra( _TERNA_X( alvo )     ), _TERNA_Y( alvo ) );
	}
	return 0;
}
