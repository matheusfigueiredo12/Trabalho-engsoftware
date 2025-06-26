#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEDIDOS 100
#define TAM_NOME 50

typedef struct {
    char cliente[TAM_NOME];
    char produto[TAM_NOME];
    int quantidade;
    float precoUnitario;
} Pedido;

void cadastrarPedido(Pedido pedidos[], int *total) {
    if (*total >= MAX_PEDIDOS) {
        printf("Limite de pedidos atingido!\n");
        return;
    }

    printf("\n--- Cadastro de Pedido ---\n");

    getchar(); // limpar buffer
    printf("Nome do cliente: ");
    fgets(pedidos[*total].cliente, TAM_NOME, stdin);
    pedidos[*total].cliente[strcspn(pedidos[*total].cliente, "\n")] = '\0';

    printf("Nome do produto: ");
    fgets(pedidos[*total].produto, TAM_NOME, stdin);
    pedidos[*total].produto[strcspn(pedidos[*total].produto, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &pedidos[*total].quantidade);

    printf("Preço unitário: R$ ");
    scanf("%f", &pedidos[*total].precoUnitario);

    (*total)++;
    printf("Pedido cadastrado com sucesso!\n");
}

void listarPedidos(Pedido pedidos[], int total) {
    if (total == 0) {
        printf("\nNenhum pedido cadastrado ainda.\n");
        return;
    }

    printf("\n--- Lista de Pedidos ---\n");
    for (int i = 0; i < total; i++) {
        float totalPedido = pedidos[i].quantidade * pedidos[i].precoUnitario;
        printf("%d. Cliente: %s | Produto: %s | Qtd: %d | Unitário: R$%.2f | Total: R$%.2f\n",
               i + 1,
               pedidos[i].cliente,
               pedidos[i].produto,
               pedidos[i].quantidade,
               pedidos[i].precoUnitario,
               totalPedido);
    }
}

int main() {
    Pedido pedidos[MAX_PEDIDOS];
    int total = 0;
    int opcao;

    do {
        printf("\n=== MENU ===\n");
        printf("1. Cadastrar pedido\n");
        printf("2. Listar pedidos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPedido(pedidos, &total);
                break;
            case 2:
                listarPedidos(pedidos, total);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}

