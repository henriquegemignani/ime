﻿#include <stdio.h>
#include <string.h>
#include "types.h"

/* Nota: nenhuma tentativa de deixar o código mais legível foi feita.
 Desde que programo bastante em C++, não considero mais possível ter um 
 código "bonito" em C, principalmente ANSI C. */

#define STR_BUFFER 1024

#define MODO_1 1
#define MODO_2 2
#define MODO_C 3
#define MODO_D 4
int trata_modo(char* input) {
    if(*(input++) != '-') return -1;
    switch(*input) {
        case '1': return MODO_1;
        case '2': return MODO_2;
        case 'c': return MODO_C;
        case 'd': return MODO_D;
        default: return -1;
    }
}
bool valida_senha(char* senha) {
    int num_digito = 0, num_letra = 0, i;
    for(i = 0; senha[i] != '\0'; ++i) {
        if(('a' <= senha[i] && senha[i] <= 'z') || ('A' <= senha[i] && senha[i] <= 'Z'))
            ++num_letra;
        else if('0' <= senha[i] && senha[i] <= '9')
            ++num_digito;
    }
    return (i >= 8) && (num_digito >= 2) && (num_letra >= 2);
}

int main(int argc, char** argv) {
    int modo;
    char arquivo_de_entrada[STR_BUFFER];
    char arquivo_de_saida[STR_BUFFER];
    char senha[STR_BUFFER];
    bool apagar = false;
    if(argc < 4) {
        printf("Uso: %s -<modo> -i <arquivo de entrada> [-o <arquivo de saida>] -p <senha> [-a]\n", argv[0]);
        return 1;
    }
    modo = trata_modo(argv[1]);
    if(modo == -1) {
        printf("Parametro inválido: '%s'. Esperado: modo (-1, -2, -c, -d)\n", argv[1]);
        return 2;
    }
    if(strcmp(argv[2], "-i") != 0) {
        printf("Parametro inválido: '%s. Esperado: -i'\n", argv[2]);
        return 3;
    }
    strncpy(arquivo_de_entrada, argv[3], STR_BUFFER - 1);
    arquivo_de_entrada[STR_BUFFER - 1] = '\0';
    
    if(modo == MODO_C || modo == MODO_D) {
        if(strcmp(argv[4], "-o") != 0) {
            printf("Parametro inválido: '%s'. Esperado: -o\n", argv[4]);
            return 4;
        }
        strncpy(arquivo_de_saida, argv[5], STR_BUFFER - 1);
        arquivo_de_saida[STR_BUFFER - 1] = '\0';
        argv++;
        argv++;
        argc -= 2;
    }
    
    if(strcmp(argv[4], "-p") != 0) {
        printf("Parametro inválido: '%s'. Esperado: -p\n", argv[4]);
        return 4;
    }
    strncpy(senha, argv[5], STR_BUFFER - 1);
    senha[STR_BUFFER - 1] = '\0';
    if(!valida_senha(senha)) {
        printf("Senha inválida: '%s'. Necessário pelo menos 8 caraceteres, pelo menos 2 digitos e 2 letras.\n", senha);
        return 5;
    }
    
    apagar = (argc == 7);
    
    printf("Modo: %d\n", modo);
    printf("Entrada: %s\n", arquivo_de_entrada);
    printf("Saida: %s\n", arquivo_de_saida);
    printf("Senha: %s\n", senha);
    printf("Apagar: %d\n", apagar);
    return 0;
}