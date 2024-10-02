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
	char descricao[100] = "";
	int quantidade = 0;
	float valor = 0;
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
		printf("\nQuantidade: [ %i ] itens", lista.itens[i].quantidade);
		printf("\nValor: R$%.2f", lista.itens[i].valor);
		printf("\n___________________________________\n");
	}
}

//Função que soma o valor de todos os itens dentro de uma só lista
float calcSomaitensLista(TipoLista lista){
	float total=0;
	//Percorre toda a lista até ultimo -1, para desconsiderar o associado a ultimo
	for(int i=0; i<lista.ultimo; i++){
		//Soma e atualiza o valor total com o valor de todos os itens
		total+=lista.itens[i].valor;
	}
	return total;
}

//Função que retorna a struct que contém o produto mais caro
float itemMaisCaro(TipoLista lista){
	//Variável maior com valor inicial 0
	float maior=0;

	//Inicia o loop de maneira padrão para comparar valores 
	for(int i=0; i<lista.ultimo-1; i++){

		//Verifica se o valor do item atual é maior que o da variável maior
		if(lista.itens[i].valor > maior){ //Se sim
			maior = lista.itens[i].valor;
		}
	}
	return maior;
}

//Função que complementa a anterior para imprimir a struct com maior valor
void imprimirItemDeMaiorValor(TipoLista lista){
	for(int i=0; i<lista.ultimo; i++){
		//Compara o valor atual do item na lista com a função anterior
		if(lista.itens[i].valor == itemMaisCaro(lista)){
			printf("\nItem [%i], ", i+1);
			printf("Descricao: %s", lista.itens[i].descricao);
			printf("\nQuantidade: %i - ", lista.itens[i].quantidade);
			printf("Valor: R$%.2f", lista.itens[i].valor);
		
		}
	}
}

//Função que retorna quantos produtos com a descrição informada estao cadastrados na lista
int searchProdutoDescricao(TipoLista lista, const char *searchDescricao){
	int qtdProdutos;
	//Loop que começa a percorrer a lista...
	for(int i=0; i<lista.ultimo-1; i++){
		//Se encontrar uma lista no atual loop, que seja igual a searchDescricao...
		if(strcmp(lista.itens[i].descricao, searchDescricao) == 0){
			qtdProdutos = lista.itens[i].quantidade;
		}
	}
	return qtdProdutos;
}

//Função que recebe uma lista e troca dois produtos(itens) de posição (posições recebidas como parâmetro)
void trocarPosicao(TipoLista *lista, int p1, int p2){
	struct TipoItem auxiliar;

	// p1 -> auxiliar
	// p2 -> p1
	// p2 -> auxiliar

	//(strcpy) Pra onde vai, d'onde vem 

	//Copiando os dados do item na posição p1 para auxiliar
	strcpy(auxiliar.descricao, lista->itens[p1-1].descricao);
	auxiliar.quantidade = lista->itens[p1-1].quantidade;
	auxiliar.valor = lista->itens[p1-1].valor;
	
	//Copiando os dados do item na posição p2 para a posição p1
	strcpy(lista->itens[p1-1].descricao, lista->itens[p2-1].descricao);
	lista->itens[p1-1].quantidade = lista->itens[p2-1].quantidade;
	lista->itens[p1-1].valor = lista->itens[p2-1].valor;
	
	//Copiando os dados de auxiliar para a posição p2
	strcpy(lista->itens[p2-1].descricao, auxiliar.descricao);
	lista->itens[p2-1].quantidade = auxiliar.quantidade;
	lista->itens[p2-1].valor = auxiliar.valor;
	
}

//Função que Recebe uma lista e busca por uma descrição, retornando -1 para não achado e a posicao se achado
int searchInListDescricao(TipoLista lista, const char *searchDescricao){
	//Loop que começa a percorrer a lista...
	for(int i=0; i<lista.ultimo; i++){
		//Se encontrar uma lista no atual loop, que seja igual a searchDescricao...
		if(strcmp(lista.itens[i].descricao, searchDescricao) == 0){
			return i+1; //i+i pois começa em 0
		}
	}
	return -1;
}

//Função que recebe duas listas e verifica sua igualdade de itens
int verIgualdadeListas(TipoLista lista1, TipoLista lista2){
	for(int i=0; i<lista1.ultimo; i++){
		//Primeira condição pra verificar por tamanho
		if(lista1.ultimo != lista2.ultimo){
			return 0;
		}

		//Se possuir o mesmo tamanho, entra no loop
		for(int i=0; i<lista1.ultimo; i++){
			// Compara cada campo do registro atual
			if(strcmp(lista1.itens[i].descricao, lista2.itens[i].descricao) != 0 || lista1.itens[i].quantidade != lista2.itens[i].quantidade || lista1.itens[i].valor != lista2.itens[i].valor) {
				return 0; // Se algum campo não for igual, retorna 0 
			}
		}
	}
	// Se todas as comparações forem iguais até aqui, as listas são iguais
    return 1;
}

//Função que verifica quantos itens possui na lista
int qtdItensLista(TipoLista *lista){
	int cont=0;
	for(int i=0; i<lista->ultimo; i++){
		if((strcmp(lista->itens[i].descricao, "") != 0) && (lista->itens[i].quantidade != 0) && (lista->itens[i].valor != 0)){
			cont++;
		}
	}
	return cont;
}

//Função que verifica qual das listas passadas como parâmetro é maior, dada a função anterior
int listaComMaisItens(TipoLista lista1, TipoLista lista2){
	int qtdLista1 = qtdItensLista(&lista1);
	int qtdLista2 = qtdItensLista(&lista2);
	
	if(qtdLista1 > qtdLista2){
		return 1;
	}
	if(qtdLista2 > qtdLista1){
		return 2;
	}
	return 0;
}

//Função que calcula qual lista possui maior valor perante a soma de todos seus itens
int listaComMaiorValor(TipoLista lista1, TipoLista lista2){

	if(calcSomaitensLista(lista1) > calcSomaitensLista(lista2)){
		return 1;
	}
	if(calcSomaitensLista(lista2) > calcSomaitensLista(lista1)){
		return 2;
	}
	return 0;
}

//Função que retorna os itens presentes de forma igualitária em ambas as listas
void itensEmAmbasListas(TipoLista *lista1, TipoLista *lista2){
	for(int i=0; i<lista1->ultimo-1; i++){
		for(int j=0; j<lista2->ultimo-1; j++){
			//Se a comparação de cada item do for 1 com cada item do for 2 for igual, imprimirá os itens 
			if((strcmp(lista1->itens[i].descricao, lista2->itens[j].descricao) == 0) && (lista1->itens[i].quantidade == lista2->itens[j].quantidade) && (lista1->itens[i].valor == lista2->itens[j].valor)){
				printf("\nItem [%i], ", i+1);
				printf("Descricao: %s", lista1->itens[i].descricao);
				printf("\nQuantidade: %i - ", lista1->itens[i].quantidade);
				printf("Valor: R$%.2f\n", lista1->itens[i].valor);
			}
		}
	}
}

//Testes
int main(void){
	
	//Criando lista
	struct TipoLista lista;
	struct TipoLista lista2;
	struct TipoItem item;

	//Iniciando lista vazia
	initVoidList(&lista2);
	initVoidList(&lista);

	//Inserindo dados
	strcpy(item.descricao, "Controle");
	item.quantidade = 24;
	item.valor = 29.00;
	insert(item, &lista);
	insert(item, &lista2);
	
	//Inserindo dados
	strcpy(item.descricao, "Radio");
	item.quantidade = 25;
	item.valor = 139.00;
	insert(item, &lista);
	insert(item, &lista2);

	//Inserindo dados
	strcpy(item.descricao, "Mouse");
	item.quantidade = 35;
	item.valor = 49.00;
	insert(item, &lista);
	insert(item, &lista2);

	//Inserindo dados
	strcpy(item.descricao, "TV-Box");
	item.quantidade = 20;
	item.valor = 199.00;
	insert(item, &lista);
	insert(item, &lista2);

	//Inserindo dados
	strcpy(item.descricao, "Pendrive");
	item.quantidade = 32;
	item.valor = 34.00;
	insert(item, &lista);
	insert(item, &lista2);
	
	//Imprimindo a lista
	impress(lista);
	impress(lista2);
	
	printf("\nImpressao da lista bem Sucedida, Pressione Enter para prosseguir aos testes...");
	getchar(); // Espera o usuário pressionar Enter
	system("clear"); // Limpa a tela

	printf("\n\nTESTES:\n");

	printf("________________________________");
	//Item) Calculando o valor total de itens em uma lista
	printf("\n\nTESTE: Item (A)");
	printf("\nValor total na lista 1: %.2f", calcSomaitensLista(lista));
	printf("\nValor total na lista 2: %.2f", calcSomaitensLista(lista));
	printf("\n________________________________");

	//Item) Retornando o produto (Struct) mais caro
	printf("\n\nTESTE: Item (B)");
	imprimirItemDeMaiorValor(lista);
	printf("\n________________________________");

	//Item) Quantidade de produtos com a descricao informada
	printf("\n\nTESTE: Item (C)");
	printf("\nQtd Produtos com a descricao informada: %i",searchProdutoDescricao(lista,"Radio"));
	printf("\n________________________________");

	//Item) Troca a posicao de 2 itens 
	printf("\n\nTESTE: Item (D)");
	trocarPosicao(&lista, 1, 3);
	impress(lista); 
	printf("\n________________________________");

	//Item) Receba uma lista e uma descrição, retornará -1 caso não tenha produto, ou a primeira posição se encontrada do item
	printf("\n\nTESTE: Item (E)");
	printf("\nBusca pela descrição\nposicao: %i", searchInListDescricao(lista, "Controle"));
	printf("\n________________________________");

	
	//Item) verificacao se 2 listas são em tudo iguais ou não
	printf("\n\nTESTE: Item (G)");

	int res = verIgualdadeListas(lista, lista2);
	if(res==0){
		printf("\nSão iguais?  %i", res);
	}else{
		printf("\nSão iguais?  %i", res);
	}
	printf("\n________________________________");
	//As listas são iguais, entretanto sempre retornará 0 neste caso devido ao teste para mudança de posicao anteriormente, desativar para que retorne 1

	//Item) Comparar quais das duas listas possuem maior quantidade de itens , (1) primeira, (2) segunda ou (0) para iguais
	printf("\n\nTESTE: Item (H)");
	printf("\nQtd de itens na lista: %i", listaComMaisItens(lista, lista2));
	printf("\n________________________________");

	//Item) Receberá duas listas e retornará a com o maior valor considerando a soma de todos os produtos de cada uma
	printf("\n\nTESTE: Item (I)");
	printf("\nLista com maior soma de valores: %i", listaComMaiorValor(lista,lista2));
	printf("\n________________________________");
	//Função funcionando corretamente, retornará até o momento dos testes 0, devido ao esquema de duplicar os itens para os testes...

	//Item) recebera duas listas e exibira os produtos presentes em ambas
	printf("\n\nTESTE: Item (J)\n");
	itensEmAmbasListas(&lista, &lista2);
	printf("\n________________________________");

}
