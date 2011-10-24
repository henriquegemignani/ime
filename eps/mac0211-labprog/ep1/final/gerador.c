/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao                          **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Primeiro Exercicio-Programa -- Linguagem de Montagem          **/
/** Arquivo: gerador.c                                            **/
/**                                                               **/
/** Henrique Gemignani Passos Lima         nUSP: 6879634          **/
/** Renan Teruo Carneiro                   nUSP: 6514157          **/
/** 31/03/2010                                                    **/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void gerador( int num, char * file ) {
  int i;
  FILE *f;
  f=fopen(file,"w");
  srand(time(NULL));
  for(i=0; i< num; i++)
    fprintf(f,"%d ", (int)(0x10000 * ((double) (1.0*rand()) / (double) (1.0*RAND_MAX + 1.0))));
  fclose(f);
}

#ifndef GERADOR_USING_FUNC_

int main(int argc, char **argv){
  if(argc<3)
    return 1;
  gerador(atoi(argv[1]), argv[2]);
  return 0;
}

#endif
