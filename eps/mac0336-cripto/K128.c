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


lbyte primeirosNbits(lbyte l, unsigned int N) {
    lbyte mask = ((0x1uL << N) - 1) << (32 - N);
    return (l & mask) >> (32 - N);
}
lbyte ultimosNbits(lbyte l, unsigned int N) {
    lbyte mask = ((0x1uL << N) - 1);
    return (l & mask);
}

void convert_lbyte_to_bytes(lbyte l, byte b[4]) {
    b[0] = (byte)((l & 0xFF000000) >> 6);
    b[1] = (byte)((l & 0x00FF0000) >> 4);
    b[2] = (byte)((l & 0x0000FF00) >> 2);
    b[3] = (byte)((l & 0x000000FF));
}
void convert_2lbytes_to_bytes(lbyte l[2], byte b[8]) {
    convert_lbyte_to_bytes(l[0], b);
    convert_lbyte_to_bytes(l[1], b + 4);
}

lbyte convert_bytes_to_lbyte(byte b[4]) {
    lbyte result = 0;
    result |= (b[0] << 24);
    result |= (b[1] << 16);
    result |= (b[2] << 8);
    result |= b[3];
    return result;
}

/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com . dentro] */
void operacao_ponto(lbyte a[2], lbyte b[2], lbyte saida[2]) {
    byte aB[8], bB[8];
    int i;
    convert_2lbytes_to_bytes(a, aB);
    convert_2lbytes_to_bytes(b, bB);
    for(i = 0; i < 8; ++i) {
        aB[i] = ponto_exp[aB[i]];
        bB[i] = ponto_exp[bB[i]];
    }
    saida[0] = convert_bytes_to_lbyte(aB) ^ convert_bytes_to_lbyte(bB);
    saida[1] = convert_bytes_to_lbyte(aB + 4) ^ convert_bytes_to_lbyte(bB + 4);
}
void operacao_ponto_inverso(lbyte xL[2], lbyte k[2], lbyte x[2]) {
    /* X' = X (*) K -> X' = f(X) ^ f(K) -> X' ^ f(K) = f(X) -> 
       -> fINV(x' ^ f(K)) = fINV(f(X)) = X. */
    byte xLB[8], kB[8];
    int i;
    convert_2lbytes_to_bytes(xL, xLB);
    convert_2lbytes_to_bytes(k, kB);
    for(i = 0; i < 8; ++i)
        xLB[i] = ponto_log[xLB[i] ^ ponto_exp[kB[i]]];
    x[0] = convert_bytes_to_lbyte(xLB);
    x[1] = convert_bytes_to_lbyte(xLB + 4);
}

/* a, b, saida: 64 bits (8 bytes) [no enunciado: quadrado com + dentro] */
void operacao_soma64(lbyte a[2], lbyte b[2], lbyte saida[2]) {
    saida[1] = a[1] + b[1];
    saida[0] = a[0] + b[0] + ((saida[1] < a[1]) || (saida[1] < b[1]));
}
/* a, b, saida: 64 bits (8 bytes) [no enunciado: circulo com + dentro] */
void operacao_xor(lbyte a[2], lbyte b[2], lbyte saida[2]) {
    saida[0] = a[0] ^ b[0];
    saida[1] = a[1] ^ b[1];
}
/* B: inteiro, a, saida: 64 bits (8 bytes) [no enunciado: <<] */
void operacao_rotacao(lbyte a[2], unsigned int b, lbyte s[2]) {
    if(b >= 64) {
        operacao_rotacao(a, b % 64, s);
    } else if(b == 0) {
        s[0] = a[0];
        s[1] = a[1];
    } else if(b == 32) {
        s[0] = a[1];
        s[1] = a[0];
    } else if(b < 32) {
        s[0]  = a[0] << b;
        s[0] += primeirosNbits(a[1], b);
        s[1]  = a[1] << b;
        s[1] += primeirosNbits(a[0], b);
    } else /* if(b > 32) */ { 
        int bL = b - 32;
        s[0]  = a[1] << bL;
        s[0] += primeirosNbits(a[0], bL);
        s[1]  =   ultimosNbits(a[0], 64 - b) << bL;
        s[1] += primeirosNbits(a[1], bL);
    }
}

/* a, b, saida: 64 bits (8 bytes) */
void operacao_rotacao_por_lbyte(lbyte a[2], lbyte b[2], lbyte s[2]) {
    int num_bits = 0, i;
    lbyte val;
    for(i = 0; i < 2; i++)
        for(val = b[i]; val > 0; val >>= 1)
            if((val & 1) != 0) num_bits++;
    operacao_rotacao(a, num_bits, s);
}

void operacao_oposto_soma64(lbyte a[2], lbyte saida[2]) {
    saida[0] = ~a[0];
    saida[1] = ~a[1] + 1;
    if(saida[1] == 0) saida[0]++;
}


void K128_Iteracao_Parte1(lbyte Xa[2], lbyte Xb[2], lbyte XaL[2], lbyte XbL[2], lbyte kA[2], lbyte kB[2]) {
    operacao_ponto(Xa, kA, XaL);
    operacao_soma64(Xb, kB, XbL);
}

void K128_Iteracao_Parte2(lbyte Xe[2], lbyte Xf[2], lbyte XeL[2], lbyte XfL[2], lbyte kE[2], lbyte kF[2]) {
    lbyte Y1[2], Z1[2];
    lbyte Y2[2], Z2[2];
    lbyte aux1[2], aux2[2];
    
    operacao_xor(Xe, Xf, Y1);
    operacao_soma64(Xe, Xf, Z1);
    
    /* Calculando Y2 = [(kE (*) Y1) [+] Z1] (*) kF */
    operacao_ponto(kE, Y1, aux1);  /* aux1 = (kE (*) Y1) */
    operacao_soma64(aux1, Z1, aux2); /* aux2 = aux1 [+] Z1 = (kE (*) Y1) [+] Z1 */
    operacao_ponto(aux2, kF, Y2);
    
    /* Calculando Z2 = (kE (*) Y1) [+] Y2 */
    operacao_ponto(kE, Y1, aux1);
    operacao_soma64(aux1, Y2, Z2);
    
    /* Calculando XeL = Xe (+) Y2; XfL = Xf [+] Z2 */
    operacao_xor(Xe, Y2, XeL);
    operacao_soma64(Xf, Z2, XfL);
}

/* entrada, saida e chave: 128 bits (16 bytes) */
void K128_Iteracao(lbyte entrada[2], lbyte saida[2], lbyte chaves[][2]) {
    lbyte Xbuffer[4];       
    K128_Iteracao_Parte1(entrada, entrada + 2, Xbuffer, Xbuffer + 2, chaves[0], chaves[1]); /* k1 e k2 */
    K128_Iteracao_Parte2(Xbuffer, Xbuffer + 2,   saida,   saida + 2, chaves[2], chaves[2]); /* k3 e k4 */
}

void K128_Iteracao_Parte1_INV(lbyte Xa[2], lbyte Xb[2], lbyte XaL[2], lbyte XbL[2], lbyte kA[2], lbyte kB[2]) {
    lbyte kB_INV[2];
    /* X' = X (*) K -> X' = f(X) ^ f(K) -> X' ^ f(K) = f(X) -> 
       -> fINV(x' ^ f(K)) = fINV(f(X)) = X. */
    operacao_ponto_inverso(Xa, kA, XaL);

    /* X + K = X'; X + K + (-K) = X; X' + (-K) = X. */
    operacao_oposto_soma64(kB, kB_INV);
    operacao_soma64(Xb, kB_INV, XbL);
}

void GeraSubChaves(lbyte K[4], lbyte k[][2]) {
    lbyte L[NUM_KEYS(R)][2];

    {
        int j;
        static lbyte magic_num1[] = { 0x9E3779B9, 0x7F4A7C15 }; /* 0x9e3779b97f4a7c15 */
        static lbyte magic_num2[] = { 0x8AED2A6B, 0xB7E15162 }; /* 0x8aed2a6bb7e15162 */
        static lbyte magic_num3[] = { 0x7C159E37, 0x79B97F4A }; /* 0x7c159e3779b97f4a */
    
        /* Passo 1. */
        memcpy(L[0], &K[0], 8);
        memcpy(L[1], &K[2], 8);
    
        /* Passo 2. */
        for(j = 2; j < NUM_KEYS(R); ++j)
            operacao_soma64(L[j-1], magic_num1, L[j]);
        
        /* Passo 3. */
        memcpy(k[0], magic_num2, 8);
    
        /* Passo 4. */
        for(j = 1; j < NUM_KEYS(R); ++j)
            operacao_soma64(k[j-1], magic_num3, k[j]);

    }
    {
        lbyte A[2], B[2];
        int s, i = 0, j = 0;

        /* Passo 5. */
        
        memset(A, 0, 8);
        memset(B, 0, 8);
    
        /* Passo 6. */
        for(s = 1; s < NUM_KEYS(R); ++s) {
            lbyte aux1[2], aux2[2];
        
            operacao_soma64(k[i], A, aux1);
            operacao_soma64(aux1, B, aux2);
            operacao_rotacao(aux2, 3, k[i]);
            memcpy(A, k[i], 8);
            i++;
        
            operacao_soma64(A, B, aux1); /* aux1 = A [+] B */
            operacao_soma64(L[i], aux1, aux2); /* aux2 = Li [+] A [+] B */
            operacao_rotacao_por_lbyte(aux2, aux1, L[i]); /* Li = aux2 << aux1 = (Li [+] A [+] B) << (A [+] B) */
            memcpy(B, L[i], 8);
            j++;
        }
    }
}

void K128_Encrypt(lbyte entrada[4], lbyte saida[4], lbyte chave[4]) {
    lbyte buffer[4];
    lbyte K_lista[NUM_KEYS(R)][2];
    int i;
    GeraSubChaves(chave, K_lista);
    
    memcpy(buffer, entrada, 16);
    for(i = 0; i < R; ++i) {
        K128_Iteracao(buffer, saida, K_lista + 4*i);
        memcpy(buffer, saida, 16);
    }
    /* Ultima transformação T */
    K128_Iteracao_Parte1(buffer, buffer + 2, saida, saida + 2, K_lista[4*R], K_lista[4*R + 1]);
}

void K128_Decrypt(lbyte entrada[4], lbyte saida[4], lbyte chave[4]) {
    lbyte buffer[4];
    lbyte K_lista[NUM_KEYS(R)][2];
    int i;
    GeraSubChaves(chave, K_lista);
    
    /* A ultima transformação T vem primeiro quando decriptografamos */
    K128_Iteracao_Parte1_INV(entrada, entrada + 2, buffer, buffer + 2, K_lista[4*R], K_lista[4*R + 1]);

    for(i = 0; i < R; ++i) {
        K128_Iteracao(buffer, saida, K_lista + 4*i);
        memcpy(buffer, saida, 16);
    }
}
