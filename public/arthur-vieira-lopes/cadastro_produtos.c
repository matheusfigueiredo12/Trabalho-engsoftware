#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define TAM_NOME 50

typedef struct {
    char nome[TAM_NOME];
    float preco;
    int quantidade;
} Produto;

void cadastrarProduto(Produto produtos[], int *total) {
    if (*total >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    printf("\n--- Cadastro de Produto ---\n");

    printf("Nome: ");
    getchar(); // limpa o buffer
    fgets(produtos[*total].nome, TAM_NOME, stdin);
    produtos[*total].nome[strcspn(produtos[*total].nome, "\n")] = '\0'; // remove o \n

    printf("Preço: R$ ");
    scanf("%f", &produtos[*total].preco);

    printf("Quantidade: ");
    scanf("%d", &produtos[*total].quantidade);

    (*total)++;
    printf("Produto cadastrado com sucesso!\n");
}

void listarProdutos(Produto produtos[], int total) {
    if (total == 0) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    printf("\n--- Lista de Produtos ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s - R$ %.2f - %d unidades\n", i + 1, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int total = 0;
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar produto\n");
        printf("2. Listar produtos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &total);
                break;
            case 2:
                listarProdutos(produtos, total);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
