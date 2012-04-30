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
    printf("\n");
}

void gera_chave_da_senha(char* senha, lbyte k[4]) { /* Chave de 128 bits */
    byte kB[16];
    size_t senha_size = strlen(senha);
    if(senha_size < 16) {
        /* senha_size é pelo menos 8 pela validação de senha acima. */
        memcpy(kB, senha, senha_size);
        memcpy(kB + senha_size, senha, 16 - senha_size);
    } else {
        memcpy(kB, senha, 16);
    }
    k[0] = convert_bytes_to_lbyte(kB);
    k[1] = convert_bytes_to_lbyte(kB + 4);
    k[2] = convert_bytes_to_lbyte(kB + 8);
    k[3] = convert_bytes_to_lbyte(kB + 12);
}

int main(void) {
    int i;
    lbyte k[4];
    lbyte lK[50][2];
    inicializarVetoresFuncPonto();

    gera_chave_da_senha("Exemplo01", k);
    GeraSubChaves(k, lK);
    for(i = 0; i < 50; i++)
        printf("k[%d] = %x%x\n", i+1, lK[i][0], lK[i][1]);

    return 0;
}
