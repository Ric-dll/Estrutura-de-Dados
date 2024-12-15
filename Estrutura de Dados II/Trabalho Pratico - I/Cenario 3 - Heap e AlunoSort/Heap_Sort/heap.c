#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Variavel especifica para tempo do clock1
clock_t InicioSec, FimSec;
unsigned long long int tempo1;

//Função que atribui valores aleatorios a um vetor de tamanho t
void FillAleatory(int vet[], int n){
	srand(time(NULL));
	
	for(int i=0; i<n ; i++){
		vet[i] = rand() % 1000;
	}
}


//Algorítimo de ordenacao HeapSort
	//Função responsável por realizar a troca
	void criaHeap(int *vet, int i, int f){
		int aux = vet[i];
		int j = i*2+1;
		
		while(j <= f){
			if(j < f && vet[j] < vet[j+1]){
				if(vet[j] <= vet[j+1]){
					j = j+1;
				}
			}
			if(aux < vet[j]){
				vet[i] = vet[j];
				i = j;
				j = i*2+1;
			}else{
				//j = f+1;
				break; //Assim está funcionando melhor
			}
		}
		vet[i] = aux;
	}
	
	//Função HeapSort
	void heapSort(int *vet, int n){
		
		int aux;
		
		//Constroi a tal da Heap
		for(int i=(n/2) - 1; i >= 0; i--){
			criaHeap(vet, i, n-1);
		}
		
		//Extrai os elemento da "Heap" um por vez
		for(int i=(n-1); i > 1; i--){
			//Movendo a raiz atual para o final
 			aux = vet[0];
			vet[0] = vet[i];
			vet[i] = aux;
			criaHeap(vet, 0, i-1);
		}
	}
//Fim HeapSort


//Função que imprime o vetor
void imprimir(int vet[], int size){
	printf("\nVetor = [ ");
	for(int i=0; i<size; i++){
		printf("%i, ", vet[i]);
	}
	printf(" ]\n");
}

int main(int argc, char *argv[]){
	
	if(argc != 3){ 
        printf("Espera-se: %s [tamanho do vetor] e [arquivo de saída]\n", argv[0]);
        exit(1);
    }
	
	//Coleta a entrada por argumento da posicao [1]
	int n = atoll(argv[1]);
	
	//Criando o vetor de maneira dinamica e preenchendo com valores aleatorios
	int *vetor = (int*)malloc(n * sizeof(int)); 
	
	//Suposto arquivo para salvar os dados
	const char *bob_esponja = argv[2];
	
	FillAleatory(vetor, n);
	//imprimir(vetor, n);
	
	//Medindo o tempo de execução da ordenação
	InicioSec = clock();
	heapSort(vetor, n);
	FimSec = clock();
	tempo1 = (FimSec - InicioSec)*1000/CLOCKS_PER_SEC;
	
	//imprimir(vetor, n);
	
	//Abrindo um arquivo para gravacao de dados e verificando a abertura
	FILE *arquivo = fopen(bob_esponja, "a");
	
	//Erro e libera memoria
	if(!arquivo){
		printf("\nErro ao abrir arquivo!...");
		free(vetor);
		exit(1);
	}
	
	fprintf(arquivo, "\nTamanho do vetor: %i\n", n);
	fprintf(arquivo, "Para [ tamanho = %d ], Tempo: %llu ms\n", n, tempo1);
	
	fclose(arquivo);
    
    printf("Resultados gravados no arquivo '%s'.\n", bob_esponja);
	
	// Libera memória
    free(vetor);
}

