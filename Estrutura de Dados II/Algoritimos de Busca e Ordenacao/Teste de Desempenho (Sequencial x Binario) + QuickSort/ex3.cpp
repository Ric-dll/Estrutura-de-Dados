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
			quickSort(vet, inicio, indice-1);	//Ordenar a metade esquerda
			quickSort(vet, indice, fim);			//Ordenar a metade direita
		}
	}
//Fim quickSort

//Algoritimo de busca sequencial
int SearchSeq(int vet[], int key, int n){
	int i=0;
	while(i < n && vet[i] != key){
		i++;
	}
	if(i<n){
		return 1;
	}
	return 0;
}

//Algoritimo de busca binaria
int SearchBin(int *vet, int inicio, int fim, int key){
	if(inicio <= fim){
		int meio = (inicio+fim)/2;
		if(vet[meio] == key){
			return meio;
		} 
		
		if(key < vet[meio]){
			//Chamada recursiva para a metade esquerda
			return SearchBin(vet, inicio, meio-1, key);
 		}
		
		//Caso ainda nao tiver sido chamada em nenhuma outra condicao...
		//Chamada recursiva para a metade direita
		return SearchBin(vet, meio+1, fim, key);
		
	}
	//caso contrário
	return -1;
}

//Função que imprime o vetor
void imprimir(int vet[], int size){
	printf("\nVetor = [ ");
	for(int i=0; i<size; i++){
		printf("%i, ", vet[i]);
	}
	printf(" ]\n");
}

int main(void){
	
//Teste 3 - Vetor relativo e testes de busca 
	printf("\n_________[ Teste 3 ]_________\n");
		
	printf("\nDigite o tamanho do vetor: ");
	int n; scanf("%i", &n);
	
	//Criando o vetor de maneira dinamica e preenchendo com valores aleatorios
	int *v3 = (int*)malloc(n * sizeof(int)); 
	FillAleatory(v3, n);
	//imprimir(v3, n);
	
	printf("\n_________[ Teste de Clock ]_________\n");
	printf("\nBuscar key: ");
	int key; scanf("%i", &key);
	
	//Medindo o tempo de execução da busca sequencial
	InicioSec = clock();
	SearchSeq(v3, key, n);
	FimSec = clock();
	
	tempo1 = (FimSec - InicioSec)*1000/CLOCKS_PER_SEC;
	printf("\nTempo de clock (Busca Sequencial): %lu milissegundos\n",tempo1);

	//Medindo o tempo de execução da busca binaria
	InicioSec2 = clock();
	SearchBin(v3, 0, n-1, key);
	FimSec2 = clock();
	
	tempo2 = (FimSec2 - InicioSec2)*1000/CLOCKS_PER_SEC;
	printf("\nTempo de clock (Busca binaria): %lu milissegundos\n",tempo2);
}
