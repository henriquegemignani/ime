/* ime2009bcc
   5s7B2P0k   */
#include <stdio.h>
#include <stdlib.h>

/* Definição de constantes */
#define PILHA_INIC_SIZE	32
#define DIR_CIMA		1
#define DIR_DIREITA		2
#define DIR_BAIXO		3
#define DIR_ESQUERDA	4

/* easter egg */
#define GOKU_POWER_LEVEL 9001
int VERBOSE = 0;
/* Matriz é dada por MATRIZ[LINHA][COLUNA]
	Geralmente, X ou I é utilizado para armazenar a LINHA,
	enquanto Y ou J para a COLUNA. */

void masterError( char* str ) {
	printf("%s\n",str);
	exit(1);
}
#define getBit(t,i) ( ( (t) & (1 << (i)) ) != 0 )
struct pontoData {
	int x, y;
};
typedef struct pontoData* ponto;
ponto createPonto( int x, int y ) {
	ponto p = malloc( sizeof(struct pontoData) );
	if( !p ) masterError("Impossivel alocar memória para um novo ponto.");
	p->x = x;
	p->y = y;
	return p;
}
void copiaValoresPonto( ponto target, ponto source ) {
	target->x = source->x;
	target->y = source->y;
}
/*=======================================*/
/* Funções relacionadas à estrutura item */
struct itemData {
    ponto p;
	char dir;
};
typedef struct itemData* item;
item createItem( int x, int y, char dir ) {
	item it = malloc( sizeof(struct itemData) );
	if( !it ) masterError("Impossivel alocar memória para um novo item.");
	it->p = createPonto( x, y );
	it->dir = dir;
	return it;
}
void copiaValoresItem( item target, item source ) {
	target->p->x = source->p->x;
	target->p->y = source->p->y;
	target->dir = source->dir;
}
item cloneItem( item it ) {
	item clone = createItem( -1, -1, 0 );
	copiaValoresItem( clone, it );
	return clone;
}
void limpaItem( item *it ) {
	free( (*it)->p );
	free( *it );
	*it = NULL;
}

/*=======================================*/
/* Funções relacionadas à pilha          */
struct pilhaStr {
	item* vetor;
	item** permVect;
	int* permSize;
	int topo, tamanho;
};
typedef struct pilhaStr* pilha;


pilha criaPilha( int tamanhoInic ) {
	pilha p = malloc( sizeof(struct pilhaStr) );
	if( !p ) masterError("Impossivel alocar memória para a pilha.\n");
	
	/* Vetor da Pilha */
	p->vetor = malloc( tamanhoInic * sizeof(item) );
	if( !p->vetor ) masterError("Impossivel alocar memória para o vetor da pilha.\n");
	
	/* Matriz de acoes invalidas */
	p->permVect = malloc( tamanhoInic * sizeof(item*) );
	if( !p->permVect ) masterError("Impossivel alocar memória para a matriz da pilha.\n");
	
	/* Vetor com o tamanho de cada linha da matriz de acoes invalidas */
	p->permSize = malloc( tamanhoInic * sizeof(int) );
	if( !p->permSize ) masterError("Impossivel alocar memória para a vetor do tamanho da matriz da pilha.\n");
	
	
	int i;
	for( i = 0; i < tamanhoInic; i++ ) {
		p->vetor[i] = createItem( -1, -1, 0 ); /* A pilha em si */
		p->permVect[i] = malloc( sizeof(item) ); /* Cada linha da matriz de acoes invalidas */
		if( !p->permVect[i] ) masterError("Impossivel alocar linha da matriz da pilha.");
		p->permVect[i][0] = createItem( -1, -1, 0 );
		p->permSize[i] = 1;
	}
	p->topo = 0;
	p->tamanho = tamanhoInic;
	return p;
}
void empilha( pilha p, item it ) {
	int i;
	if( p->topo == p->tamanho ) { /* aumentar vetor da pilha */
		i = p->tamanho;
		p->tamanho *= 2;
		item* aux = realloc( p->vetor, p->tamanho * sizeof(item) );
		if( !aux ) masterError("Impossivel alocar memória para expandir o vetor da pilha.\n");
		p->vetor = aux;
		for( ; i < p->tamanho; i++ ) {
			p->vetor[i] = createItem( -1, -1, 0 ); /* A pilha em si */
			p->permVect[i] = malloc( sizeof(item) ); /* Cada linha da matriz de acoes invalidas */
			if( !p->permVect[i] ) masterError("Impossivel alocar linha da matriz da pilha."); 
			p->permVect[i][0] = createItem( -1, -1, 0 );
			p->permSize[i] = 1;
		}
		if( VERBOSE ) printf("Aumentou tamanho da pilha para %d\n", p->tamanho);
	}
	copiaValoresItem( p->vetor[p->topo], it );
	for( i = 0; i < p->permSize[p->topo]; i++ )
		limpaItem( &p->permVect[p->topo][i] );
	p->permVect[p->topo][0] = createItem( -1, -1, 0 );
	p->permSize[p->topo] = 1;
	p->topo++;
}
void desempilha( pilha p ) {
	p->topo--;
}
item topoPilha( pilha p ) {
	return p->vetor[p->topo-1];
}
char pilhaVazia( pilha p ) {
	return (p->topo == 0);
}

/*===============================*/
void adcionaAcaoErrada( pilha p, ponto tar, char dir ) {
	if( pilhaVazia( p ) ) return; /* Chamada Invalida. */
	int cur = p->topo - 1, i;
	for( i = 0; i < p->permSize[cur] && ( p->permVect[cur][i]->dir != 0 ); i++ );
	if( i == p->permSize[cur] ) {
		p->permSize[cur] *= 2;
		item* aux = realloc( p->permVect[cur], p->permSize[cur] * sizeof(item) );
		if( !aux ) masterError("Impossivel alocar memória para expandir uma linha da matriz da pilha.\n");
		p->permVect[cur] = aux;
		/* iniciliza o resto */
		int j;
		for( j = i; j < p->permSize[cur]; j++ )
			p->permVect[cur][j] = createItem( -1, -1, 0 );
	}
	copiaValoresPonto( p->permVect[cur][i]->p, tar );
	p->permVect[cur][i]->dir = dir;
}
char isAcaoErrada( pilha p, ponto tar, char dir ) {
	int i, cur = p->topo - 1;
	if( cur < 0 ) return 0;
	for( i = 0; i < p->permSize[cur]; i++ ) {
		if( dir == p->permVect[cur][i]->dir && tar->x == p->permVect[cur][i]->p->x && tar->y == p->permVect[cur][i]->p->y )
			return 1;
	}
	return 0;
}

/*=======================================*/
/* Declaração de variáveis globais       */
unsigned short int TAMANHO_X_MATRIZ = 7, TAMANHO_Y_MATRIZ = 7;
char **pecas;
unsigned int numPecas = 0, numBuracos = 0;
unsigned long long numIteracoes = 0;
/* PILHA */
pilha respPilha;

/*=======================================*/
/* Codigo para resolução do problema     */

/* Dado as coordenadas (X,Y) de um valor da matriz global "pecas" e uma direção DIR,
	devolve 1 se é possivel fazer uma jogada no ponto dado com a direção dada,
	e 0 caso contrário. */
char acaoValida( ponto p, char dir ) {
	int x = p->x, y = p->y;
	switch( dir ) {
		case DIR_CIMA:
			if( y < 2 || pecas[y - 2][x] != 1 || pecas[y - 1][x] != 1 || pecas[y][x] != 0 )
				return 0;
			return 1;
		case DIR_DIREITA:
			if( x > TAMANHO_X_MATRIZ - 3 || pecas[y][x + 2] != 1 || pecas[y][x + 1] != 1 || pecas[y][x] != 0 )
				return 0;
			return 1;
		case DIR_BAIXO:
			if( y > TAMANHO_Y_MATRIZ - 3 || pecas[y + 2][x] != 1 || pecas[y + 1][x] != 1 || pecas[y][x] != 0 )
				return 0;
			return 1;
		case DIR_ESQUERDA:
			if( x < 2 || pecas[y][x - 2] != 1 || pecas[y][x - 1] != 1 || pecas[y][x] != 0 )
				return 0;
			return 1;
	}
	return 0;
}
void realizaAcao( int x, int y, char dir ) {
	numPecas--;
	numBuracos++;
	switch( dir ) {
		case DIR_CIMA:
			pecas[y][x] = 1;
			pecas[y - 1][x] = 0;
			pecas[y - 2][x] = 0;
			return;
		case DIR_DIREITA:
			pecas[y][x] = 1;
			pecas[y][x + 1] = 0;
			pecas[y][x + 2] = 0;
			return;
		case DIR_BAIXO:
			pecas[y][x] = 1;
			pecas[y + 1][x] = 0;
			pecas[y + 2][x] = 0;
			return;
		case DIR_ESQUERDA:
			pecas[y][x] = 1;
			pecas[y][x - 1] = 0;
			pecas[y][x - 2] = 0;
			return;
	}
}
void desfazAcao( int x, int y, char dir ) {
	numPecas++;
	numBuracos--;
	switch( dir ) {
		case DIR_CIMA:
			pecas[y][x] = 0;
			pecas[y - 1][x] = 1;
			pecas[y - 2][x] = 1;
			return;
		case DIR_DIREITA:
			pecas[y][x] = 0;
			pecas[y][x + 1] = 1;
			pecas[y][x + 2] = 1;
			return;
		case DIR_BAIXO:
			pecas[y][x] = 0;
			pecas[y + 1][x] = 1;
			pecas[y + 2][x] = 1;
			return;
		case DIR_ESQUERDA:
			pecas[y][x] = 0;
			pecas[y][x - 1] = 1;
			pecas[y][x - 2] = 1;
			return;
	}
}
char encontraBuraco( ponto p, item resp, int* aux ) {
	int x = *aux % TAMANHO_Y_MATRIZ, y = *aux / TAMANHO_Y_MATRIZ;
	for( ; y < TAMANHO_Y_MATRIZ; y++ ) {
		for( ; x < TAMANHO_X_MATRIZ; x++ ) {
			if( pecas[y][x] == 0 ) {
				resp->p->x = x;
				resp->p->y = y;
				resp->dir = 0;
				return 1;
			}
			(*aux)++;
		}
		x = 0;
	}
	return 0;
}
void imprimeTabuleiro() {
	int x, y;
	for( y = 0; y < TAMANHO_Y_MATRIZ; y++ ) {
		for( x = 0; x < TAMANHO_X_MATRIZ; x++ ) {
			printf("%d ", pecas[y][x]);
		}
		printf("\n");
	}
}

int main(void) {
	scanf(" %hu %hu", &TAMANHO_X_MATRIZ, &TAMANHO_Y_MATRIZ );
	int x, y;
	char dir;
	pecas = (char**) malloc( TAMANHO_Y_MATRIZ * sizeof(char*) );
	if( !pecas ) masterError("Impossivel alocar memória para as linhas da matriz pecas.\n");
	for( y = 0; y < TAMANHO_Y_MATRIZ; y++ ) {
		pecas[y] = (char*) malloc( TAMANHO_X_MATRIZ * sizeof(char) );
		if( !pecas[y] ) masterError("Impossivel alocar memória para as colunas da linha Y matriz pecas.\n");
		for( x = 0; x < TAMANHO_X_MATRIZ; x++ ) {
			scanf(" %hd", (short int*) &pecas[y][x] );
			if( pecas[y][x] == 1 )
				numPecas++;
			else if( pecas[y][x] == 0 )
				numBuracos++;
		}
	}
	
	x = 0; y = 0; dir = 1;
	ponto curPonto = createPonto( 0, 0 );
	item it = createItem( 0, 0, 1 );
	int aux = 0;
	respPilha = criaPilha( PILHA_INIC_SIZE );
	
	VERBOSE = 0;
	while( numPecas > 1 ) {
		/*if( numIteracoes + 5 >= 10000 ) VERBOSE = 1; */
		if( VERBOSE ) printf("Loop: %d pecas\n", numPecas );
		aux = 0;
		while( GOKU_POWER_LEVEL > 9000 ) {
			if( VERBOSE ) printf("\tBusca > ");
			if( !encontraBuraco( curPonto, it, &aux ) ) {
				if( pilhaVazia( respPilha ) ) {
					printf("Tabuleiro sem solucao.\n");
					/* libera memória */
					exit(0);
				}
				/* não há mais buracos no tabuleiro. Backtrack */
				copiaValoresItem( it, topoPilha( respPilha ) );
				if( VERBOSE ) printf("Backtrack (%d,%d,%d)", it->p->x, it->p->y, (int) it->dir );
				desempilha( respPilha );
				adcionaAcaoErrada( respPilha, it->p, it->dir );
				desfazAcao( it->p->x, it->p->y, it->dir );
				aux = it->p->y * TAMANHO_Y_MATRIZ + it->p->x;
			} else if( VERBOSE ) {
				printf("(%d,%d)", it->p->x, it->p->y );
			}
			if( VERBOSE ) printf(" Dir: ");
			for( dir = 1; dir <= 4; dir++ ) {
				if( acaoValida( it->p, dir ) ) {
					if( !isAcaoErrada( respPilha, it->p, dir ) ) {
						break;
					} else {
						if( VERBOSE ) printf("[%d,BT] ", dir );
					}
				} else {
					if( VERBOSE ) printf("[%d,IN] ", dir );
				}
			}
			if( (int) dir <= 4 ) {
				if( VERBOSE ) printf("[%d,OK]\n", (int) dir );
				it->dir = dir;
				break;
			}
			if( VERBOSE ) printf("\n");
			aux++;
		}
		
		if( VERBOSE ) printf("\tEmpilhando (%d,%d,%d)... ", it->p->x, it->p->y, (int) it->dir);
		empilha( respPilha, it );
		if( VERBOSE ) printf("Sucesso!\n");
		if( VERBOSE ) printf("\tAtualizando Tabuleiro... ");
		realizaAcao( it->p->x, it->p->y, it->dir );
		if( VERBOSE ) printf("Sucesso!\n");
		copiaValoresPonto( curPonto, it->p );
		numIteracoes++;
		if( numIteracoes % 5000 == 0 && 0 ) {
			int i, j;
			imprimeTabuleiro();
			printf("[i]\t(x,y,dir): ERRORS\n");
			for( i = 0; i < respPilha->topo; i++ ) {
				printf("[%d]\t(%d,%d,%d)\t", i, respPilha->vetor[i]->p->x, respPilha->vetor[i]->p->y, (int) respPilha->vetor[i]->dir );
				for( j = 0; j < respPilha->permSize[i] && respPilha->permVect[i][j]->dir != 0 && j < 10; j++ )
					printf("(%d,%d,%d);", respPilha->permVect[i][j]->p->x, respPilha->permVect[i][j]->p->y, (int) respPilha->permVect[i][j]->dir );
				printf("\n");
			}
			/*exit(1); */
		}
	}
	while( !pilhaVazia( respPilha ) ) {
		it = topoPilha( respPilha );
		printf("(%d,%d,%d)\n", it->p->x, it->p->y, (int) it->dir );
		desempilha( respPilha );
	}
	imprimeTabuleiro();
	return 0;
}