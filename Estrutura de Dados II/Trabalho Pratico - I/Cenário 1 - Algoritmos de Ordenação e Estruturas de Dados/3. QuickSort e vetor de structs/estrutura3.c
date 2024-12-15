#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#define TAM_STRING 201 //201 por conta de nos vetores de caracteres ser necessário uma posição para o '\0'



//VARIÁVEL QUE CONTABILIZA O NÚMERO DE COMPARAÇÕES:
unsigned long int num_comparacoes = 0;


//ESTRUTURA:
typedef struct Item{
	int chave;
	char strings[10][TAM_STRING];
	bool booleano;
	float nuns_reais[4];
} Item;


//FUNÇÕES AUXILIARES:
void geraValoresAleatorios(long long int n, Item itens[]){
	long long int i, numero;
	int j, num_aux;
	char s_aux[TAM_STRING], aux[10];
	
	srand(time(NULL));
	
	for(i = 0; i < n; i++){ //'for' que percorre todas as posições do vetor
		//Criando a chave aleatória:
		itens[i].chave = rand() % 1000; //Gerando valores aleatórios na faixa de 0 a 999
		
		//Criando as 10 cadeias de caracteres aleatórias:
		strcpy(s_aux, "");
		while(strlen(s_aux) < 199){ //Obtendo 199 caracteres aleatórios para que possam ser atribuídos à cada uma das 10 strings de cada item, que se diferenciarão nestas apenas pelo último caracter
			numero = rand() + i;
			
			strcpy(aux, ""); //Inicializando 'aux'
			itoa(numero, aux, 10); //Convertendo o número aleatório gerado para string
			
			if((strlen(aux) + strlen(s_aux)) <= 199){
				strcat(s_aux, aux);
			} else{
				num_aux = 199 - strlen(s_aux);
				strncat(s_aux, aux, num_aux);
			}
		}
		//Atribuindo a string preenchida com valores aleatórios às strings de 'itens[]', porém, adicionando à elas o índice no fina para diferenciá-las. Isso reduz o custo de para cada item ter que gerar 10 novas strings
		for(j = 0; j < 10; j++){ //'for' que percorre as 10 cadeias
			strcpy(itens[i].strings[j], s_aux);
			itoa(j, aux, 10);
			strcat(itens[i].strings[j], aux);
		}
		
		//Criando o valor booleano aleatoriamente
		itens[i].booleano = (bool)(rand() % 2);
		
		//Criando os valores reais aleatórios
		for(j = 0; j < 4; j++){
			itens[i].nuns_reais[j] = (float)(rand()) / 1000; //Gera valores aleatórios reais com até 3 casas decimais
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
	
	
	//VERIFICANDO SE TODOS OS DADOS FORAM INFORMADOS CORRETAMENTE ATRAVÉS DO Prompt:
	if(argc < 4){
		printf("ERRO - Informe o tamanho do vetor, o arquivo onde serao impressos os resultados e o respectivo conjundo de dados (1o, 2o ...)!\n");
		exit(1); //Encerra o programa
	}
	
	
	//RECEBENDO O TAMANHO DO CONJUNTO DE DADOS ATRAVÉS DO PARÂMETRO '*argv[1]':
	n = strtoll(argv[1], &endptr, 10);
	
	//RECEBENDO O NOME E A EXTENSÃO DO ARQUIVO ATRAVÉS DO PARÂMETRO '*argv[2]':
	strcpy(nome_arquivo, argv[2]);
	
	//RECEBENDO O RESPECTIVO NÚMERO DO CONJUNTO CRIADO:
	num_conjunto = atoi(argv[3]);
	
	
	//DECLARANDO O VETOR DE STRUCTS DINÂMICAMENTE:
	itens = malloc(n * sizeof(Item));
	if(!itens){
		printf("\nERRO na alocacao de memoria para a criacao do vetor!");
		exit(1); //Encerra o programa
	}
	
	
	//PREENCHENDO O VETOR COM VALORES ALEATÓRIOS:
	geraValoresAleatorios(n, itens);
	
	
	//ORDENANDO OS VALORES:
	inicio = clock(); //Registrando a hora que estava marcando no início da ordenação
	quickSort(itens, 0, n - 1);
	fim = clock(); //Registrando a hora que estava marcando no final da ordenação
	
	
	//CALCULANDO O TEMPO TOTAL GASTO:
	tempo = (fim - inicio) * 1000 / CLOCKS_PER_SEC;
	
	
	//CRIANDO UM APONTADOR PARA CONTROLAR O ARQUIVO E JÁ O ABRINDO:
	FILE *f;
	f = fopen(nome_arquivo, "a");
	if(f == NULL){
		printf("\nERRO - Criacao e/ou abertura mal sucedida do arquivo para escrita!\n");
		exit(1);
	}
	
	
	//ESCREVENDO O NÚMERO DE COMPARAÇÕES E O TEMPO TOTAL GASTO NA ORDENAÇÃO NO ARQUIVO:
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
