#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Algoritimo de busca sequencial
int SearchSeq(int vet[], int key){
	int i=0;
	while(vet[i] != key){
		if(key){
			return 1;
		}
		i++;
	}
	return 0;
}

int main(void){
	
//Teste 1 - Vetor Fixo com busca sequencial
	int chave, v1[] = {10, 12, 11, 6, 7, 8, 3, 4, 2, 1};
	
	printf("\n_________[ Teste 1 ]_________\n");
	printf("\nInforme a chave de Busca: "); 
	scanf("%i", &chave);
	
	if(SearchSeq(v1, chave) == 0){
		printf("Key: %i", chave);
	}else{
		printf("\nKey nao encontrada!...");
	}
		
}
