/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao                          **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Primeiro Exercicio-Programa -- Linguagem de Montagem          **/
/** Arquivo: main.c                                               **/
/**                                                               **/
/** Henrique Gemignani Passos Lima         nUSP: 6879634          **/
/** Renan Teruo Carneiro                   nUSP: 6514157          **/
/** 31/03/2010                                                    **/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *args[] ) {
  unsigned short int p, r;
  char *entrada, *saida;
  int resp;
  int filtra_os_primos (unsigned short int p, unsigned short int r, char * nome_arquivo_entrada, char * nome_arquivo_saida);
  if( argc != 5 ) {
    printf("Numero de parametros errado. (%d em vez de 4)\n", argc - 1);
    return 1;
  }
  p = (unsigned short int) atoi( args[1] );
  r = (unsigned short int) atoi( args[2] );
  entrada = args[3];
  saida = args[4];
  /* printf("OH NOES DEBUG\n"); */
  resp = filtra_os_primos(p, r, entrada, saida);
  printf("%d primo(s) encontrado(s).\n", resp);
  return 0;
}
