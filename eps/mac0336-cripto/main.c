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
#define MODO_K 5
int trata_modo(char* input) {
    if(*(input++) != '-') return -1;
    switch(*input) {
        case '1': return MODO_1;
        case '2': return MODO_2;
        case 'c': return MODO_C;
        case 'd': 
            if(strcmp(input, "debug") == 0)
                return MODO_K;
            return MODO_D;
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

unsigned long encriptografa_raw(FILE* entrada, FILE* saida, block128 k) { /* Chave de 128 bits */
    unsigned long source_size = 0;
    size_t actual_read = 0;
    block128 bloco_anterior = { 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF };
    do {
        block128 ent, sai;
        source_size += actual_read = fread(&ent, 1, 16, entrada);

        /* CBC: XOR com o bloco criptografado anterior. */
        ent.esquerda ^= bloco_anterior.esquerda;
        ent.direita  ^= bloco_anterior.direita;

        K128_Encrypt(ent, &sai, k);

        if(actual_read < 16) /* Last block. */
            memset(((byte*)&sai) + actual_read, 0xFF, 16 - actual_read);
        fwrite(&sai, 1, 16, saida);

        /* Guarda saída para o CBC do próximo bloco. */
        copy_block128(sai, &bloco_anterior);


    } while(actual_read == 16);
    return source_size;
}

void decriptografa_raw(FILE* entrada, FILE* saida, block128 k) { /* Chave de 128 bits */
    unsigned long source_size = 0;
    size_t actual_read = 0;
    block128 bloco_anterior = { 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF };

    fread(&source_size, 4, 1, entrada);
    while(source_size > 0) {
        block128 ent, sai;
        actual_read = fread(&ent, 1, 16, entrada);
        if(actual_read < 16) printf("Erro: bloco incompleto!\n");

        K128_Decrypt(ent, &sai, k);

        /* CBC: XOR com o bloco criptografado anterior. */
        sai.esquerda ^= bloco_anterior.esquerda;
        sai.direita  ^= bloco_anterior.direita;

        if(source_size < 16) {
            fwrite(&sai, 1, source_size, saida);
            source_size = 0;
        } else {
            fwrite(&sai, 1, 16, saida);

            /* Guarda crifra para o CBC do próximo bloco. */
            copy_block128(ent, &bloco_anterior);
            source_size -= 16;
        }
    }
}

void encriptografa(char* nome_entrada, char* nome_saida, char* senha) {
    unsigned long source_size = 0;
    FILE* entrada = fopen(nome_entrada, "rb");
    FILE* saida = fopen(nome_saida, "wb");
    block128 k; /* Chave de 128 bits */
    gera_chave_da_senha(senha, &k);

    fwrite(&source_size, 4, 1, saida);

    printf("Encrypting '%s' to '%s'...\n", nome_entrada, nome_saida);
    source_size = encriptografa_raw(entrada, saida, k);

    fseek(saida, 0, SEEK_SET);
    fwrite(&source_size, 4, 1, saida);

    fclose(entrada);
    fclose(saida);
}

void decriptografa(char* nome_entrada, char* nome_saida, char* senha) {
    FILE* entrada = fopen(nome_entrada, "rb");
    FILE* saida = fopen(nome_saida, "wb");
    block128 k; /* Chave de 128 bits */
    gera_chave_da_senha(senha, &k);

    printf("Decrypting '%s' to '%s'...\n", nome_entrada, nome_saida);
    decriptografa_raw(entrada, saida, k);

    fclose(entrada);
    fclose(saida);
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
        printf("Parametro inválido: '%s'. Esperado: modo (-1, -2, -c, -d, -debug)\n", argv[1]);
        return 2;
    }
    if(modo != MODO_K) {
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
    } else {
        /* -debug atrapalha tudo... Isso é feio mas funciona. */
        argv -= 2;
        argc += 2;
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
        
        argv += 2;
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
    
    /* Necessidade. */
    inicializarVetoresFuncPonto();
    
    switch(modo) {
        case MODO_1: break;
        case MODO_2: break;
        case MODO_C:
            encriptografa(arquivo_de_entrada, arquivo_de_saida, senha);
            if(apagar) {
                FILE* f = fopen(arquivo_de_entrada, "w");
                if(f) fclose(f);
            }
            break;
        case MODO_D:
            decriptografa(arquivo_de_entrada, arquivo_de_saida, senha);
            break;
        case MODO_K:
            {
                int i;
                block128 k;
                block64 lK[50];
                gera_chave_da_senha(senha, &k);
                GeraSubChaves(k, lK);
                for(i = 0; i < 50; i++)
                    printf("k[%d] = %016llx\n", i+1, lK[i]);
            }
        default: break;
    }
    return 0;
}