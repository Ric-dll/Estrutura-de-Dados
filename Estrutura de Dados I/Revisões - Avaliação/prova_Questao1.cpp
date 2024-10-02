#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INICIO_ARRANJO 1 //Indica o início da lista
#define TAM_MAX 20 //Tamanho maximo da lista

//Definido um novo tipo de dado chamado TipoApontador e
//é usado para representar ponteiros para elementos na lista
typedef int TipoApontador;

//Definindo a Estrutura de um Produto, definindo como 0 e vazio para facilitar comparações futuras
struct TipoItem{
	int cod;
	char descricao[100];
	int ano;
	float valor;
};

//Definindo o tipo da lista
struct TipoLista{
	TipoItem itens[TAM_MAX];
	//Esses apontadores são usados para indicar o primeiro e o último elemento da lista
	TipoApontador primeiro;
	TipoApontador ultimo;
};

//Função pra inicializar uma lista vazia
void initVoidList(TipoLista *lista){
	//lista aponta para o "primeiro" apontador, receber o valor definido em INICIO_ARRANJO
	lista -> primeiro = INICIO_ARRANJO;
	
	//lista aponta também para o "ultimo" apontador, que recebe lista apontada para primeiro
	//Como a lista está vazia, o ultimo também aponta para o mesmo lugar que o primeiro
	lista -> ultimo = lista -> primeiro;
}

//Função que verifica se a lista está vazia (1)-Sim (0)-Nao
int isVoid(TipoLista lista){
	return (lista.primeiro == lista.ultimo);
}

//Função que insere informações ao item da lista
void insert(TipoItem item, TipoLista *lista){
	//Se a lista que aponta para a ultima posicao estiver cheia...
	if(lista -> ultimo >= TAM_MAX){
		printf("\nLista cheia!...");
	}else{
		//Caso contrario...

		//lista aponta para itens na posição (lista apontando para ultimo - 1), que recebera um novo item
		lista -> itens[lista->ultimo-1] = item;

		//lista aponta para ultimo que incrementa 1
		lista -> ultimo++;
	}
}

//Função que remove um item da lista, recebe 3 parâmetros
void remove(TipoApontador p, TipoLista *lista, TipoItem *itemParametro){

	//Se a lista estiver vazia, ou, se a posição "p" fornecida é válida
	//Se usar apenas lista ao invés de *lista, estará passando o próprio ponteiro, não o valor apontado por ele. 
	if(isVoid(*lista) || p >= lista -> ultimo){
		printf("\nErro: Posicao nao existe");
		return; //Encerra a função aqui
	}

	//Item recebe lista que está localizada na posição anterior da posição p passada para exclusão
	//Quando  usa-se *item está acessando o valor apontado pelo ponteiro
	*itemParametro = lista -> itens[p-1]; //(p-1) pois o array começa em 0...
	//Decrementa um no piscador
	lista -> ultimo--;

	//Começa o loop de ordenação
	//i recebe o valor passado como parâmetro e através dele começa a percorrer até chegar em ultimo
	for(int i=p; i<lista->ultimo; i++){
		//lista aponta para a posição anterior da atual passada como parâmetro e recebe
		//o item que está sendo apontado por lista na posição i atual
		lista -> itens[i-1] = lista -> itens[i];
	}
}

//Função que imprime os elementos da lista
void impress(TipoLista lista){
	for(int i=0; i<lista.ultimo; i++){
		printf("\n_____________[ Item %i ]____________", i+1);
		printf("\nDescricao: %s", lista.itens[i].descricao);
		printf("\nCodigo: [ %i ]", lista.itens[i].cod);
		printf("\nAno: %i ", lista.itens[i].ano);
		printf("\nValor: R$%.2f", lista.itens[i].valor);
		printf("\n___________________________________\n");
	}
}

float somaVeiculosPorAno(TipoLista lista, int anoParametro){
	float soma = 0;
	
	//For que inicia percorrendo a partir do primeiro em lista, e gira até ultimo em lista
	for(int i = lista.primeiro-1; i<lista.ultimo-1; i++){
		if(lista.itens[i].ano == anoParametro){
			soma += lista.itens[i].valor;
		}
	}
	return soma;
}

//Testes
int main(void){
	
	//Criando lista
	struct TipoLista lista1;
	struct TipoItem item;
	
	//Inicializando a lista com campos vazios
	initVoidList(&lista1);
	
	//Inserindo dados
	item.cod = 1;
	item.ano = 2004;
	item.valor = 14.000;
	strcpy(item.descricao, "Corsa");
	insert(item, &lista1);
	
	//Inserindo dados
	item.cod = 1;
	item.ano = 2004;
	item.valor = 14.000;
	strcpy(item.descricao, "Corsa");
	insert(item, &lista1);
	
	//Inserindo dados
	item.cod = 1;
	item.ano = 2004;
	item.valor = 14.000;
	strcpy(item.descricao, "Corsa");
	insert(item, &lista1);
	
	printf("\nTeste, soma total dos valores de tal ano: %.3f ", somaVeiculosPorAno(lista1, 2004));
}
