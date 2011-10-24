/*******************************************************************/
/** MAC 122 - Principios de Desenvolvimento de Algoritmos         **/
/** IME-USP - Segundo Semestre de 2009                            **/
/**                                                               **/
/** Primeiro Exercocio-Programa -- Conjectura 3n + 1              **/
/** Arquivo: conjectura.c                                         **/                                             
/**                                                               **/
/** Henrique Gemignani Passos Lima    n� USP: ???????             **/
/**                                                               **/
/** 22/08/2009                                                    **/
/*******************************************************************/


#include <stdio.h>
#include <stdlib.h>
int main() {
	unsigned long inputLength = 0; // N�mero de intervalos da entrada.
	unsigned long vectorLength = 2; // Tamanho do vetor de intervalos dispon�vel.
	unsigned long inputNumber = 0; // Quantidade de n�meros distintos da uni�o de todos os intervalos da entrada.
	unsigned long long MIN = 0, MAX = 0, i = 0, x = 0, a = 0, q = 0, r = 0;
	long * RESULTS;
	unsigned long long * START, * END, * VALUES;
	START = (unsigned long long*) malloc( vectorLength * sizeof( long long ) );
	END = (unsigned long long*) malloc( vectorLength * sizeof( long long ) );
	
	// Le todos os intervalos da entrada e armazena em START e END
	// Preenche MIN e MAX com o menor in�cio e o maior t�rmino de intervalos.
	while( 1 ) {
		scanf(" %llu", &i );
		if( i == 0 ) break; // Finaliza a leitura da entrada.
		
		if( inputLength >= vectorLength ) { // Necessita-se aumentar o tamanho do vetor de intervalos.
			vectorLength *= 2;
			START = realloc( START, vectorLength * sizeof( long long ) );
			END = realloc( END, vectorLength * sizeof( long long ) );
		}
		
		START[inputLength] = i;
		scanf(" %llu", &i );
		END[inputLength] = i;
		
		if( START[inputLength] < MIN || MIN == 0 ) MIN = START[inputLength];
		if( END[inputLength]   > MAX || MAX == 0 ) MAX = END[inputLength];
		inputLength++;
	}
	vectorLength = END[0] - START[0] + 1; // Estima a quantidade de n�meros distintos de todos os intevalos pelo primeiro intervalo.
	VALUES = malloc( vectorLength * sizeof( long long ) );
	for( i = MIN; i <= MAX; i++ ) for( a = 0; a < inputLength; a++ )
		if( START[a] <= i && i <= END[a] ) {
			if( inputNumber >= vectorLength ) { // Necessita-se aumentar o tamanho do vetor de n�meros.
				vectorLength *= 2;
				VALUES = realloc( VALUES, vectorLength * sizeof( long long ) );
			}
			VALUES[ inputNumber ] = i;
			inputNumber++;
			break;
		}
	// N�o necessitamos saber sobre os intervalos mais.
	free(START);
	free(END);
	RESULTS = malloc( inputNumber * sizeof( long long ) );
	for( i = 0; i < inputNumber; i++ ) {
		RESULTS[i] = 0;
		// Seja X o n�mero a ser testado, podemos escrever X da forma 4q + r.
		x = VALUES[i];
		q = x / 4;
		r = x % 4;
		while( x > 1 ) {
			if( x < 4 ) { // Caso x seja menor que 4, o mais funcional � uma aplica��o direta da f�rmula.
				if( x % 2 == 0 )
					x /= 2;
				else
					x = 3*x + 1;
				RESULTS[i]++;
				q = x / 4;
				r = x % 4;
				continue;
			}
			
			switch( r ) {
				case 0: // r == 0:
					//  Sendo X = 4q + 0, f(f(x)) = q = X' = 4q' + r', logo q' = q/4 e r' = q % 4.
					r = q % 4;
					q = q / 4;
					RESULTS[i] += 2;
					break;
					
				case 1: // r == 1:
					//  Sendo X = 4q + 1, f(x) = 3*(4q + 1) + 1 e f(f(x)) = 6q + 2, logo 
					// f(f(f(x))) = 3q + 1 = X' = 4q' + r'. Portanto r' = (3*(q / 4) + q % 4) % 4
					// e q' = 3*(q / 4) + q % 4.
					r = (3*q + 1) % 4;
					q = (3*q + 1) / 4;
					RESULTS[i] += 3;
					break;
					
				case 2: // r == 2:
					//  Sendo X = 4q + 2, f(x) = 2q + 1 = X' = 4q' + r'. Portanto, r' = q % 2 e q' = q / 2.
					r = (2* q + 1) % 4;
					q = (2* q + 1) / 4;
					RESULTS[i] += 1;
					break;
					
				case 3: // r == 3:
					//  Sendo X = 4q + 3, f(x) = 12q + 10 e f(f(x)) = 6q + 5 = X' = 4q' + r'.
					// Logo, q' = 3q/2 + 1 e r' = (6q + 5) % 4 = (6q % 4 + 1) % 4 = (2*(3q % 2) + 1) % 4
					r = (2*(3*q % 2) + 1) % 4;
					q = (3*q) / 2 + 1;
					RESULTS[i] += 2;
					break;
			}
			x = 4*q + r;
		}
		printf("%llu %ld\r\n", VALUES[i], RESULTS[i] );
	}
	return 0;
}
