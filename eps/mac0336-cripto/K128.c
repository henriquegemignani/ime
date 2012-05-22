#include <stdio.h>
#include <string.h>
#include "K128.h"

#define R 12
#define NUM_KEYS(R) (4*(R)+2)

static byte ponto_exp[256];
static byte ponto_log[256];

void adiciona_valor(byte x, byte y) {
    ponto_exp[x] = y;
    ponto_log[y] = x;
}

void inicializarVetoresFuncPonto(void) {
    unsigned int x, result = 1;
    adiciona_valor(0, 1);
    for(x = 1; x < 256; ++x) {
        result = (result * 45) % 257; 
        if(x == 128)
            adiciona_valor((byte) x, 0);
        else
            adiciona_valor((byte) x, (byte) result);
    }
}

void imprimeValoresPonto(void) {

}


lbyte primeirosNbits(lbyte l, unsigned int N) {
    lbyte mask = ((0x1uL << N) - 1) << (32 - N);
    return (l & mask) >> (32 - N);
}
lbyte ultimosNbits(lbyte l, unsigned int N) {
    lbyte mask = ((0x1uL << N) - 1);
    return (l & mask);
}

void convert_lbyte_to_bytes(lbyte l, byte b[4]) {
    b[0] = (byte)((l & 0xFF000000) >> 24);
    b[1] = (byte)((l & 0x00FF0000) >> 16);
    b[2] = (byte)((l & 0x0000FF00) >> 8);
    b[3] = (byte)((l & 0x000000FF));
}
void convert_2lbytes_to_bytes(lbyte l[2], byte b[8]) {
    convert_lbyte_to_bytes(l[0], b);
    convert_lbyte_to_bytes(l[1], b + 4);
}
void convert_block64_to_bytes(block64 l, byte b[8]) {
    b[0] = (byte)((l & 0xFF00000000000000) >> 56);
    b[1] = (byte)((l & 0x00FF000000000000) >> 48);
    b[2] = (byte)((l & 0x0000FF0000000000) >> 40);
    b[3] = (byte)((l & 0x000000FF00000000) >> 32);
    b[4] = (byte)((l & 0x00000000FF000000) >> 24);
    b[5] = (byte)((l & 0x0000000000FF0000) >> 16);
    b[6] = (byte)((l & 0x000000000000FF00) >> 8);
    b[7] = (byte)((l & 0x00000000000000FF));
}

lbyte convert_bytes_to_lbyte(byte b[4]) {
    lbyte result = 0;
    result |= (b[0] << 24);
    result |= (b[1] << 16);
    result |= (b[2] << 8);
    result |= b[3];
    return result;
}

block64 convert_bytes_to_block64(byte b[8]) {
    block64 result = 0;
    result |= ((block64)(b[0]) << 56);
    result |= ((block64)(b[1]) << 48);
    result |= ((block64)(b[2]) << 40);
    result |= ((block64)(b[3]) << 32);
    result |= ((block64)(b[4]) << 24);
    result |= ((block64)(b[5]) << 16);
    result |= ((block64)(b[6]) <<  8);
    result |= ((block64)(b[7])      );
    return result;
}

/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com . dentro] */
void operacao_ponto(block64 a, block64 b, block64 *saida) {
    byte aB[8], bB[8];
    int i;
    convert_block64_to_bytes(a, aB);
    convert_block64_to_bytes(b, bB);
    for(i = 0; i < 8; ++i) {
        aB[i] = ponto_exp[aB[i]];
        bB[i] = ponto_exp[bB[i]];
    }
    *saida = convert_bytes_to_block64(aB) ^ convert_bytes_to_block64(bB);
}
void operacao_ponto_inverso(block64 xL, block64 k, block64 *x) {
    /* X' = X (*) K -> X' = f(X) ^ f(K) -> X' ^ f(K) = f(X) -> 
       -> fINV(x' ^ f(K)) = fINV(f(X)) = X. */
    byte xLB[8], kB[8];
    int i;
    convert_block64_to_bytes(xL, xLB);
    convert_block64_to_bytes(k, kB);
    for(i = 0; i < 8; ++i)
        xLB[i] = ponto_log[xLB[i] ^ ponto_exp[kB[i]]];
    *x = convert_bytes_to_block64(xLB);
}

/* a, b, saida: 64 bits (8 bytes) [no enunciado: quadrado com + dentro] */
void operacao_soma64(block64 a, block64 b, block64 *saida) {
    *saida = a + b;
}
/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com + dentro] */
void operacao_xor(block64 a, block64 b, block64 *saida) {
    *saida = a ^ b;
}
/* B: inteiro, a, saida: 64 bits (8 bytes) [no enunciado: <<] */
void operacao_rotacao(block64 a, unsigned int b, block64 *s) {
    if(b >= 64) b = b % 64;
    *s = (a << b) | (a >> (64 - b));
}

/* a, b, saida: 64 bits (8 bytes) */
void operacao_rotacao_por_lbyte(block64 a, block64 b, block64 *s) {
    /* x << y == x << (y mod 64) */
    /* Os ultimos 6 bits de um número representam o resto da divisão por 64. */
    operacao_rotacao(a, b & 0x3F, s);
}

void operacao_oposto_soma64(block64 a, block64 *s) {
    *s = -a;
}


void K128_Iteracao_Parte1(block64 Xa, block64 Xb, block64 *XaL, block64 *XbL, block64 kA, block64 kB) {
    operacao_ponto(Xa, kA, XaL);
    operacao_soma64(Xb, kB, XbL);
}

void K128_Iteracao_Parte2(block64 Xe, block64 Xf, block64 *XeL, block64 *XfL, block64 kE, block64 kF) {
    block64 Y1, Y2, Z;
    block64 aux1, aux2;
    
    operacao_xor(Xe, Xf, &Y1);
    
    /* Calculando Y2 = [(kE (*) Y1) [+] Y1] (*) kF */
    operacao_ponto(kE, Y1, &aux1);  /* aux1 = (kE (*) Y1) */
    operacao_soma64(aux1, Y1, &aux2); /* aux2 = aux1 [+] Z1 = (kE (*) Y1) [+] Z1 */
    operacao_ponto(aux2, kF, &Y2);
    
    /* Calculando Z = (kE (*) Y1) [+] Y2 */
    operacao_ponto(kE, Y1, &aux1);
    operacao_soma64(aux1, Y2, &Z);
    
    /* Calculando XeL = Xe (+) Z; XfL = Xf [+] Z */
    operacao_xor(Xe, Z, XeL);
    operacao_xor(Xf, Z, XfL);
}

/* entrada, saida e chave: 128 bits (16 bytes) */
void K128_Iteracao(block128 entrada, block128 *saida, block64 chaves[]) {
    block128 Xbuffer;
    K128_Iteracao_Parte1(entrada.esquerda, entrada.direita, &(Xbuffer.esquerda), &(Xbuffer.direita), chaves[0], chaves[1]); /* k1 e k2 */
    K128_Iteracao_Parte2(Xbuffer.esquerda, Xbuffer.direita, &(saida->esquerda),  &(saida->direita) , chaves[2], chaves[2]); /* k3 e k4 */
}

void K128_Iteracao_Parte2_INV(block64 Xe, block64 Xf, block64 *XeL, block64 *XfL, block64 kE, block64 kF) {
    K128_Iteracao_Parte2(Xe, Xf, XeL, XfL, kE, kF);
}

void K128_Iteracao_Parte1_INV(block64 Xa, block64 Xb, block64 *XaL, block64 *XbL, block64 kA, block64 kB) {
    block64 kB_INV;
    /* X' = X (*) K -> X' = f(X) ^ f(K) -> X' ^ f(K) = f(X) -> 
       -> fINV(x' ^ f(K)) = fINV(f(X)) = X. */
    operacao_ponto_inverso(Xa, kA, XaL);

    /* X + K = X'; X + K + (-K) = X; X' + (-K) = X. */
    operacao_oposto_soma64(kB, &kB_INV);
    operacao_soma64(Xb, kB_INV, XbL);
}

void K128_Iteracao_INV(block128 entrada, block128 *saida, block64 chaves[]) {
    block128 Xbuffer;
    K128_Iteracao_Parte2    (entrada.esquerda, entrada.direita, &(Xbuffer.esquerda), &(Xbuffer.direita), chaves[2], chaves[3]); /* k1 e k2 */
    K128_Iteracao_Parte1_INV(Xbuffer.esquerda, Xbuffer.direita, &(saida->esquerda),  &(saida->direita) , chaves[0], chaves[1]); /* k3 e k4 */
}

void rawprint_bloco64(block64 block) {
    byte bytes[8];
    int i;
    convert_block64_to_bytes(block, bytes);
    for(i = 0; i < 8; i++)
        printf("%x", bytes[i]);
}

void GeraSubChaves(block128 K, block64 k_out[]) {
    block64 L[NUM_KEYS(R) + 1];
    block64 k[NUM_KEYS(R) + 1];

    {
        int j;
        static block64 magic_num1 = 0x9E3779B97F4A7C15; /* 0x9e3779b97f4a7c15 */
        static block64 magic_num2 = 0x8AED2A6BB7E15162; /* 0x8aed2a6bb7e15162 */
        static block64 magic_num3 = 0x7C159E3779B97F4A; /* 0x7c159e3779b97f4a */

        /* Passo 1. */
        L[0] = K.esquerda;
        L[1] = K.direita;
    
        /* Passo 2. */
        for(j = 2; j <= NUM_KEYS(R); ++j)
            operacao_soma64(L[j-1], magic_num1, &L[j]);
        
        /* Passo 3. */
        k[0] = magic_num2;
    
        /* Passo 4. */
        for(j = 1; j <= NUM_KEYS(R); ++j)
            operacao_soma64(k[j-1], magic_num3, &k[j]);
    }
    {
        /* Passo 5. */
        int i = 0, j = 0;
        block64 A = 0;
        block64 B = 0;
    
        /* Passo 6. */
        int s;
        for(s = 0; s < NUM_KEYS(R); ++s) {
            block64 aux1, aux2;
        
            operacao_soma64(k[i], A, &aux1);
            operacao_soma64(aux1, B, &aux2);
            operacao_rotacao(aux2, 3, &k[i]);
            A = k[i++];
        
            operacao_soma64(A, B, &aux1); /* aux1 = A [+] B */
            operacao_soma64(L[j], aux1, &aux2); /* aux2 = Li [+] A [+] B */
            operacao_rotacao_por_lbyte(aux2, aux1, &L[j]); /* Li = aux2 << aux1 = (Li [+] A [+] B) << (A [+] B) */
            B = L[j++];
        }

        for(i = 0; i < NUM_KEYS(R); ++i)
            k_out[i] = k[i + 1];
    }
}

void K128_Encrypt(block128 entrada, block128 *saida, block128 chave) {
    block128 buffer;
    block64 K_lista[NUM_KEYS(R)];
    int i;
    GeraSubChaves(chave, K_lista);
    
    memcpy(&buffer, &entrada, 16);
    for(i = 0; i < R; ++i) {
        K128_Iteracao(buffer, saida, K_lista + 4*i);
        memcpy(&buffer, saida, 16);
    }
    /* Ultima transformação T */
    K128_Iteracao_Parte1(buffer.esquerda, buffer.direita, &(saida->esquerda), &(saida->direita), K_lista[4*R], K_lista[4*R + 1]);
}

void K128_Decrypt(block128 entrada, block128 *saida, block128 chave) {
    block128 buffer;
    block64 K_lista[NUM_KEYS(R)];
    int i;
    GeraSubChaves(chave, K_lista);
    
    /* A ultima transformação T vem primeiro quando decriptografamos */
    K128_Iteracao_Parte1_INV(entrada.esquerda, entrada.direita, &(buffer.esquerda), &(buffer.direita), K_lista[4*R], K_lista[4*R + 1]);

    for(i = R - 1; i >= 0; --i) {
        K128_Iteracao_INV(buffer, saida, K_lista + 4*i);
        memcpy(&buffer, saida, 16);
    }
}

void gera_chave_da_senha(char* senha, block128 *k) { /* Chave de 128 bits */
    byte kB[16];
    size_t senha_size = strlen(senha);
    if(senha_size < 16) {
        /* senha_size é pelo menos 8 pela validação de senha acima. */
        memcpy(kB, senha, senha_size);
        memcpy(kB + senha_size, senha, 16 - senha_size);
    } else {
        memcpy(kB, senha, 16);
    }
    k->esquerda  = convert_bytes_to_block64(kB);
    k->direita = convert_bytes_to_block64(kB + 8);
}
