#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#define TAM_STRING 201 //201 por conta de nos vetores de caracteres ser necess�rio uma posi��o para o '\0'



//VARI�VEL QUE CONTABILIZA O N�MERO DE COMPARA��ES:
unsigned long int num_comparacoes = 0;


//ESTRUTURA:
typedef struct Item{
	int chave;
	char strings[10][TAM_STRING];
	bool booleano;
	float nuns_reais[4];
} Item;


//FUN��ES AUXILIARES:
void geraValoresAleatorios(long long int n, Item itens[]){
	long long int i, numero;
	int j, num_aux;
	char s_aux[TAM_STRING], aux[10];
	
	srand(time(NULL));
	
	for(i = 0; i < n; i++){ //'for' que percorre todas as posi��es do vetor
		//Criando a chave aleat�ria:
		itens[i].chave = rand() % 1000; //Gerando valores aleat�rios na faixa de 0 a 999
		
		//Criando as 10 cadeias de caracteres aleat�rias:
		strcpy(s_aux, "");
		while(strlen(s_aux) < 199){ //Obtendo 199 caracteres aleat�rios para que possam ser atribu�dos � cada uma das 10 strings de cada item, que se diferenciar�o nestas apenas pelo �ltimo caracter
			numero = rand() + i;
			
			strcpy(aux, ""); //Inicializando 'aux'
			itoa(numero, aux, 10); //Convertendo o n�mero aleat�rio gerado para string
			
			if((strlen(aux) + strlen(s_aux)) <= 199){
				strcat(s_aux, aux);
			} else{
				num_aux = 199 - strlen(s_aux);
				strncat(s_aux, aux, num_aux);
			}
		}
		//Atribuindo a string preenchida com valores aleat�rios �s strings de 'itens[]', por�m, adicionando � elas o �ndice no fina para diferenci�-las. Isso reduz o custo de para cada item ter que gerar 10 novas strings
		for(j = 0; j < 10; j++){ //'for' que percorre as 10 cadeias
			strcpy(itens[i].strings[j], s_aux);
			itoa(j, aux, 10);
			strcat(itens[i].strings[j], aux);
		}
		
		//Criando o valor booleano aleatoriamente
		itens[i].booleano = (bool)(rand() % 2);
		
		//Criando os valores reais aleat�rios
		for(j = 0; j < 4; j++){
			itens[i].nuns_reais[j] = (float)(rand()) / 1000; //Gera valores aleat�rios reais com at� 3 casas decimais
		}
	}
}

void imprimeItens(long long int n, Item itens[]){
	long long int i, j;
	
	for(i = 0; i < n; i++){
		printf("  %d", itens[i].chave);
		/*printf("\n- Chave: %d\n", itens[i].chave);
		for(j = 0; j < 10; j++){
			printf(". String %d: %s\n", j + 1, itens[i].strings[j]);
		}
		if(itens[i].booleano){
			printf(". Valor booleano: %s\n", "True");
		} else{
			printf(". Valor booleano: %s\n", "False");
		}
		for(j = 0; j < 4; j++){
			printf(". Valor real %d: %f\n", j + 1, itens[i].nuns_reais[j]);
		}*/
	}
}


//QuickSort

int particiona(Item itens[], long long int inicio, long long int fim){
	long long int esq, dir;
	Item pivo, aux;
	
	esq = inicio;
	dir = fim;
	pivo = itens[inicio];
	
	while(esq < dir){
		do{
			if(esq <= fim && itens[esq].chave <= pivo.chave){
				esq ++;
			}
			num_comparacoes ++;
		} while(esq <= fim && itens[esq].chave <= pivo.chave);
		do{
			if(dir >= inicio && itens[dir].chave > pivo.chave){
				dir --;
			}
			num_comparacoes ++;
		} while(dir >= inicio && itens[dir].chave > pivo.chave);
		if(esq < dir){
			aux = itens[esq];
			itens[esq] = itens[dir];
			itens[dir] = aux;
		}
	}
	
	itens[inicio] = itens[dir];
	itens[dir] = pivo;
	
	return dir;
}

void quickSort(Item itens[], long long int inicio, long long int fim){
	long long int pivo;
	
	if(fim > inicio){
		pivo = particiona(itens, inicio, fim);
		quickSort(itens, inicio, pivo - 1);
		quickSort(itens, pivo + 1, fim);
	}
}



int main(int argc, char *argv[]){
	long long int n;
	int num_conjunto, i;
	char *endptr, nome_arquivo[15];
	Item *itens;
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
	
	
	//DECLARANDO O VETOR DE STRUCTS DIN�MICAMENTE:
	itens = malloc(n * sizeof(Item));
	if(!itens){
		printf("\nERRO na alocacao de memoria para a criacao do vetor!");
		exit(1); //Encerra o programa
	}
	
	
	//PREENCHENDO O VETOR COM VALORES ALEAT�RIOS:
	geraValoresAleatorios(n, itens);
	
	
	//ORDENANDO OS VALORES:
	inicio = clock(); //Registrando a hora que estava marcando no in�cio da ordena��o
	quickSort(itens, 0, n - 1);
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
		fprintf(f, "\n\n\n-------------------------------------------------------------\n\n");
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
