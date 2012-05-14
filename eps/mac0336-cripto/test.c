#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "K128.h"

void print_block64_as_binary(char* before, block64 l) {
    char buffer[65];
    int i;
    buffer[64] = '\0';
    for(i = 63; i >= 0; --i) {
        buffer[i] = ((l & 1) != 0) ? '1' : '0';
        l >>= 1;
    }
    printf(before);
    printf("%s", buffer);
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

void init(void) {
    srand(time(NULL));
    inicializarVetoresFuncPonto();
}

void imprime_chaves(void) {
    int i;
    block128 k;
    block64 lK[50];
    gera_chave_da_senha("Exemplo01", &k);
    GeraSubChaves(k, lK);
    puts("Exemplo01");
    for(i = 0; i < 50; i++)
        printf("k[%d] = %016llx\n", i+1, lK[i]);
}

int main(void) {
    block64 A, B;

    A = rand();
    B = rand();
    
    init();

    /*print_block64_as_binary("", A);
    printf("\n");
    while(fgetc(stdin) != 'q') {
        block64 C;
        operacao_soma64(B, 1, &C);
        B = C;

        operacao_rotacao_por_lbyte(A, B, &C);
        print_block64_as_binary("", C);
    }*/
    imprime_chaves();

    return 0;
}
