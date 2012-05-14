#include <stdio.h>
#include <string.h>
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

void init(void) {
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
        printf("k[%d] = 0x%016llx\n", i+1, lK[i]);
}

int main(void) {   
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
