#include <stdio.h>
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
    /*printf("\n");*/
}

int main() {
    lbyte a[] = { 0x43214321, 0x12341234 }, s[2];
    unsigned b = 0;
    while(b <= 64) {
        fgetc(stdin);
        operacao_rotacao(a, b, s);
        print_lbyte_vector("", s, 2);
        printf("  - %d ", b++);
    }
    return 0;
}