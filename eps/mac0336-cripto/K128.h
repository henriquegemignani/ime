#ifndef K128_H_
#define K128_H_

#include "types.h"

lbyte primeirosNbits(lbyte l, unsigned int N);

void operacao_ponto(lbyte a[], lbyte b[], lbyte saida[]);
void operacao_soma64(lbyte a[], lbyte b[], lbyte saida[]);
void operacao_xor(lbyte a[], lbyte b[], lbyte saida[]);
void operacao_rotacao(lbyte a[], unsigned int b, lbyte s[]);

void K128_Iteracao_Parte1(lbyte Xa[], lbyte Xb[], lbyte XaL[], lbyte XbL[], lbyte kA[], lbyte kB[]);
void K128_Iteracao_Parte2(lbyte Xe[], lbyte Xf[], lbyte XeL[], lbyte XfL[], lbyte kE[], lbyte kF[]);
void K128_Iteracao(lbyte entrada[], lbyte saida[], lbyte** chaves);
void GeraSubChaves(lbyte K[], lbyte* K_lista[]);
void K128_R12(lbyte entrada[], lbyte saida[], lbyte chave[]);


#endif /* K128_H_ */
