#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Variavel especifica para tempo do clock1
clock_t InicioSec, FimSec;
unsigned long int tempo1;

//Variavel especifica para tempo do clock2
clock_t InicioSec2, FimSec2;
unsigned long int tempo2;

//Fun��o que atribui valores aleatorios a um vetor de tamanho t
void FillAleatory(int vet[], int n){
	srand(time(NULL));
	
	for(int i=0; i<n ; i++){
		vet[i] = rand() % n + 1;
	}
}

//Algor�timo de ordenacao QuickSort em etapas, retorna o �ndice do corte
	//O piv� � um elemento escolhido de um array para dividir os dados em duas partes.
	int particionarVetor(int *vet, int inicio, int fim){
		//Calcula a m�dia dos tres valores para tentar encontrar um ponto balanceado de divis�o
		int pivot = (vet[inicio] + vet[fim] + vet[(inicio+fim)/2])/3;
		
		while(inicio < fim){
			/* Estes dois la�os pegam a posicao central e comparam com tudo o que antecede ou 
			 * que seja posterior, se caso tudo o que vier antes ou ap�s, j� estiver em ordem
			 * entao avan�a pra direita ou esquerda o ponteiro ate chegar ao pivot.
			 *
			 * Caso quebre a condi��o, realizara a mudan�a apos os la�os
			 */
			
			while(inicio < fim && vet[inicio] <= pivot) inicio++; 
			while(inicio < fim && vet[fim] > pivot) fim--; 
			
			//Realizando a mudan�a
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

//Fun��o que imprime o vetor
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
        printf("Erro ao alocar mem�ria!..\n");
        return 1; // Sair do programa se a aloca��o falhar
    }
    
	printf("\n_________[ Teste QuickSort ]_________\n");
	
	//Medindo o tempo de execu��o da ordena��o QuickSort
	InicioSec = clock();
	
	quickSort(vetor, 0, n);
	FimSec = clock();
	tempo1 = (FimSec - InicioSec)*1000/CLOCKS_PER_SEC;
	
	printf("\nTempo de clock: %lu milissegundos\n",tempo1);

	printf("\n_________[ Teste Por Selecao ]_________\n");	
	//Medindo o tempo de execu��o da ordenacao por selecao
	InicioSec2 = clock();
	ordenacaoSelecao(vetor2, n);
	FimSec2 = clock();
	
	tempo2 = (FimSec2 - InicioSec2)*1000/CLOCKS_PER_SEC;
	printf("\nTempo de clock (Busca binaria): %lu milissegundos\n",tempo2);
}
