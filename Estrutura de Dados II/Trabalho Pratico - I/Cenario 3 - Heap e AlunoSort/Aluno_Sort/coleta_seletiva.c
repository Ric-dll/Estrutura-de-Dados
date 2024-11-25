#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

//Variavel especifica para tempo do clock1
clock_t InicioSec, FimSec;
unsigned long long int tempo1;

//Funcao que atribui valores aleatorios a um vetor de tamanho t
void FillAleatory(int *vet, long long int n){
	srand(time(NULL));
	long long int i;
	
	for(i=0; i<n ; i++){
		vet[i] = rand() % 1000;
	}
}

//Funcao que gera o pior caso de tamanho n
void gerarPiorCaso(int *vetor, int n){
	int i;
	for(i = 0; i<n; i++){
		vetor[i] = n-i;
	}
}

//Função que imprime o vetor
void imprimir(int *vet, int size){
	long long int i;
	
	if(size == 0){
		printf("!Vetor Vazio!...");
		return;
	}
	
	printf("\nVetor = [ ");
	for(i=0; i<size; i++){
		printf("%d, ", vet[i]);
	}
	printf(" ]\n");
}

//Funcao que realiza a troca
void troca(int *x, int *y){
	int temp = *x;
	*x = *y;
	*y = temp;
}

//Funcao que particiona o vetor
int particionarVetor(int *vet, long long int inicio, long long int fim){
	//Pega a posicao media do vetor
	int pivot = vet[(inicio+fim)/2];
	
	while(inicio <= fim){
	
		while(vet[inicio] < pivot) inicio++;
		while(vet[fim] > pivot) fim--;

		if(inicio <= fim){
			troca(&vet[inicio], &vet[fim]);
			inicio++;
			fim--;
		}
	}
	return inicio;
}

//Funcao que realiza o quick de maneira recursiva
void quickSort(int *vet, long long int inicio, long long int fim){
	if(inicio < fim){
		//Divide o vetor
		int indice = particionarVetor(vet, inicio, fim);
		
		quickSort(vet, inicio, indice-1);	//Ordena a parte esquerda
		quickSort(vet, indice, fim);			//Ordena a parte direita
	}
}

//Funcao que realiza a separacao dos valores baseados no sistema de unidades
void recicleSort(int *vetor, long long int tamanho){

	//Vetores para unidades(vet1), dezenas(vet2) e centenas(vet3)
	int *vet1 = (int *)malloc(tamanho * sizeof(int));
	int *vet2 = (int *)malloc(tamanho * sizeof(int));
	int *vet3 = (int *)malloc(tamanho * sizeof(int));
	
	//Inicializando o tamanho iniciais dos vetores
	size_t tam1=0, tam2=0, tam3=0;
	
	//Verificacao inicial
	if(!vet1 || !vet2 || !vet3){
		printf("\nErro na Alocacao de Memoria!...");
		return;
	}
	
	long long int i;
	
	//Agora realizando a coleta seletiva
	for(i = 0; i < tamanho; i++){
		
		//percorre todo vetor pegando todos os numeros e realizando os calculos
		int numero = vetor[i];
		
		if (numero >= 0 && numero <= 9) {
            vet1[tam1++] = numero;  // Unidades
        }
        else if (numero >= 10 && numero <= 99) {
            vet2[tam2++] = numero;  // Dezenas
        }
        else if (numero >= 100 && numero <= 999) {
            vet3[tam3++] = numero;  // Centenas
        }
	}
	
	//Agora ordenando com o quickSort, começa pelo 0 de cada vetor até k-1
	if(tam1 > 1) quickSort(vet1, 0, tam1-1);
	if(tam2 > 1) quickSort(vet2, 0, tam2-1);
	if(tam3 > 1) quickSort(vet3, 0, tam3-1);
	
	/* Exibindo os vetores ordenados
    printf("Vet1 (Unidades): ");
	imprimir(vet1, tam1);

    printf("Vet2 (Dezenas): ");
    imprimir(vet2, tam2);

    printf("Vet3 (Centenas): ");
    imprimir(vet3, tam3);
    
    printf("\n");
	*/
	
	//Libera a Memoria alocada
    free(vet1);
    free(vet2);
    free(vet3);
}

//Funcao principal
int main(int argc, char *argv[]){
	
	if(argc != 3){ 
        printf("Espera-se: %s [tamanho do vetor] e [arquivo de saída]\n", argv[0]);
        exit(1);
    }

	//Coleta a entrada por argumento da posicao [1]
	int tamanho = atoll(argv[1]);
	
	//Suposto arquivo para salvar os dados
	const char *bob_esponja = argv[2];
	
	//Criando os vetores de maneira dinamica 
	int *vetor = (int*)malloc(tamanho * sizeof(int)); 
	
	//Preenchendo com valores aleatorios ou pior caso
	
	//gerarPiorCaso(vetor, n);
	//gerarPiorCaso(vetor2, n);
	FillAleatory(vetor, tamanho); 
	//imprimir(vetor, tamanho);
	
	//Medindo o tempo de execução da ordenação
	InicioSec = clock();
	recicleSort(vetor, tamanho);
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
	//fprintf(arquivo, "\n\tDados - Diagnostico do Aluno Sort \n\n");
	fprintf(arquivo, "\nTamanho do vetor: %i\n", tamanho);
	fprintf(arquivo, "\nPara [ tamanho = %d ], Tempo: %llu ms\n", tamanho, tempo1);
	fprintf(arquivo, "\n--------------------------------------------------------------------");
	
	fclose(arquivo);
	
	// Libera a memória alocada 
    free(vetor);
    
    printf("Resultados gravados no arquivo '%s'.\n", bob_esponja);

}

