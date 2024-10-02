#include "ruaFila.h"
#include <string.h>
#define MAX_CARROS 5 // Numero maximo de carros no estacionamento

/* Funcoes para gerenciamento do estacionamento */

// Funcao que verifica se o estacionamento possui mais de 5 carros (MAX_CARROS)
int estacionamentoEstaCheio(TipoFila *estacionamento) {
    TipoApontador apontadorCarro = estacionamento->frente->prox;
    int numeroDeCarros = 0;

    while (apontadorCarro != NULL) {
        numeroDeCarros++;
        apontadorCarro = apontadorCarro->prox;
    }
    return numeroDeCarros == MAX_CARROS;
}

void estacionarCarro(TipoCarro carro, TipoFila *estacionamento, TipoFila *ruaMonsenhor){
    /**
     *  Verifica se a fila BomJesusDosPassos (estacionamento) esta cheia
     *      Se estiver cheia enfileira na fila MonsenhorJoaoPedro
     *      Caso nao estiver cheia imprimir/retornar que o carro foi estacionado
     */

    if(estacionamentoEstaCheio(estacionamento)){
        Enfileira(carro, ruaMonsenhor);
        printf("Carro de placa %s esta aguardando na rua Monsenhor Joao Pedro.\n", carro.placa);
        return;
    }

    Enfileira(carro, estacionamento);
    printf("Carro de placa %s foi estacionado.\n", carro.placa);
}

/* Funcoes para retirada de carros */

// Função para retirar o carro específico
int verificarCarro(TipoFila *estacionamento, TipoCarro carro, TipoFila *filaAuxiliar){
    TipoCarro carroAtual;
    int carroEncontrado = 0;

    while(!Vazia(*estacionamento)){
        Desenfileira(estacionamento, &carroAtual);
        if (strcmp(carroAtual.placa, carro.placa) == 0) {
            carroEncontrado = 1;
            printf("\nCarro de placa: %s removido. Deslocamentos: %d\n", carroAtual.placa, carroAtual.deslocamento+1); // deslocamentos + 1, pois a sáida conta como deslocamento
            break;
        }
        carroAtual.deslocamento++;
        Enfileira(carroAtual, filaAuxiliar);
    }
    return carroEncontrado;
}

/* Função para restaurar a fila auxiliar de volta ao estacionamento */
void restaurarFilaAuxiliar(TipoFila *filaAuxiliar, TipoFila *estacionamento){
    TipoCarro carroAtual;
    while (!Vazia(*filaAuxiliar)) {
        Desenfileira(filaAuxiliar, &carroAtual);
        Enfileira(carroAtual, estacionamento);
    }
}

//Função para estacionar carros da fila ruaMonsenhor no estacionamento
void estacionarCarrosDaRua(TipoFila *ruaMonsenhor, TipoFila *estacionamento, TipoFila *filaAuxiliar){
    TipoCarro carroAtual;

    while(!Vazia(*ruaMonsenhor)){
        Desenfileira(ruaMonsenhor, &carroAtual);
        if (!estacionamentoEstaCheio(estacionamento) && carroAtual.prioridade == 1) {
            Enfileira(carroAtual, estacionamento);
            printf("Carro de placa %s foi estacionado.\n", carroAtual.placa);
            continue;
        }
        Enfileira(carroAtual, filaAuxiliar);
    }
}

//Função principal para retirada de carro
void retirarCarro(TipoFila *ruaMonsenhor, TipoFila *estacionamento, TipoCarro carro){
    TipoFila filaAuxiliar;
    FFVazia(&filaAuxiliar);

    // Verifica e remove o carro, e organiza os carros na filaAuxiliar
    int carroEncontrado = verificarCarro(estacionamento, carro, &filaAuxiliar);

    // Restaura os carros da fila auxiliar para o estacionamento
    restaurarFilaAuxiliar(&filaAuxiliar, estacionamento);

    if(!carroEncontrado){
        printf("\nCarro de placa: %s não encontrado no estacionamento...\n", carro.placa);
        return;
    }

    //Estaciona carros com prioridade da ruaMonsenhor
    estacionarCarrosDaRua(ruaMonsenhor, estacionamento, &filaAuxiliar);

    //Finaliza estacionando carros restantes
    restaurarFilaAuxiliar(&filaAuxiliar, ruaMonsenhor);

    while(!Vazia(*ruaMonsenhor) && !estacionamentoEstaCheio(estacionamento)){
        TipoCarro carroAtual;
        Desenfileira(ruaMonsenhor, &carroAtual);
        Enfileira(carroAtual, estacionamento);
        printf("Carro de placa %s foi estacionado.\n", carroAtual.placa);
    }
}

// Função para exibir as ruas
void exibirRuas(TipoFila BomJesusDosPassos, TipoFila MonsenhorJoaoPedro) {
    printf("\nEstacionamento: \n");
    Vazia(BomJesusDosPassos) ? printf("\nNao ha carros no estacionamento.") : exibe(BomJesusDosPassos);

    printf("\n\nRua Monsenhor Joao Pedro: \n");
    Vazia(MonsenhorJoaoPedro) ? printf("\nNao ha carros na rua Monsenhor Joao Pedro.") : exibe(MonsenhorJoaoPedro);
}

int main() {

    TipoFila BomJesusDosPassos; // Estacionamento
    FFVazia(&BomJesusDosPassos);

    TipoFila MonsenhorJoaoPedro; // Entrada/Fila de espera
    FFVazia(&MonsenhorJoaoPedro);

    TipoCarro carro;

    carro.deslocamento = 0;
    carro.prioridade = 0;
    strcpy(carro.placa, "1");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "2");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "3");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "4");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "5");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 1;
    strcpy(carro.placa, "6");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 0;
    strcpy(carro.placa, "7");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 1;
    strcpy(carro.placa, "8");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 0;
    strcpy(carro.placa, "9");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 1;
    strcpy(carro.placa, "10");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);

    // TipoFila JaimeGoncalves; Eh necessaria?
    // FFVazia(&JaimeGoncalves);
    int opcao = 0;

    do {
        printf("\nSISTEMA DE ESTACIONAMENTO\n");
        printf("\n 1. Estacionar carro\n");
        printf(" 2. Retirar carro\n");
        printf(" 3. Exibir ruas\n");
        printf(" 0. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer deixado pelo scanf

        switch (opcao) {
        case 1:
            printf("\nDigite a placa do carro: ");
            fgets(carro.placa, 10, stdin);
            // Remove o newline do final da string, se presente
            carro.placa[strcspn(carro.placa, "\n")] = '\0';

            printf("\nO carro tem alguma prioridade, [S]/[N]: ");
            char resposta[2];
            fgets(resposta, 2, stdin);

            if (strcmp("S", resposta) == 0 || strcmp("s", resposta) == 0) {
                carro.prioridade = 1;
            } else {
                carro.prioridade = 0;
            }

            carro.deslocamento = 0;

            estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
            getchar();
            break;
        case 2:
            printf("\nDigite a placa do carro: ");
            char placa[10];
            fgets(placa, 10, stdin);
            // Remove o newline do final da string, se presente
            placa[strcspn(placa, "\n")] = '\0';

            // TipoCarro temporário para remocao
            TipoCarro carroBusca;
            // Atribuindo a placa obtida anteriormente ao carroBusca
            strcpy(carroBusca.placa, placa);

            // Chamando a funcao
            retirarCarro(&MonsenhorJoaoPedro, &BomJesusDosPassos, carroBusca);

            break;
        case 3:
            exibirRuas(BomJesusDosPassos, MonsenhorJoaoPedro);
            break;
        default:
            if (opcao != 0) {
                printf("\nVoce digitou uma opcao invalida. Por favor, digite outro valor.\n");
            }
            break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
        system("cls");
        system("clear");
    } while (opcao != 0);

    return 0;
}
