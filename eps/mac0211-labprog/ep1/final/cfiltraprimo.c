/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao                          **/
/** IME-USP - Primeiro Semestre de 2010                           **/
/**                                                               **/
/** Primeiro Exercicio-Programa -- Linguagem de Montagem          **/
/** Arquivo: cfiltraprimo.c                                       **/
/**                                                               **/
/** Henrique Gemignani Passos Lima         nUSP: 6879634          **/
/** Renan Teruo Carneiro                   nUSP: 6514157          **/
/** 31/03/2010                                                    **/
/*******************************************************************/

#include <stdio.h>

char verifica_primo(unsigned short int p) {
    int i, c;
	if( p < 2 )
		return 0;
	if( p % 2 == 0 )
		return 0;
	if( p == 2 )
		return 1;
	for( i = 3, c = 9; c <= p; i += 2, c += i + i)
		if( p % i == 0 )
			return 0;
	return 1;
}

unsigned short int le_numero( FILE * source ) {
	unsigned short int resp = 0;
	int c = 1;
	while( (c = fgetc( source )) >= '0' && c <= '9') {
		resp = 10 * resp + (c - '0');
	}
	return resp;
}


int filtra_os_primos (unsigned short int p, unsigned short int r, char * nome_arquivo_entrada, char * nome_arquivo_saida) {
	FILE *entrada, *saida;
	int numPrimo = 0;
	unsigned short int num;
	entrada = fopen( nome_arquivo_entrada, "r" );
	saida = fopen( nome_arquivo_saida, "w" );
	
	while( !feof(entrada) ){
		num = le_numero( entrada );
		if( p <= num && r >= num && verifica_primo( num ) ) {
			fprintf( saida, "%hu ", num);
			numPrimo++;
		}
	}
	fclose( entrada );
	fclose( saida );
	return numPrimo;
}
