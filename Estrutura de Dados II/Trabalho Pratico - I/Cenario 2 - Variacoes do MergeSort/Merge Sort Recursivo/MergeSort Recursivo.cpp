#include<stdio.h> 
#include<stdlib.h>
#include<time.h>

// Vari�veis globais para contabilizar compara��es e c�pias
long long comparacoes = 0;
long long copias = 0;

// Fun��o para mesclar dois subvetores
void mesclar(int vetor[], int inicio, int meio, int fim){
    // Tamanho total do intervalo a ser mesclado
    int tamanho = fim - inicio + 1;

    // Cria��o de um �nico vetor auxiliar
    int *auxiliar = (int*)malloc(tamanho * sizeof(int));

    // �ndices para os subvetores e o vetor auxiliar
    int i = inicio, j = meio + 1, k = 0;

    // Mescla os dois subvetores
    while(i <= meio && j <= fim){
        comparacoes++; // Incrementa o contador de compara��es
        if(vetor[i] <= vetor[j]){
            auxiliar[k++] = vetor[i++];
        } else {
            auxiliar[k++] = vetor[j++];
        }
        copias++; // Incrementa o contador de c�pias
    }

    // Copia os elementos restantes do lado esquerdo, se houver
    while(i <= meio){
        auxiliar[k++] = vetor[i++];
        copias++;
    }

    // Copia os elementos restantes do lado direito, se houver
    while(j <= fim){
        auxiliar[k++] = vetor[j++];
        copias++;
    }

    // Copia os elementos do vetor auxiliar de volta para o vetor original
    for(k = 0; k < tamanho; k++){
        vetor[inicio + k] = auxiliar[k];
        copias++;
    }

    // Libera a mem�ria alocada para o vetor auxiliar
    free(auxiliar);
}

// Fun��o recursiva para dividir e ordenar o vetor
void ordenarRecursivo(int vetor[], int inicio, int fim){
    if(inicio < fim){
        int meio = inicio + (fim - inicio) / 2; // Calcula o ponto m�dio
        ordenarRecursivo(vetor, inicio, meio); // Ordena a primeira metade
        ordenarRecursivo(vetor, meio + 1, fim); // Ordena a segunda metade
        mesclar(vetor, inicio, meio, fim); // Mescla as metades ordenadas
    }
}

// Fun��o para exibir os elementos de um vetor
void exibirVetor(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]){
    int tamanho;
    char nome_arquivo_saida[100] = "saida.txt";
    FILE *arquivo_saida;

    // Verifica se o nome do arquivo de sa�da foi fornecido via argumentos de linha de comando
    if(argc > 1){
        snprintf(nome_arquivo_saida, sizeof(nome_arquivo_saida), "%s", argv[1]);
    }

    // Solicita o tamanho do vetor ao usu�rio
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);

    // Aloca mem�ria para o vetor e preenche com n�meros aleat�rios
    int *vetor = (int*)malloc(tamanho * sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < tamanho; i++){
        vetor[i] = rand() % 100000;
    }

    printf("\n___________________________________________________________________________________________________________________\n");
    printf("Vetor Gerado:\n");
    exibirVetor(vetor, tamanho);

    // Mede o tempo de execu��o do algoritmo
    clock_t inicio_tempo = clock();
    ordenarRecursivo(vetor, 0, tamanho-1);
    clock_t fim_tempo = clock();
    double tempo_gasto = (double)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;

    printf("\n___________________________________________________________________________________________________________________\n");
    printf("Vetor Ordenado:\n");
    exibirVetor(vetor, tamanho);

    // Exibe as estat�sticas do processo de ordena��o
    printf("\n___________________________________________________________________________________________________________________\n");
    printf("Numero de Comparacoes: %lld\n", comparacoes);
    printf("Numero de Copias: %lld\n", copias);
    printf("Tempo de Processamento: %.6f segundos\n", tempo_gasto);

    // Cria ou abre o arquivo de sa�da e salva as estat�sticas
    arquivo_saida = fopen(nome_arquivo_saida, "w");
    if(arquivo_saida == NULL){
        printf("Erro ao criar ou abrir o arquivo de saida");
        free(vetor);
        return 1;
    }

    fprintf(arquivo_saida, "N�mero de Compara��es: %lld\n", comparacoes);
    fprintf(arquivo_saida, "N�mero de C�pias: %lld\n", copias);
    fprintf(arquivo_saida, "Tempo de Processamento: %.6f segundos\n", tempo_gasto);

    fclose(arquivo_saida); // Fecha o arquivo de sa�da
    free(vetor); // Libera a mem�ria alocada para o vetor

    return 0;
}

