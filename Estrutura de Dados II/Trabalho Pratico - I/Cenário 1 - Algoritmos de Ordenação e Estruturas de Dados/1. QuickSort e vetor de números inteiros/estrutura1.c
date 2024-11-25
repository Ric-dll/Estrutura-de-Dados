#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



//VARI�VEL QUE CONTABILIZA O N�MERO DE COMPARA��ES:
unsigned long int num_comparacoes = 0;


//FUN��ES AUXILIARES:
void geraValoresAleatorios(long long int n, int vetor[]){
	long long int i;
	srand(time(NULL));
	
	for(i = 0; i < n; i++){
		vetor[i] = rand() % 1000; //Gerando valores aleat�rios na faixa de 0 a 999
	}
}


//QuickSort

int particiona(int vetor[], long long int inicio, long long int fim){
	long long int esq, dir, pivo, aux;
	
	esq = inicio;
	dir = fim;
	pivo = vetor[inicio];
	
	while(esq < dir){
		do{
			if(esq <= fim && vetor[esq] <= pivo){
				esq ++;
			}
			num_comparacoes ++;
		} while(esq <= fim && vetor[esq] <= pivo);
		do{
			if(dir >= inicio && vetor[dir] > pivo){
				dir --;
			}
			num_comparacoes ++;
		} while(dir >= inicio && vetor[dir] > pivo);
		if(esq < dir){
			aux = vetor[esq];
			vetor[esq] = vetor[dir];
			vetor[dir] = aux;
		}
	}
	
	vetor[inicio] = vetor[dir];
	vetor[dir] = pivo;
	
	return dir;
}

void quickSort(int vetor[], long long int inicio, long long int fim){
	long long int pivo;
	
	if(fim > inicio){
		pivo = particiona(vetor, inicio, fim);
		quickSort(vetor, inicio, pivo - 1);
		quickSort(vetor, pivo + 1, fim);
	}
}



int main(int argc, char *argv[]){
	long long int n;
	int *vetor, num_conjunto;
	char *endptr, nome_arquivo[15];
	clock_t inicio, fim;
	unsigned long int tempo = 0;
	
	
	//VERIFICANDO SE TODOS OS DADOS FORAM INFORMADOS CORRETAMENTE ATRAV�S DO Prompt:
	if(argc < 4){
		printf("ERRO - Informe o tamanho do vetor, o arquivo onde serao impressos os resultados e o respectivo conjundo de dados (1o, 2o ...)!\n");
		exit(1); //Encerra o programa
	}
	
	
	//RECEBENDO O TAMANHO DO CONJUNTO DE DADOS ATRAV�S DO PAR�METRO '*argv[1]':
	n = strtoll(argv[1], &endptr, 10);
	
	//RECEBENDO O NOME E A EXTENS�O DO ARQUIVO ATRAV�S DO PAR�METRO '*argv[2]':
	strcpy(nome_arquivo, argv[2]);
	
	//RECEBENDO O RESPECTIVO N�MERO DO CONJUNTO CRIADO:
	num_conjunto = atoi(argv[3]);
	
	
	//DECLARANDO O VETOR DIN�MICAMENTE:
	vetor = (int *)calloc(n, sizeof(int));
	if(!vetor){ //Caso n�o tenha dado certo e 'calloc' retornou um ponteiro nulo (NULL)
		printf("\nERRO na alocacao de memoria para a criacao do vetor!");
		exit(1); //Encerra o programa
	}
	
	
	//PREENCHENDO O VETOR COM VALORES ALEAT�RIOS:
	geraValoresAleatorios(n, vetor);
	
	
	//ORDENANDO OS VALORES:
	inicio = clock(); //Registrando a hora que estava marcando no in�cio da ordena��o
	quickSort(vetor, 0, n - 1);
	fim = clock(); //Registrando a hora que estava marcando no final da ordena��o
	
	
	//CALCULANDO O TEMPO TOTAL GASTO:
	tempo = (fim - inicio) * 1000 / CLOCKS_PER_SEC;
	
	
	//CRIANDO UM APONTADOR PARA CONTROLAR O ARQUIVO E J� O ABRINDO:
	FILE *f;
	f = fopen(nome_arquivo, "a");
	if(f == NULL){
		printf("\nERRO - Criacao e/ou abertura mal sucedida do arquivo para escrita!\n");
		exit(1);
	}
	
	
	//ESCREVENDO O N�MERO DE COMPARA��ES E O TEMPO TOTAL GASTO NA ORDENA��O NO ARQUIVO:
	if(num_conjunto == 1 && n > 1000){
		fprintf(f, "\n\n\n--------------------------------------------------------------------------------------\n\n");
	} else if(num_conjunto > 1){
		fprintf(f, "\n\n");
	}
	fprintf(f, "- CONJUNTO %d PARA %lld VALORES", num_conjunto, n);
	fprintf(f, "\n. Numero de comparacoes de chaves: %lu", num_comparacoes);
	fprintf(f, "\n. Tempo total gasto na ordenacao: %lu", tempo);
	printf("\nResultados registrados no arquivo!\n");
	
	
	//FECHANDO O ARQUIVO:
	fclose(f);
	
	
	return 0;
}
