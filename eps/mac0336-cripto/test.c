#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "K128.h"

void print_lbyte_as_binary(lbyte l) {
    char buffer[33];
    int i;
    buffer[32] = '\0';
    for(i = 31; i >= 0; --i) {
        buffer[i] = ((l & 1) != 0) ? '1' : '0';
        l >>= 1;
    }
    printf("%s", buffer);
}

void print_lbyte_vector(char* before, lbyte a[], int size) {
    int i;
    printf(before);
    for(i = 0; i < size; ++i)
        print_lbyte_as_binary(a[i]);
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
    k->esquerda.bytes[0]  = convert_bytes_to_lbyte(kB);
    k->esquerda.bytes[1]  = convert_bytes_to_lbyte(kB + 4);
    k->direita.bytes[0] = convert_bytes_to_lbyte(kB + 8);
    k->direita.bytes[1] = convert_bytes_to_lbyte(kB + 12);
}

void init(void) {
    srand(time(NULL));
    inicializarVetoresFuncPonto();
}

void imprime_chaves(void) {
    block128 k;
    block64 lK[50];
    gera_chave_da_senha("Exemplo01", &k);
    GeraSubChaves(k, lK);
    {   int i;
        for(i = 0; i < 50; i++)
            printf("k[%d] = %x%x\n", i+1, lK[i].bytes[0], lK[i].bytes[1]); }
}

int main(void) {
    block64 A, B;

    A.bytes[0] = rand();
    A.bytes[1] = rand();
    B.bytes[0] = rand();
    B.bytes[1] = rand();
    
    init();

    print_lbyte_vector("", A.bytes, 2);
    printf("\n");
    while(fgetc(stdin) != 'q') {
        static block64 one = { 0x00000000, 0x00000001 };
        block64 C;
        operacao_soma64(B, one, &C);
        copy_block64(C, &B);

        operacao_rotacao_por_lbyte(A, B, &C);
        print_lbyte_vector("", C.bytes, 2);
    }
    /* imprime_chaves(); */

    return 0;
}
