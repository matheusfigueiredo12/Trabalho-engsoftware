#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VEICULOS 100
#define MAX_LOCAL 100

// ============================
// DEFINIÇÃO DOS TIPOS ABSTRATOS
// ============================

typedef struct {
    char nome[MAX_LOCAL];
} Local;

typedef struct {
    char placa[10];         // Identificador único
    char modelo[50];
    char status[15];        // "disponivel" ou "ocupado"
    Local localAtual;       // Nome do local atual
} Veiculo;

// ============================
// FUNÇÕES DO SISTEMA
// ============================

// Função para cadastrar novo veículo
void criarVeiculo(Veiculo veiculos[], int *total) {
    if (*total >= MAX_VEICULOS) {
        printf("Limite de veículos atingido.\n");
        return;
    }

    Veiculo novo;

    printf("Placa: ");
    scanf("%s", novo.placa);

    // Verifica se a placa já existe
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

// Função para listar todos os veículos cadastrados
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

// Função para atualizar status e local de um veículo
void atualizarVeiculo(Veiculo veiculos[], int total) {
    char placaBusca[10];
    printf("Digite a placa do veículo a atualizar: ");
    scanf("%s", placaBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(veiculos[i].placa, placaBusca) == 0) {
            printf("Novo status (disponivel/ocupado): ");
            scanf("%s", veiculos[i].status);

            printf("Novo local atual: ");
            scanf(" %[^\n]", veiculos[i].localAtual.nome);

            printf("Veículo atualizado com sucesso!\n");
            return;
        }
    }

    printf("Veículo com placa %s não encontrado.\n", placaBusca);
}

// Função para remover um veículo do vetor
void excluirVeiculo(Veiculo veiculos[], int *total) {
    char placaBusca[10];
    printf("Digite a placa do veículo a excluir: ");
    scanf("%s", placaBusca);

    for (int i = 0; i < *total; i++) {
        if (strcmp(veiculos[i].placa, placaBusca) == 0) {
            // Move os veículos seguintes para "fechar o buraco"
            for (int j = i; j < *total - 1; j++) {
                veiculos[j] = veiculos[j + 1];
            }
            (*total)--;
            printf("Veículo removido com sucesso!\n");
            return;
        }
    }

    printf("Veículo com placa %s não encontrado.\n", placaBusca);
}

// ============================
// MENU PRINCIPAL
// ============================

void exibirMenu() {
    printf("\n==== MENU VEÍCULOS ====\n");
    printf("1. Cadastrar veículo\n");
    printf("2. Listar veículos\n");
    printf("3. Atualizar veículo\n");
    printf("4. Excluir veículo\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    Veiculo veiculos[MAX_VEICULOS]; // Vetor de veículos
    int totalVeiculos = 0;
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarVeiculo(veiculos, &totalVeiculos);
                break;
            case 2:
                listarVeiculos(veiculos, totalVeiculos);
                break;
            case 3:
                atualizarVeiculo(veiculos, totalVeiculos);
                break;
            case 4:
                excluirVeiculo(veiculos, &totalVeiculos);
                break;
            case 0:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
