#ifndef K128_H_
#define K128_H_

#include "types.h"

void inicializarVetoresFuncPonto();

lbyte primeirosNbits(lbyte l, unsigned int N);
lbyte ultimosNbits(lbyte l, unsigned int N);

void convert_lbyte_to_bytes(lbyte l, byte b[4]);
lbyte convert_bytes_to_lbyte(byte b[4]);

/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com . dentro] */
void operacao_ponto(lbyte a[2], lbyte b[2], lbyte saida[2]);
/* a, b, saida: 64 bits (8 bytes) [no enunciado: quadrado com + dentro] */
void operacao_soma64(lbyte a[2], lbyte b[2], lbyte saida[2]);
/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com + dentro] */
void operacao_xor(lbyte a[2], lbyte b[2], lbyte saida[2]);
/* B: inteiro, a, saida: 64 bits (8 bytes) [no enunciado: <<] */
void operacao_rotacao(lbyte a[2], unsigned int b, lbyte s[2]);
/* a, saida: 64 bits (8 bytes) */
void operacao_oposto_soma64(lbyte a[2], lbyte saida[2]);

/* a, b, saida: 64 bits (8 bytes) */
void operacao_rotacao_por_lbyte(lbyte a[2], lbyte b[2], lbyte s[2]);

void K128_Iteracao_Parte1(lbyte Xa[2], lbyte Xb[2], lbyte XaL[2], lbyte XbL[2], lbyte kA[2], lbyte kB[2]);
void K128_Iteracao_Parte2(lbyte Xe[2], lbyte Xf[2], lbyte XeL[2], lbyte XfL[2], lbyte kE[2], lbyte kF[2]);
void K128_Iteracao(lbyte entrada[2], lbyte saida[2], lbyte chaves[][2]);

void K128_Iteracao_Parte1_INV(lbyte Xa[2], lbyte Xb[2], lbyte XaL[2], lbyte XbL[2], lbyte kA[2], lbyte kB[2]);
void K128_Iteracao_Parte2_INV(lbyte Xe[2], lbyte Xf[2], lbyte XeL[2], lbyte XfL[2], lbyte kE[2], lbyte kF[2]);
void K128_Iteracao_INV(lbyte entrada[2], lbyte saida[2], lbyte chaves[][2]);

void GeraSubChaves(lbyte K[4], lbyte K_lista[][2]);
void K128_Encrypt(lbyte entrada[4], lbyte saida[4], lbyte chave[4]);
void K128_Decrypt(lbyte entrada[4], lbyte saida[4], lbyte chave[4]);


#endif /* K128_H_ */
