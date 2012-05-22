#ifndef K128_H_
#define K128_H_

#include "types.h"

void inicializarVetoresFuncPonto(void);

lbyte primeirosNbits(lbyte l, unsigned int N);
lbyte ultimosNbits(lbyte l, unsigned int N);

void convert_lbyte_to_bytes(lbyte l, byte b[4]);
void convert_2lbytes_to_bytes(lbyte l[2], byte b[8]);
lbyte convert_bytes_to_lbyte(byte b[4]);
block64 convert_bytes_to_block64(byte b[8]);

/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com . dentro] */
void operacao_ponto(block64 a, block64 b, block64 *saida);
void operacao_ponto_inverso(block64 xL, block64 k, block64 *x);

/* a, b, saida: 64 bits (8 bytes) [no enunciado: quadrado com + dentro] */
void operacao_soma64(block64 a, block64 b, block64 *saida);
/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com + dentro] */
void operacao_xor(block64 a, block64 b, block64 *saida);
/* B: inteiro, a, saida: 64 bits (8 bytes) [no enunciado: <<] */
void operacao_rotacao(block64 a, unsigned int b, block64 *saida);
/* a, saida: 64 bits (8 bytes) */
void operacao_oposto_soma64(block64 a, block64 *saida);

/* a, b, saida: 64 bits (8 bytes) */
void operacao_rotacao_por_lbyte(block64 a, block64 b, block64 *saida);

void copy_block128(block128 a, block128* s);

void K128_Iteracao_Parte1(block64 Xa, block64 Xb, block64 *XaL, block64 *XbL, block64 kA, block64 kB);
void K128_Iteracao_Parte2(block64 Xe, block64 Xf, block64 *XeL, block64 *XfL, block64 kE, block64 kF);
void K128_Iteracao(block128 entrada, block128 *saida, block64 chaves[]);

void K128_Iteracao_Parte1_INV(block64 Xa, block64 Xb, block64 *XaL, block64 *XbL, block64 kA, block64 kB);
void K128_Iteracao_INV(block128 entrada, block128 *saida, block64 chaves[]);

void GeraSubChaves(block128 K, block64 K_lista[]);
void K128_Encrypt(block128 entrada, block128 *saida, block128 chave);
void K128_Decrypt(block128 entrada, block128 *saida, block128 chave);

void K128CBC_Encrypt(block128 entrada[], block128 saida[], block128 chave, int numblock);

void gera_chave_da_senha(char* senha, block128 *k);

#endif /* K128_H_ */
