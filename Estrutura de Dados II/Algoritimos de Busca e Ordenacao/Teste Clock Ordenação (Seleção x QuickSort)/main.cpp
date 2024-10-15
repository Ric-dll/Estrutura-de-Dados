#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Variavel especifica para tempo do clock1
clock_t InicioSec, FimSec;
unsigned long int tempo1;

//Variavel especifica para tempo do clock2
clock_t InicioSec2, FimSec2;
unsigned long int tempo2;

//Função que atribui valores aleatorios a um vetor de tamanho t
void FillAleatory(int vet[], int n){
	srand(time(NULL));
	
	for(int i=0; i<n ; i++){
		vet[i] = rand() % n + 1;
	}
}

//Algorítimo de ordenacao QuickSort em etapas, retorna o índice do corte
	//O pivô é um elemento escolhido de um array para dividir os dados em duas partes.
	int particionarVetor(int *vet, int inicio, int fim){
		//Calcula a média dos tres valores para tentar encontrar um ponto balanceado de divisão
		int pivot = (vet[inicio] + vet[fim] + vet[(inicio+fim)/2])/3;
		
		while(inicio < fim){
			/* Estes dois laços pegam a posicao central e comparam com tudo o que antecede ou 
			 * que seja posterior, se caso tudo o que vier antes ou após, já estiver em ordem
			 * entao avança pra direita ou esquerda o ponteiro ate chegar ao pivot.
			 *
			 * Caso quebre a condição, realizara a mudança apos os laços
			 */
			
			while(inicio < fim && vet[inicio] <= pivot) inicio++; 
			while(inicio < fim && vet[fim] > pivot) fim--; 
			
			//Realizando a mudança
			int aux = vet[inicio];
			vet[inicio] = vet[fim];
			vet[fim] = aux;
		}
		return inicio;
	}

	//Funcao recursiva de ordenacao principal
	/* Basicamente pega o indice ao meio e realiza duas chamadas recursivas, uma do inicio ate a metade
	 * e outra da metade ao final, assim realizando o metodo de divisao e conquista*/
	void quickSort(int *vet, int inicio, int fim){
		if(inicio < fim){
			int indice = particionarVetor(vet, inicio, fim);
			quickSort(vet, inicio, indice-1);		//Ordenar a metade esquerda
			quickSort(vet, indice, fim);			//Ordenar a metade direita
		}
	}
//Fim quickSort

//Metodo de ordenacao por selecao
void ordenacaoSelecao(int *vet, int n){
	int min, temp;
	for(int i=0; i<n; i++){
		min = i;
		for(int j=i+1; j<=n; j++){
			if(vet[j] < min){
				min = j;
			}
		}
		if(min != i){
			temp = vet[min];
			vet[min] = vet[i];
			vet[i] = temp;
		}
	}
}

//Ordenacao bolha

//Função que imprime o vetor
void imprimir(int vet[], int size){
	printf("\nVetor = [ ");
	for(int i=0; i<size; i++){
		printf("%i, ", vet[i]);
	}
	printf(" ]\n");
}

int main(void){
	
//Teste 
	printf("\n_________[ Teste Clock ]_________\n");
		
	printf("\nDigite o tamanho do vetor: ");
	int n; scanf("%i", &n);

	//Criando o vetor de maneira dinamica e preenchendo com valores aleatorios
	int *vetor = (int*)malloc(n * sizeof(int)); 
	FillAleatory(vetor, n);
	
	int *vetor2 = (int*)malloc(n * sizeof(int)); 
	FillAleatory(vetor2, n);
	//imprimir(vetor, n);
	
	if(vetor == NULL) {
        printf("Erro ao alocar memória!..\n");
        return 1; // Sair do programa se a alocação falhar
    }
    
	printf("\n_________[ Teste QuickSort ]_________\n");
	
	//Medindo o tempo de execução da ordenação QuickSort
	InicioSec = clock();
	
	quickSort(vetor, 0, n);
	FimSec = clock();
	tempo1 = (FimSec - InicioSec)*1000/CLOCKS_PER_SEC;
	
	printf("\nTempo de clock: %lu milissegundos\n",tempo1);

	printf("\n_________[ Teste Por Selecao ]_________\n");	
	//Medindo o tempo de execução da ordenacao por selecao
	InicioSec2 = clock();
	ordenacaoSelecao(vetor2, n);
	FimSec2 = clock();
	
	tempo2 = (FimSec2 - InicioSec2)*1000/CLOCKS_PER_SEC;
	printf("\nTempo de clock (Busca binaria): %lu milissegundos\n",tempo2);
}
