#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

//Conforme o enunciado testes para k=5
#define K 10

//1 para habilitar mensagens 0 para desativar
#define DEBUG 0

//Variavel especifica para tempo do clock1
clock_t InicioSec, FimSec;
unsigned long long int tempo1;

//Variavel especifica para tempo do clock2
clock_t InicioSec2, FimSec2;
unsigned long long int tempo2;

//Funcao que atribui valores aleatorios a um vetor de tamanho t
void FillAleatory(long long int *vet, long long int n){
	long long int i;
	srand(time(NULL));
	
	for(i=0; i<n ; i++){
		vet[i] = rand() % 1000;
	}
}

//Funcao que gera o pior caso de tamanho n
void gerarPiorCaso(int *vetor, long long int n){
	int i;
	
	for(i = 0; i<n; i++){
		vetor[i] = n-i;
	}
}

//Funcao que faz o merge de multiplos subvetores em (k subvetores)
void merge(long long int *vet, long long int inicio, long long int meio, long long int fim, long long int *vetor_temporario){
	//Enquanto houver elementos, realiza o merge
	long long int i = inicio, j = meio, posicao;
	
	for(posicao = inicio; posicao <  fim; posicao++){
		if(i < meio && (j >= fim || vet[i] <= vet[j])){
			vetor_temporario[posicao] = vet[i];
			i++;
		}else{
			vetor_temporario[posicao] = vet[j];
			j++;
		}
	}
	
	//Apos, copia o restante
	for(posicao = inicio; posicao < fim; posicao++){
		vet[posicao] = vetor_temporario[posicao];
	}
}

//Funcao que e responsavel pela chamada recursiva utilizando (k) particoes
void multiwayMergeSort(long long int *vet, long long int inicio, long long int fim, int k, long long int *vetor_temporario){
	//Pega o tamanho
	long long int i, tamanho_total = fim - inicio;
	
	//Significa que o vetor e nulo ou unico
	if(tamanho_total <= 1){
		if(DEBUG){
			printf("\nVetor menor que 1 !...");
		}
		return;
	}
	
	//Dividindo em (k) particoes desejadas
	long long int tamanhos_subvetores[k+1];
	tamanhos_subvetores[0] = inicio;
	
	for(i = 1; i <= k; i++){
		//Evita valores nao inteiros para o vetor
		tamanhos_subvetores[i] = tamanhos_subvetores[i-1] + tamanho_total / k + (i <= (tamanho_total % k));
	}
	
	//Chamada recursiva para cada pedaço
	for(i = 0; i < k; i++){
		multiwayMergeSort(vet, tamanhos_subvetores[i], tamanhos_subvetores[i+1], k, vetor_temporario);
	}
	
	//Agora une em um vetor unico
	for(i = 1; i < k; i++){
		merge(vet, tamanhos_subvetores[0], tamanhos_subvetores[i], tamanhos_subvetores[i+1], vetor_temporario);
	}
}

//Função que imprime o vetor
void imprimir(long long int *vet, long long int size){
	int i;
	printf("\nVetor = [ ");
	for(i=0; i<size; i++){
		printf("%lld, ", vet[i]);
	}
	printf(" ]\n");
}

int main(int argc, char *argv[]){
	if(argc != 3){ //Pois espera 3 parametros
        printf("Espera-se: %s [tamanho do vetor], [m] e [arquivo de saída]\n", argv[0]);
        exit(1);
    }
    //argumentos: nome do arquivo.cpp, tamanho do vetor (n), (k) divisoes desejadas, arquivo para salvar os dados
	
	//Coleta a entrada por argumento da posicao [1] (n = tamanho) e converte para inteiro
	long long int n = atoll(argv[1]);
	
	if (n <= 0) {
		printf("Erro: O tamanho do vetor deve ser maior que 0.\n");
		exit(1);
	}
	
	//Suposto arquivo para salvar os dados
	const char *sirigueijo = argv[2];
	
	//Criando os vetores de maneira dinamica 
	long long int *vetor = (long long int*)malloc(n * sizeof(long long int)); 
	
	//Vetores temporarios auxiliares
	long long int *vetor_temporario = (long long int*)malloc(n * sizeof(long long int)); 
	
	//Preenchendo com valores aleatorios ou pior caso
	
	//gerarPiorCaso(vetor, n);
	FillAleatory(vetor, n); 
	
	//Medindo o tempo de execução da ordenação para k = 5
	InicioSec = clock();
	multiwayMergeSort(vetor, 0, n, K, vetor_temporario);
	FimSec = clock();
	tempo1 = (FimSec - InicioSec)*1000/CLOCKS_PER_SEC;

	
	//Abrindo um arquivo para gravacao de dados e verificando a abertura
	FILE *arquivo = fopen(sirigueijo, "a");
	
	//Erro e libera memoria
	if(!arquivo){
		printf("\nErro ao abrir arquivo!...");
		free(vetor);
		exit(1);
	}
	
	//Caso de tudo certo, entao escreve os dados no arquivo
	fprintf(arquivo, "Tamanho do vetor: %lld\n", n);
	fprintf(arquivo, "Para [ k = %d ], Tempo: %llu ms\n", K, tempo1);
	
	fclose(arquivo);
	
	//Imprime o vetor para verificacao
	//imprimir(vetor, n);
	
	// Libera a memória alocada 
    free(vetor);
    free(vetor_temporario);
    
    printf("Resultados gravados no arquivo '%s'.\n", sirigueijo);
}
