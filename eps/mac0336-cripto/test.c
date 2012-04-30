#include <stdio.h>
#include <stdlib.h>
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

int main() {
    int i;

    srand(time(NULL));

    for(i = 0; i < 1000; i++) {
        lbyte oposto[2], soma[2], a[2];
        a[0] = rand();
        a[1] = rand();
        operacao_oposto_soma64(a, oposto);
        operacao_soma64(a, oposto, soma);
        print_lbyte_vector("sum: ", soma, 2);
    }

    inicializarVetoresFuncPonto();
    return 0;
}
