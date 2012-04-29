#include <stdio.h>
#include <string.h>
#include "types.h"
#include "K128.h"

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

void criptografa(char* nome_entrada, char* nome_saida, char* senha) {
    FILE* entrada = fopen(nome_entrada, "r");
    FILE* saida = fopen(nome_saida, "w");
    byte kB[16];
    lbyte k[2];
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
    while(!feof(entrada)) {
        lbyte ent[2], sai[2];
        fread(ent, 16, 1, entrada);
        K128_R12(ent, sai, k); /* usar CBC */
        fwrite(sai, 16, 1, saida);
    }
    fclose(entrada);
    fclose(saida);
}

int main(int argc, char** argv) {
    int modo;
    char arquivo_de_entrada[STR_BUFFER];
    char arquivo_de_saida[STR_BUFFER];
    char senha[STR_BUFFER];
    bool apagar = false;
    if(argc < 6) {
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
    {
        FILE* f = fopen(arquivo_de_entrada, "r");
        if(f == NULL) {
            printf("Impossível abrir arquivo '%s' para leitura.\n", arquivo_de_entrada);
            return 5;
        }
        fclose(f);
    }
    
    if(modo == MODO_C || modo == MODO_D) {
        if(strcmp(argv[4], "-o") != 0) {
            printf("Parametro inválido: '%s'. Esperado: -o\n", argv[4]);
            return 4;
        }
        strncpy(arquivo_de_saida, argv[5], STR_BUFFER - 1);
        arquivo_de_saida[STR_BUFFER - 1] = '\0';
        
        {
            FILE* f = fopen(arquivo_de_saida, "a");
            if(f == NULL) {
                printf("Impossível abrir arquivo '%s' para escrita.\n", arquivo_de_saida);
                return 5;
            }
            fclose(f);
        }
        
        argv++;
        argv++;
        argc -= 2;
        
        if(argc < 6) {
            printf("Uso: %s -<modo> -i <arquivo de entrada> [-o <arquivo de saida>] -p <senha> [-a]\n", argv[0]);
            return 1;
        }
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
    
    /* Necessidade. */
    inicializarVetoresFuncPonto();
    
    switch(modo) {
        case MODO_1: break;
        case MODO_2: break;
        case MODO_C: break;
            criptografa(arquivo_de_entrada, arquivo_de_saida, senha);
            if(apagar) {
                FILE* f = fopen(arquivo_de_entrada, "w");
                if(f) fclose(f);
            }
        case MODO_D: break;
        default: break;
    }
    
    return 0;
}