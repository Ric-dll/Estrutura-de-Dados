#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/* Funcao de busca binaria recursiva
 * 
 * Calcula o meio e verifica se a posicao central adquirida é menor ou maior
 * ao elemento que desejamos, realizando o calculo do "meio" a cada chamada. 
 * 
 * Desconsidera o restante do vetor relativo a posicao central a esquerda ou 
 * a direita ate encontrar o elemento desejado.
 */
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
void imprimir(int *vet, int size){
	printf("\nVetor = [ ");
	for(int i=0; i<size; i++){
		printf("\n%i, ", vet[i]);
	}
	printf(" ]\n");
}


int main(void){
	
//Teste 2 - Vetor Fixo com busca binaria
	int chave, v2[] = {1, 2, 4, 6, 7, 8, 10, 10, 12, 15, 17, 19, 20, 21};
	
	int sizeV2 = sizeof(v2)/sizeof(v2[0]);
	printf("\n_________[ Teste 2 ]_________\n");
	printf("\nInforme a chave de Busca: "); 
	scanf("%i", &chave);
		
	if(SearchBin(v2, 0, sizeV2-1, chave) != -1){
		printf("Key: %i", chave);
	}else{
		printf("\nKey nao encontrada!...");
	}
}
