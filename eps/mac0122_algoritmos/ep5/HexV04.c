/**********************************************/
/* MAC122 - Quinto-Exercicio Programa: Hex    */
/*                                            */
/* Alunos:                                    */
/* André Santos de Medeiros         - ??????? */
/* Gustavo Teixeira da Cunha Coelho - ??????? */
/* Henrique Gemignani Passos Lima   - ??????? */
/* Renan Teruo Carneiro             - ??????? */
/**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BRANCO 1
#define PRETO 2
typedef struct _jogada{
     int i, j;
} jogada;

/* O tabuleiro do jogo. */
char tab[14][14];

/* Numero de jogadas que nosso time fez. */
int numJogada, numOponente;

int corDoTime;

int numeroRandom( int min, int max ) {
  /* Codigo abaixo tirado do PACA de MAC122 do ano passado*/
  return (((max-min) * ( (double) (1.0*rand()) / (double) (1.0*RAND_MAX + 1.0)))+min);
}

char jogadaValida( jogada jog ) {
  return (tab[ jog.i ][ jog.j ] == 0 && jog.i <= 13 && jog.i >=0 && jog.j <=13 && jog.j >= 0); /*POGamacao defensiva*/
}

time_t tempo( time_t *t ) { /* pra nao trocar o 'int time' de inicializaJogo */
  return time( t );
}

/* Com essa função, o programa fica sabendo em que time vai jogar.
  BRANCO: tenta fazer a linha na vertical (cima para baixo). Além
          disso, o time branco sempre começa o jogo.
	  PRETO: tenta fazer a linha na horizontal (esquerda para direita) */
void inicializaJogo(int time) {
  int i, j;
  for( i = 0; i < 14; i++ )
    for( j = 0; j < 14; j++ )
      tab[i][j] = 0;
  numJogada = numOponente = 0;
  corDoTime = time;
  srand(tempo(NULL));
  /* TODO: iniciar seed de random. *//*Done*/
}

/* Com essa função, o programa devolve a jogada que deseja fazer.
Para aplicar a Pie Rule, o time preto deve fazer a mesma jogada que o
time branco na primeira jogada. */
jogada novaJogada() { /* Ignora a PIE rule. */
  jogada jog;
  do {
    jog.i = numeroRandom( 0, 13 );
    jog.j = numeroRandom( 0, 13 );
  } while( !jogadaValida( jog ) );
  tab[ jog.i ][ jog.j ] = corDoTime;
  numJogada++;
  return jog;
}

/* Com essa função, o programa recebe a jogada do adversário. */
void recebeJogada(jogada jog) {
  if(numOponente==0 && corDoTime==BRANCO){
    corDoTime=PRETO;
    numJogada--;
  }
  tab[ jog.i ][ jog.j ] = 3 - corDoTime; /* Cor do adversario. */
  numOponente++;
}

void imprimeTab()
{
  int i,j;
  for(i=0;i<14;i++)
  {
    for(j=0;j<i;j++)
      printf(" ");
    for(j=0;j<14;j++)
    {
      if (tab[i][j]==0)  printf(".");
      if (tab[i][j]==BRANCO) printf("X");
      if (tab[i][j]==PRETO) printf("O");
    }
    printf("\n");
  }
}

int main( ) {
  int cor;
  jogada jog;
  printf("Cor do PC: ");
  do {
    scanf(" %d", &cor );
  } while( cor < 1 && cor > 2 );
  inicializaJogo( cor );
  if( corDoTime == BRANCO ) {
    jog = novaJogada();
    printf("Joguei: inicializaJogo(%d,%d)\n", jog.i, jog.j );
    imprimeTab();
  }
  while( numJogada + numOponente <= 14*14 ) {
    printf("Voce: ");
    scanf(" %d %d", &jog.i, &jog.j );
    recebeJogada( jog );

    jog = novaJogada();
    printf("Joguei: inicializaJogo(%d,%d)\n", jog.i, jog.j );
    imprimeTab();
  }
  return 0;
}
