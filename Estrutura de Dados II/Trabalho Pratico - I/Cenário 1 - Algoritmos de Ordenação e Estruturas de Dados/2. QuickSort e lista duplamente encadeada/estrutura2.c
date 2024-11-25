#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>



//VARIÁVEL QUE CONTABILIZA O NÚMERO DE COMPARAÇÕES:
unsigned long int num_comparacoes = 0;


//ESTRUTURA DA LISTA DUPLAMENTE ENCADEADA:
typedef struct TipoItem{
	int numero;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula{
	long long int Indice;
	TipoItem Item;
	TipoApontador Prox;
	TipoApontador Ant;
} TipoCelula;

typedef struct{
	TipoApontador Primeiro, Ultimo;
} TipoLista;



//FUNÇÕES BÁSICAS PARA MANIPULAÇÃO DA LISTA DUPLAMENTE ENCADEADA:
int ListaVazia(TipoLista Lista){
	return (Lista.Primeiro == Lista.Ultimo);
}

void FLVazia(TipoLista *Lista){
	Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
	Lista->Ultimo = Lista->Primeiro;
	Lista->Primeiro->Ant = NULL;
	Lista->Primeiro->Prox = NULL;
	Lista->Primeiro->Indice = -1;
}

void Insere(TipoItem Item, TipoLista *Lista){
	Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
	Lista->Ultimo->Prox->Ant = Lista->Ultimo;
	Lista->Ultimo = Lista->Ultimo->Prox;
	Lista->Ultimo->Item = Item;
	Lista->Ultimo->Prox = NULL;
	Lista->Ultimo->Indice = Lista->Ultimo->Ant->Indice + 1;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item){
	TipoApontador q;
	if(ListaVazia(*Lista) || p == NULL || p->Prox == NULL){
		printf("\n\nErro: Lista esta vazia ou a posicao informada nao existe!\n\n");
		return ;
	}
	
	q = p->Prox;
	*Item = q->Item;
	p->Prox = q->Prox;
	q->Prox->Ant = p;
	if(p->Prox == NULL){
		Lista->Ultimo = p;
	}
	
	free(q);
}

void Imprime(TipoLista Lista){
	TipoApontador Aux;
	
	Aux = Lista.Primeiro->Prox;
	while(Aux != NULL){
		printf("  %d", Aux->Item.numero);
		
		Aux = Aux->Prox;
	}
}



//FUNÇÕES PARA SOLUÇÃO DO PROBLEMA:

void geraValoresAleatorios(long long int n, TipoLista *Lista){
	long long int i;
	TipoItem Item_aux;
	TipoApontador Aux;
	
	srand(time(NULL));
	
	for(i = 0; i < n; i++){
		Item_aux.numero = rand() % 1000; //Gerando valores aleatórios na faixa de 0 a 999
		
		Insere(Item_aux, Lista);
	}
}


//QuickSort

int particiona(TipoLista lista, long long int inicio, long long int fim, TipoApontador celula_inicio, TipoApontador celula_fim, TipoApontador *endereco_pivo){
	long long int esq, dir, pivo, aux;
	TipoApontador celula_esq, celula_dir;
	//TipoApontador esq_aux = NULL, dir_aux = NULL;
	
	esq = inicio;
	dir = fim;
	celula_esq = celula_inicio;
	celula_dir = celula_fim;
	pivo = celula_inicio->Item.numero;
	
	while(esq < dir){
		do{
			if(esq <= fim && celula_esq->Item.numero <= pivo){
				esq ++;
				celula_esq = celula_esq->Prox;
			}
			num_comparacoes ++;
		} while(esq <= fim && celula_esq->Item.numero <= pivo);
		do{
			if(dir >= inicio && celula_dir->Item.numero > pivo){
				dir --;
				celula_dir = celula_dir->Ant;
			}
			num_comparacoes ++;
		} while(dir >= inicio && celula_dir->Item.numero > pivo);
		if(esq < dir){
			aux = celula_esq->Item.numero;
			celula_esq->Item.numero = celula_dir->Item.numero;
			celula_dir->Item.numero = aux;
		}
	}
	
	celula_inicio->Item.numero = celula_dir->Item.numero;
	celula_dir->Item.numero = pivo;
	*endereco_pivo = celula_dir;
	
	return dir;
}

void quickSort(TipoLista lista, long long int inicio, long long int fim, TipoApontador celula_inicio, TipoApontador celula_fim){
	long long int pivo;
	TipoApontador endereco_pivo;
	
	if(fim > inicio){
		pivo = particiona(lista, inicio, fim, celula_inicio, celula_fim, &endereco_pivo);
		quickSort(lista, inicio, pivo - 1, celula_inicio, endereco_pivo->Ant);
		quickSort(lista, pivo + 1, fim, endereco_pivo->Prox, celula_fim);
	}
}



int main(int argc, char *argv[]){
	long long int n;
	int num_conjunto, i;
	char *endptr, nome_arquivo[15];
	TipoLista lista;
	clock_t inicio, fim;
	unsigned long int tempo = 0;
	
	if(argc < 4){
		printf("ERRO - Informe o tamanho do vetor, o arquivo onde serao impressos os resultados e o respectivo conjundo de dados (1o, 2o ...)!\n");
		exit(1);
	}
	
	
	//RECEBENDO O TAMANHO DO CONJUNTO DE DADOS ATRAVÉS DO PARÂMETRO '*argv[1]':
	n = strtoll(argv[1], &endptr, 10);
	
	//RECEBENDO O NOME E A EXTENSÃO DO ARQUIVO ATRAVÉS DO PARÂMETRO '*argv[2]':
	strcpy(nome_arquivo, argv[2]);
	
	//RECEBENDO O RESPECTIVO NÚMERO DO CONJUNTO CRIADO:
	num_conjunto = atoi(argv[3]);
	
	
	//CRIANDO A LISTA DUPLAMENTE ENCADEADA (fazendo-a começar vazia):
	FLVazia(&lista);
	
	
	//PREENCHENDO A LISTA COM VALORES ALEATÓRIOS:
	geraValoresAleatorios(n, &lista);
	
	
	//ORDENANDO OS VALORES:
	inicio = clock(); //Registrando a hora que estava marcando no início da ordenação
	quickSort(lista, lista.Primeiro->Prox->Indice, lista.Ultimo->Indice, lista.Primeiro->Prox, lista.Ultimo);
	fim = clock(); //Registrando a hora que estava marcando no fim da ordenação
	
	
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
