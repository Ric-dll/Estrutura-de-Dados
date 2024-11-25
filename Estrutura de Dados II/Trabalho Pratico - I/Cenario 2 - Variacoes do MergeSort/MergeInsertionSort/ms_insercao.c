#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

#define M 100

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
void gerarPiorCaso(long long int *vetor, long long int n){
	long long int i;
	
	for(i = 0; i<n; i++){
		vetor[i] = n-i;
	}
}

//Implementando a ordenacao por Insercao para controle do Merge
void InsertionSort(long long int *vet, long long int inicio, long long int fim){
	long long int referencial, i, j;
	
	//Primeiro loop de inicio ate fim, comecando na segunda posicao
	for(i = inicio+1; i <= fim; i++){
		//Armazena o valor atual do laco que ira ser alocado na posicao correta
		referencial = vet[i];
		//Compara com o elemento anterior
		j = i-1;
		
		//Cada elemento maior que o referencial sera movido a frente
		while(j >= inicio && vet[j] > referencial){
			vet[j+1] = vet[j];
			j--;
		}
		vet[j+1] = referencial;
	}
}
	
//Funcao Merge, combinacao de dois subarrays ordenados
void merge(long long int *vetor, long long int inicio, long long int meio, long long int fim){
	//Tamanho do subarray
	long long int i, j, k, size_subarray = fim-inicio+1;
	//Flags para indicar quando os subarrays terminam
	long long int fim_subArray1=0, fim_subArray2=0;
	
	//Vetor temporario para armazenar a combinacao de elementos
	int *vetor_temporario = (int *)malloc(size_subarray * sizeof(int));
	//Ponteiros para cada subarray
	long long int point_inicio = inicio, point_meio = meio;
	
	//Loop que funciona ate o tamanho total do SUBARRAY
	for(i=0; i < size_subarray; i++){
		if(!fim_subArray1 && !fim_subArray2){
			 //Compara os elementos de ambos os subarrays e insere o menor no vetor temporário
			if(vetor[point_inicio] < vetor[point_meio]){
				vetor_temporario[i] = vetor[point_inicio++];
			}else{
				//Insere o menor DO segundo subarray
				vetor_temporario[i] = vetor[point_meio++];
			}
			
			//Verifica as flags em caso de termino dos subarrays
			if(point_inicio > meio-1){
				fim_subArray1 = 1;
			}
			if(point_meio > fim){
				fim_subArray2 = 1;
			}
			
		}else{ //Caso um dos subarrays ja tenha sito terminado
			//Porem nao o primeiro ou o segundo
			if(!fim_subArray1){
				vetor_temporario[i] = vetor[point_inicio++];
			}else{ 
				vetor_temporario[i] = vetor[point_meio++];
			}
		}
	}
	//Agora realiza a copia obtida no vetor temporario para o original
	for(j = 0, k = inicio; j < size_subarray; j++, k++){
		vetor[k] = vetor_temporario[j];
	}
	//Libera a memória alocada para o vetor temporário
	free(vetor_temporario);
}

//Funcao que ordena o vetor usando MergeSort, porem utuliza insercao para valores (m) passados por parametro
void MergeSortAlterado(long long int *vetor, long long int inicio, long long int fim, int m){
	//Verificando se a particao e menor ou igual a (m)
	long long int v = fim-inicio+1;
	//Se sim, usa o Insertion
	if(v <= m){
		InsertionSort(vetor, inicio, fim);
	}else 
		if(inicio < fim){
			//Calcula o indice do meio atual
			long long int indice_meio = (inicio+fim)/2;
			//Ordena a primeira metade
			MergeSortAlterado(vetor, inicio, indice_meio, m);
			//Ordena a segunda metade
			MergeSortAlterado(vetor, indice_meio+1, fim, m);
			//Combina ambas
			merge(vetor, inicio, indice_meio+1, fim);
	}
}

//Função que imprime o vetor
void imprimir(long long int *vet, long long int size){
	long long int i;
	printf("\nVetor = [ ");
	for(i=0; i<size; i++){
		printf("%lld, ", vet[i]);
	}
	printf(" ]\n");
}

//Funcao principal
int main(int argc, char *argv[]){
	
	if(argc != 3){ 
        printf("Espera-se: %s [tamanho do vetor], [m] e [arquivo de saída]\n", argv[0]);
        exit(1);
    }
	
	//argumentos: arquivo.cpp, tamanho do vetor (n), (m) e nome do arquivo
	 
	//Coleta a entrada por argumento da posicao [1]
	long long int n = atoll(argv[1]);
	
	//Suposto arquivo para salvar os dados
	const char *bob_esponja = argv[2];
	
	//Criando os vetores de maneira dinamica 
	long long int *vetor = (long long int*)malloc(n * sizeof(long long int)); 
	
	//Preenchendo com valores aleatorios ou pior caso
	
	//gerarPiorCaso(vetor, n);
	FillAleatory(vetor, n); 

	//Medindo o tempo de execução da ordenação para m = 10
	InicioSec = clock();
	MergeSortAlterado(vetor, 0, n-1, M);
	FimSec = clock();
	tempo1 = (FimSec - InicioSec)*1000/CLOCKS_PER_SEC;	
	
	//Abrindo um arquivo para gravacao de dados e verificando a abertura
	FILE *arquivo = fopen(bob_esponja, "a");
	
	//Erro e libera memoria
	if(!arquivo){
		printf("\nErro ao abrir arquivo!...");
		free(vetor);
		exit(1);
	}
	
	//Caso de tudo certo, entao escreve os dados no arquivo
	fprintf(arquivo, "\nTamanho do vetor: %lld\n", n);
	fprintf(arquivo, "Para [ m = %d ], Tempo: %llu ms\n", M, tempo1);
	fprintf(arquivo, "\n--------------------------------------------------------------------");
	fclose(arquivo);
	
	//Libera a memória alocada 
    free(vetor);
    
    printf("Resultados gravados no arquivo '%s'.\n", bob_esponja);

}
