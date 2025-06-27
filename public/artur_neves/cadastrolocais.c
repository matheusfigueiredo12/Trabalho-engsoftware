#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOCAIS 100
#define TAM_NOME_LOCAL 100

typedef struct {
    char nome[TAM_NOME_LOCAL];
} Local;
void cadastrarLocal(Local locais[], int *total) {
    if (*total >= MAX_LOCAIS) {
        printf("Limite de locais atingido!\n");
        return;
    }

   
    for (int i = 0; i < *total; i++) {
        if (strcmp(locais[i].nome, locais[*total].nome) == 0) {
            printf("Local já cadastrado!\n");
            return;
        }
    }

    (*total)++;
    printf("Local cadastrado com sucesso!\n");
}

void listarLocais(Local locais[], int total) {
    if (total == 0) {
        printf("\nNenhum local cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Locais ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s\n", i + 1, locais[i].nome);
    }
}