#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEDIDOS 100
#define MAX_LOCAIS 100
#define MAX_VEICULOS 100
#define TAM_NOME 50
#define TAM_NOME_LOCAL 100

// ======= Estruturas =======

typedef struct {
    char nome[TAM_NOME_LOCAL];
} Local;

typedef struct {
    char cliente[TAM_NOME];
    char produto[TAM_NOME];
    int quantidade;
    float precoUnitario;
    char localEntrega[TAM_NOME_LOCAL];
} Pedido;

typedef struct {
    char placa[10];
    char modelo[50];
    char status[15];
    Local localAtual;
} Veiculo;

// ======= Funções de Pedidos =======

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

    getchar();
    printf("Local de entrega: ");
    fgets(pedidos[*total].localEntrega, TAM_NOME_LOCAL, stdin);
    pedidos[*total].localEntrega[strcspn(pedidos[*total].localEntrega, "\n")] = '\0';

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
        printf("%d. Cliente: %s | Produto: %s | Qtd: %d | Unitário: R$%.2f | Total: R$%.2f | Entrega: %s\n",
               i + 1,
               pedidos[i].cliente,
               pedidos[i].produto,
               pedidos[i].quantidade,
               pedidos[i].precoUnitario,
               totalPedido,
               pedidos[i].localEntrega);
    }
}

// ======= Funções de Locais =======

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

// ======= Funções de Veículos =======

void criarVeiculo(Veiculo veiculos[], int *total) {
    if (*total >= MAX_VEICULOS) {
        printf("Limite de veículos atingido.\n");
        return;
    }

    Veiculo novo;

    printf("Placa: ");
    scanf("%s", novo.placa);

    for (int i = 0; i < *total; i++) {
        if (strcmp(veiculos[i].placa, novo.placa) == 0) {
            printf("Erro: Veículo com essa placa já existe.\n");
            return;
        }
    }

    printf("Modelo: ");
    scanf(" %[^\n]", novo.modelo);

    printf("Status (disponivel/ocupado): ");
    scanf("%s", novo.status);

    printf("Local atual: ");
    scanf(" %[^\n]", novo.localAtual.nome);

    veiculos[(*total)++] = novo;
    printf("Veículo cadastrado com sucesso!\n");
}

void listarVeiculos(Veiculo veiculos[], int total) {
    if (total == 0) {
        printf("Nenhum veículo cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\n--- Veículo %d ---\n", i + 1);
        printf("Placa: %s\n", veiculos[i].placa);
        printf("Modelo: %s\n", veiculos[i].modelo);
        printf("Status: %s\n", veiculos[i].status);
        printf("Local atual: %s\n", veiculos[i].localAtual.nome);
    }
}

// ======= Rota de Entrega (Simples) =======

void exibirRotasDeEntrega(Pedido pedidos[], int totalPedidos) {
    if (totalPedidos == 0) {
        printf("Nenhum pedido para calcular rotas.\n");
        return;
    }

    printf("\n--- Rota de Entrega (Simples) ---\n");
    for (int i = 0; i < totalPedidos; i++) {
        printf("%d. Entregar para %s no local: %s\n", i + 1, pedidos[i].cliente, pedidos[i].localEntrega);
    }
}

// ======= Menu Principal =======

int main() {
    Pedido pedidos[MAX_PEDIDOS];
    Local locais[MAX_LOCAIS];
    Veiculo veiculos[MAX_VEICULOS];

    int totalPedidos = 0, totalLocais = 0, totalVeiculos = 0;
    int opcao;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar pedido\n");
        printf("2. Cadastrar local\n");
        printf("3. Cadastrar veículo\n");
        printf("4. Listar pedidos\n");
        printf("5. Listar locais\n");
        printf("6. Listar veículos\n");
        printf("7. Exibir rota de entrega\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarPedido(pedidos, &totalPedidos);
                break;
            case 2:
                cadastrarLocal(locais, &totalLocais);
                break;
            case 3:
                criarVeiculo(veiculos, &totalVeiculos);
                break;
            case 4:
                listarPedidos(pedidos, totalPedidos);
                break;
            case 5:
                listarLocais(locais, totalLocais);
                break;
            case 6:
                listarVeiculos(veiculos, totalVeiculos);
                break;
            case 7:
                exibirRotasDeEntrega(pedidos, totalPedidos);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
