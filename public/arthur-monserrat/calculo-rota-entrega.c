#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAX_VEICULOS 100
#define MAX_LOCAIS 100
#define MAX_PEDIDOS 100

typedef struct {
    char nome[100];
    float x;
    float y;
} Local;

typedef struct {
    char placa[10];
    char modelo[30];
    char status[15]; 
    char localAtual[100]; 
} Veiculo;

typedef struct {
    int id;
    char origem[100];
    char destino[100];
    float peso;
} Pedido;


float calcularDistancia(Local a, Local b) {
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}


int buscarIndiceLocal(Local locais[], int totalLocais, const char nome[]) {
    for (int i = 0; i < totalLocais; i++) {
        if (strcmp(locais[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}


void calcularERotearEntrega(Pedido pedidos[], int totalPedidos,
                            Veiculo veiculos[], int totalVeiculos,
                            Local locais[], int totalLocais) {
    int idPedido;
    printf("\nDigite o ID do pedido a ser entregue: ");
    scanf("%d", &idPedido);

    int indicePedido = -1;
    for (int i = 0; i < totalPedidos; i++) {
        if (pedidos[i].id == idPedido) {
            indicePedido = i;
            break;
        }
    }

    if (indicePedido == -1) {
        printf("Pedido nao encontrado.\n");
        return;
    }

    Pedido pedido = pedidos[indicePedido];

    int idxOrigem = buscarIndiceLocal(locais, totalLocais, pedido.origem);
    int idxDestino = buscarIndiceLocal(locais, totalLocais, pedido.destino);

    if (idxOrigem == -1 || idxDestino == -1) {
        printf("Erro: Local de origem ou destino nao encontrado.\n");
        return;
    }

    Local origem = locais[idxOrigem];
    Local destino = locais[idxDestino];

    
    int veiculoMaisProximo = -1;
    float menorDistancia = -1;

    for (int i = 0; i < totalVeiculos; i++) {
        if (strcmp(veiculos[i].status, "disponivel") == 0) {
            int idxLocalAtual = buscarIndiceLocal(locais, totalLocais, veiculos[i].localAtual);
            if (idxLocalAtual == -1) continue;

            float dist = calcularDistancia(locais[idxLocalAtual], origem);
            if (menorDistancia == -1 || dist < menorDistancia) {
                menorDistancia = dist;
                veiculoMaisProximo = i;
            }
        }
    }

    if (veiculoMaisProximo == -1) {
        printf("Nao ha veiculos disponiveis para realizar a entrega.\n");
        return;
    }

    
    float distOrigemDestino = calcularDistancia(origem, destino);
    float distanciaTotal = menorDistancia + distOrigemDestino;

    printf("\n=== ROTA DE ENTREGA ===\n");
    printf("Veiculo: %s\n", veiculos[veiculoMaisProximo].placa);
    printf("Origem: %s\n", pedido.origem);
    printf("Destino: %s\n", pedido.destino);
    printf("Distancia total percorrida: %.2f\n", distanciaTotal);

    
    strcpy(veiculos[veiculoMaisProximo].status, "ocupado");
    printf("Entrega em andamento...\n");

    
    strcpy(veiculos[veiculoMaisProximo].status, "disponivel");
    strcpy(veiculos[veiculoMaisProximo].localAtual, pedido.destino);

    printf("Entrega concluida. Veiculo atualizado para local de destino e status disponivel.\n");
}
