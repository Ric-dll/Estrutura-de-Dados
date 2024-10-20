#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NOMES 100
#define MAX_TAM 100

void initVetOrdenado(int *vet, int n){
	for(int i=0; i<n; i++){
		vet[i] = i*2;
	}
}

int isOrdenado(int *vet, int n){
	for(int i=0; i<n; i++){
		if(vet[i] >  vet[i+1] && vet[i] < n){
			return 0;	
		}
	}
	return 1;
}

void imprimeVet(int *vet, int n){
	printf("\n Vetor = [");
	
	for(int i=0; i<n; i++){
		printf(" %i", vet[i]);
		if(i < n-1) printf(",");
	}

	printf("]\n");
}

//Função que adiciona o numero na posiçãoc orreta do vetor
void addNumero(int *vet, int *n, int x){
	int i;
	//For que busca a posição onde deve-se inserir (x)
	for(i = *n-1; (i >= 0 && vet[i] > x); i--){
		vet[i+1] = vet[i];
	}
	//Responsável por inserir corretamente
	vet[i+1] = x;
	(*n)++;
}
//Função que ordena em ordem crescente um vetor
void insertionSort(int *vet, int n){
	for(int i=1; i<n; i++){
	   	int aux = vet[i];
	   	int j=i-1;
	   	
	   	while(j >= 0 && vet[j] > aux){
			vet[j+1] = vet[j];
			j--;
		}
		vet[j+1] = aux;
	}
}

//Função que ordena em ordem decrescente um vetor
void insertionSortDecrescente(int *vet, int n){
	for(int i=1; i<n; i++){
		int aux = vet[i];
		int j = i-1;
		
		while(j >= 0 && vet[j] < aux){
			vet[j+1] = vet[j];
			j--;
		}
		vet[j+1] = aux;
	}
}

//BubbleSort
void bubbleSortStr(char *str){
	int size = strlen(str);
	char temp;
	
	for(int i=0; i < size-1; i++){
		for(int j=0; j < size-i-1; j++){
			if(str[j] > str[j+1]){
				temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
		}
	}
}

//SelectionSort para ordenar nomes
void selectionSortNames(char nomes[][MAX_TAM], int n){
	for(int i=0; i < n-1; i++){
		int menorIndice = i; //inicialmente começa em 0
		
		//Primeiro for para localizar o indice
		for(int j = i+1; j < n; j++){
			//Compara o tamanho da string atual com a posterior
			if(strlen(nomes[j]) < strlen(nomes[menorIndice])){
				menorIndice = j;
			}
		}
		
		//Realizando a troca
		if(menorIndice != i){
			char temp[MAX_TAM];
			strcpy(temp, nomes[i]);
			strcpy(nomes[i], nomes[menorIndice]);
			strcpy(nomes[menorIndice], temp);
		}
	}
}

int main(void){
	
	printf("\n __________________[ Implementacao ]__________________\n");
	
	//(P3) Criando vetor e verificando se esta ordenado:
	int n;
	printf("\n Digite o tamanho do vetor: "); 
	scanf("%i", &n);
	
	int vet[n]={0}; initVetOrdenado(vet, n);	
	imprimeVet(vet, n);
	isOrdenado(vet, n) ? printf("\n\n ORDENADO!...\n") : printf("\n\n DESORDENADO!...\n");
	
	printf("\n Digite um número para adicionar ao vetor: ");
    int x; scanf("%d", &x);
    
    //Terá que ter uma casa a mais pra acomodar (x)
    int vet2[n+1];
    for(int i=0; i<n; i++){
		vet2[i] = vet[i];
	}
	printf("\n Ordem Crescente: ");
	addNumero(vet2, &n, x);
	imprimeVet(vet2, n);
	
	printf("\n Ordem Decrescente: ");
	//P6) Algorítimo que ordena em ordem decrescente
	insertionSortDecrescente(vet2, n);
	imprimeVet(vet2, n);
	printf("\n -----------------------------------------------------\n");
	
	//P8) Teste vetor fixo
	printf("\n Vetor Fixo (Antes): ");
	int vet3[] = {2, 3, 1, 5, 4, 8, 1, 9, 2, 0};
	
	imprimeVet(vet3, 10);
	printf("\n Vetor Fixo (Depois): ");
	
	insertionSort(vet3, 10);
	imprimeVet(vet3, 10);
	
	printf("\n -----------------------------------------------------\n");
	
	//P11) Colocando as Letras em ordem crescente utilizando bubbleSort
	char str[100];
	
	printf("\n Digite uma string: "); 
	scanf("%99s", str);
    
	bubbleSortStr(str);
	printf("\n String Ordenada: %s", str);
	
	printf("\n -----------------------------------------------------\n");
	
	//P12) Ordenando nomes pelo tamanho, utilizando selectionSort
	printf("\n Digite a quantidade de nomes a adicionar: ");
	scanf("%i", &n);
	
	char nomes[MAX_NOMES][MAX_TAM];
	
	//Limpa o Buffer
	getchar();
	
	//Coleta os nomes
	for(int i=0; i<n; i++){
		printf("\n Nome: ");
		fgets(nomes[i], MAX_TAM, stdin);
	}
	
	selectionSortNames(nomes, n);
	
	printf("\n Nomes ordenados por tamanho:\n");
    for (int i = 0; i < n; i++) {
        printf(" %s\n", nomes[i]);
    }
}



















