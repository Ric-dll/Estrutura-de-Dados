#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

// Variáveis globais para estatísticas
long int comparacoes = 0; // Número de comparações realizadas
long int copias = 0; // Número de cópias realizadas

// Função para mesclar dois subvetores ordenados
void mesclar(int vetor[], int inicio, int meio, int fim){
    int tamanho_esquerdo = meio - inicio + 1; // Tamanho do subvetor esquerdo
    int tamanho_direito = fim - meio; // Tamanho do subvetor direito

    // Aloca memória para os subvetores temporários
    int *vetor_esquerdo = (int *)malloc(tamanho_esquerdo * sizeof(int));
    int *vetor_direito = (int *)malloc(tamanho_direito * sizeof(int));

    // Copia elementos para os subvetores esquerdo e direito
    for(int i = 0; i < tamanho_esquerdo; i++){
        vetor_esquerdo[i] = vetor[inicio + i];
        copias++;
    }
    for(int i = 0; i < tamanho_direito; i++){
        vetor_direito[i] = vetor[meio + 1 + i];
        copias++;
    }

    int i = 0, j = 0, k = inicio;
    // Mescla os subvetores no vetor original
    while(i < tamanho_esquerdo && j < tamanho_direito){
        comparacoes++; // Conta uma comparação
        if(vetor_esquerdo[i] <= vetor_direito[j]){
            vetor[k] = vetor_esquerdo[i];
            copias++;
            i++;
        }
		else{
            vetor[k] = vetor_direito[j];
            copias++;
            j++;
        }
        k++;
    }

    // Copia os elementos restantes do subvetor esquerdo
    while(i < tamanho_esquerdo){
        vetor[k] = vetor_esquerdo[i];
        copias++;
        i++;
        k++;
    }

    // Copia os elementos restantes do subvetor direito
    while(j < tamanho_direito){
        vetor[k] = vetor_direito[j];
        copias++;
        j++;
        k++;
    }

    // Libera a memória alocada para os subvetores
    free(vetor_esquerdo);
    free(vetor_direito);
}

// Função para ordenar iterativamente
void ordenarIterativo(int vetor[], int tamanho){
    // Controla o tamanho do subvetor em cada etapa
    for(int tamanho_subvetor = 1; tamanho_subvetor < tamanho; tamanho_subvetor *= 2){
        // Itera pelos pares de subvetores a serem mesclados
        for(int inicio = 0; inicio < tamanho - 1; inicio += 2 * tamanho_subvetor){
            int meio = inicio + tamanho_subvetor - 1;
            int fim = inicio + 2 * tamanho_subvetor - 1;
            if(fim >= tamanho) fim = tamanho - 1; // Ajusta o limite do vetor
            if(meio < tamanho) mesclar(vetor, inicio, meio, fim);
        }
    }
}

// Exibe os elementos de um vetor
void exibirVetor(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++) printf("%d ", vetor[i]);
    printf("\n");
}

// Salva as estatísticas da ordenação em um arquivo
void salvarEstatisticasEmArquivo(double tempo){
    FILE *arquivo = fopen("saida.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }
    fprintf(arquivo, "Estatisticas da Ordenacao:\n");
    fprintf(arquivo, "Numero de comparacoes: %ld\n", comparacoes);
    fprintf(arquivo, "Numero de copias: %ld\n", copias);
    fprintf(arquivo, "Tempo total de processamento: %.6f segundos\n", tempo);
    fclose(arquivo);
}

// Função principal
int main(int argc, char *argv[]){
    int tamanho;

    // Se os argumentos não forem fornecidos, solicita os dados ao usuário
    if(argc != 3){
        printf("Argumentos nao fornecidos. Por favor, insira os dados manualmente.\n");
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);
    } 
	else{
        // Usa os argumentos fornecidos
        tamanho = atoi(argv[1]);
    }

    // Valida o tamanho do vetor
    if(tamanho <= 0){
        printf("O tamanho do vetor deve ser um numero inteiro positivo.\n");
        return 1;
    }

    // Aloca memória para o vetor
    int *vetor = (int *)malloc(tamanho * sizeof(int));
    if(vetor == NULL){
        printf("Erro ao alocar memoria para o vetor.\n");
        return 1;
    }

    // Gera valores aleatórios para preencher o vetor
    srand(time(NULL));
    for(int i = 0; i < tamanho; i++){
		vetor[i] = rand() % 100000;
	}

    printf("\n_______________________________________________________________________________________________\n");
    printf("Vetor Gerado:\n");
    exibirVetor(vetor, tamanho);

    // Mede o tempo de execução da ordenação
    clock_t inicio = clock();
    ordenarIterativo(vetor, tamanho);
    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n_______________________________________________________________________________________________\n");
    printf("Vetor Ordenado:\n");
    exibirVetor(vetor, tamanho);
    printf("\n_______________________________________________________________________________________________\n");
    printf("Numero de comparacoes: %ld\n", comparacoes);
    printf("Numero de copias: %ld\n", copias);
    printf("Tempo total de processamento: %.6f segundos\n", tempo);

    // Salva as estatísticas em um arquivo
    salvarEstatisticasEmArquivo(tempo);

    free(vetor); // Libera a memória alocada para o vetor
    
    return 0;
}
