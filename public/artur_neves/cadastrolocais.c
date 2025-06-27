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

    getchar();
    printf("\n--- Cadastro de Local ---\n");
    printf("Nome do local: ");
    fgets(locais[*total].nome, TAM_NOME_LOCAL, stdin);
    locais[*total].nome[strcspn(locais[*total].nome, "\n")] = '\0';

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

void excluirLocal(Local locais[], int *total) {
    char nomeBusca[TAM_NOME_LOCAL];
    getchar();
    printf("Digite o nome do local a excluir: ");
    fgets(nomeBusca, TAM_NOME_LOCAL, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(locais[i].nome, nomeBusca) == 0) {
            for (int j = i; j < *total - 1; j++) {
                locais[j] = locais[j + 1];
            }
            (*total)--;
            printf("Local removido com sucesso!\n");
            return;
        }
    }

    printf("Local não encontrado.\n");
}

void menuLocais() {
    Local locais[MAX_LOCAIS];
    int totalLocais = 0;
    int opcao;

    do {
        printf("\n=== MENU LOCAIS ===\n");
        printf("1. Cadastrar local\n");
        printf("2. Listar locais\n");
        printf("3. Excluir local\n");
        printf("0. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarLocal(locais, &totalLocais);
                break;
            case 2:
                listarLocais(locais, totalLocais);
                break;
            case 3:
                excluirLocal(locais, &totalLocais);
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
}

int main() {
    menuLocais();
    return 0;
}
