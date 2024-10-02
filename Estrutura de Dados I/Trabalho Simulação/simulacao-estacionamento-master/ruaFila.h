#include <stdio.h>
#include <stdlib.h>

typedef struct TipoCelula *TipoApontador;

typedef struct {
    char placa[10];
    int deslocamento;
    int prioridade;
} TipoCarro;

typedef struct TipoCelula {
    TipoCarro carro;
    TipoApontador prox;
} TipoCelula;

typedef struct TipoFila {
    TipoApontador frente, tras;
} TipoFila;

void FFVazia(TipoFila *Fila) {
    Fila->frente = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
}

int Vazia(TipoFila Fila) {
    return (Fila.frente == Fila.tras);
}

void Enfileira(TipoCarro x, TipoFila *Fila) {
    Fila->tras->prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->carro = x;
    Fila->tras->prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoCarro *carro) {
    TipoApontador q;
    if (Vazia(*Fila)) {
        printf("Erro fila esta vazia\n");
        return;
    }
    q = Fila->frente;
    Fila->frente = Fila->frente->prox;
    *carro = Fila->frente->carro;
    free(q);
}

void exibe(TipoFila fila) {
    TipoApontador aux = fila.frente->prox;
    while (aux != NULL) {
        printf("\nDeslocamento: %d\n", aux->carro.deslocamento);
        printf("Placa: %s\n", aux->carro.placa);
        printf("Prioridade: %d\n", aux->carro.prioridade);
        aux = aux->prox;
    }
}
