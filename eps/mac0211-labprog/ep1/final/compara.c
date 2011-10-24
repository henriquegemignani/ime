/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao                          **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Primeiro Exercicio-Programa -- Linguagem de Montagem          **/
/** Arquivo: compara.c                                            **/
/**                                                               **/
/** Henrique Gemignani Passos Lima         nUSP: 6879634          **/
/** Renan Teruo Carneiro                   nUSP: 6514157          **/
/** 05/04/2010                                                    **/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

/* O arquivo "gerador.c" deve estar no mesmo diretorio */
#define GERADOR_USING_FUNC_
#include "gerador.c"
void gerador( int num, char * file );

long long tv_2_ms(struct timeval *tv)
{
	return (long long)tv->tv_sec * 1000 + (long long)tv->tv_usec / 1000;
}

#define _GETTIME(var,tv) gettimeofday(&tv,NULL);var=tv_2_ms(&tv);

void printResults( long long time[6][10] ) {
    int i, j;
    long double media[6], dp;
    printf("10^n\t\t1\t\t2\t\t3\t\t4\t\t5\t\t6\n");
    printf("media");
    for( i = 0; i < 6; i++ ) {
        media[i] = 0;
        for( j = 0; j < 10; j++ )
            media[i] += time[i][j];
        media[i] /= 10;
        printf("\t%5.7Lf", media[i]);
    }
    printf("\ndesvio");
    for( i = 0; i < 6; i++ ) {
        dp = 0;
        for( j = 0; j < 10; j++ )
            dp += (time[i][j] - media[i])*(time[i][j] - media[i]);
        dp = sqrt(dp / 9);
        printf("\t%5.7Lf", dp);
    }
    printf("\n");
}


int main() {
    int i, j, tam = 1;
    struct timeval tv;
    long long aft, bef;
    long long timeASM[6][10], timeC[6][10], timeDIF[6][10];
    
    fflush(stderr);
    for( i = 0; i < 6; i++ ) {
        tam *= 10;
        gerador( tam, "TEMPENTRADA.txt" );
        for( j = 0; j < 10; j++ ) {
            printf("Calculando o tempo para entrada de tamanho n^%d... %d de 10 feitos. [ASM]\r", i + 1, j);
            fflush(stdout);
            _GETTIME(bef, tv)
            system("./filtra 1 65535 TEMPENTRADA.txt TEMPSAIDA.txt > TEMPSAIDAEX.txt");
            _GETTIME(aft, tv);
            timeASM[i][j] = aft - bef;

            printf("Calculando o tempo para entrada de tamanho n^%d... %d de 10 feitos. [C]  \r", i + 1, j);
            fflush(stdout);
            _GETTIME(bef, tv)
            system("./cfiltra 1 65535 TEMPENTRADA.txt TEMPSAIDA.txt > TEMPSAIDAEX.txt");
            _GETTIME(aft, tv);
            timeC[i][j] = aft - bef;
            
            timeDIF[i][j] = timeC[i][j] - timeASM[i][j];
        }
    }
    printf("Calculando o tempo para entrada de tamanho n^6... 10 de 10 feitos.\nResultados (em milisegundos):\n\nAssembly\n");
    printResults(timeASM);
    printf("C\n");
    printResults(timeC);
    printf("Dif\n");
    printResults(timeDIF    );
    return 0;
}