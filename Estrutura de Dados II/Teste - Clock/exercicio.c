//Exercicio proposto

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Escopo de variaveis
int i, j, soma = 0;

//Variavel especifica para tempo de clock
clock_t inicio, fim;
unsigned long int tempo;

//Declaração de funções
void algoritimo1(int n){
	for(i=0 ; i<=n ; i++){
			soma+=i;
		}
}

void algoritimo2(int n){
	for(i=0; i<n; i++){
		for(j=0; j<=i; j++){
			soma+=1;
		}
	}
}


void algoritimo3(int n){
	soma = n * (n+1)/2;
}


int main(int argc, char *argv[]){
	
	inicio = clock();
	
	printf("\nargc: %i", argc);
	
	int n = atoi(argv[2]);
	
	if(*argv[1] == '1'){
		algoritimo1(n);
	}else 
		if(*argv[1] == '2'){
			algoritimo2(n);
	}else
		if(*argv[1] == '3'){
			algoritimo3(n);
	}else{
		printf("\nParametro Invalido!...");
	}
	
	fim = clock();
	
	tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
	printf("\ntempo: %lu milissegundos\n",tempo);

	return 0;
}
