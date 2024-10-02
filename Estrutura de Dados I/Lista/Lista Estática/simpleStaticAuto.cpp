#include<stdio.h>
#include<string.h>
#define S_TAM 10 //Definindo tamanho da lista
#define ANO_ATUAL 2024 //Definindo ano atual

struct Veiculo{
	int ano;
	char montadora[30];
	char modelo[50];
	float valor;

	//Adicionado um flag para controle e facilitação condicional
	int flag = 0; //Inicialmente em 0, para quando for inserido seja 1
};

struct Lista{
	Veiculo itens[S_TAM];
	int tamanho;
};

//Função pra inicializar a lista vazia
//agenda é um ponteiro, e " -> "(aponta/seta) aponta pra tamanho na posição 0
void initVoidList(Lista *lista){
	lista -> tamanho = 0;
}

//Função de inserção que recebe um veículo e uma lista por referência
void insert(Veiculo v, Lista *lista){
	//Se agenda apontar para o tamanho e for maior ou igual o limite definido, então ...
	if(lista -> tamanho >= S_TAM){ //Escolhido S_TAM como max da lista
		printf("Lista cheia!..");
		return;
	}
	//Caso ainda não estiver cheia...

	//lista que é um ponteiro está sendo "setada/apontada" para itens, que é um vetor que analisa a posição como sendo lista "setando" em tamanho que recebe o veiculo (v)
	//Como lista é um ponteiro, logo inicia-se apontando pro endereço, ou seja, a primeira posição
	lista -> itens[lista -> tamanho] = v;
	lista -> tamanho++; //Tamanho inicialmente começa na posição 0 pela função initVoidList
}

//Função de excluir
void remove(Lista *lista, int position){
	//i = position, enquanto i for menor que lista que aponta para tamanho, i++
	for(int i=position; i < lista -> tamanho; i++){
		//Lista que aponta para itens na posição localizada 'i', recebe itens na próxima posição
		lista -> itens[i] = lista -> itens[i+1];
	}
	//Decrementa o tamanho
	lista -> tamanho--;
}

//função de impressão
void impress(Lista lista){
	for(int i=0; i < lista.tamanho; i++){
		printf("\n_________| Veículo |_________\n");
		printf("\nModelo: %s", lista.itens[i].modelo);
		printf("\nMontadora: %s", lista.itens[i].montadora);
		printf("\nAno: %i", lista.itens[i].ano);
		printf("\nValor: %.2f", lista.itens[i].valor);
		printf("\n_____________________________\n");
	}
}

//Função que verifica a quantidade de itens
int qtdItensInList(Lista *lista){
	int cont=0;

	for(int i=0; i<lista->tamanho; i++){
		if(lista->itens[i].flag == 1){
			cont++;
		}
	}
	return cont;
}

//Função que retorna o veículo mais caro
float maiorValor(Lista lista){
	float maior=0;

	for(int i=0; i<lista.tamanho; i++){
		if(lista.itens[i].valor > maior){
			maior = lista.itens[i].valor;
		}
	}
	return maior;
}

//Função que soma o valor de todos os carros dentro de uma lista
float calcSumListVal(Lista lista){
	float total=0;

	for(int i=0; i<lista.tamanho; i++){
		total += lista.itens[i].valor;
	}
	return total;
}

//Função que retorna a média do valor de todos os carros dentro de uma lista
float calcMedListVal(Lista lista){
	//Retorna o resultado baseado na diferença entre as duas funções anteriores, soma e quantidade
	return calcSumListVal(lista) / qtdItensInList(&lista);
}

//Função que retorna o item de maior valor
void itemDeMaiorValor(Lista lista){
	for(int i=0; i<lista.tamanho; i++){
		if(lista.itens[i].valor == maiorValor(lista)){
			printf("\nItem mais Caro: ");
			printf("%s ", lista.itens[i].montadora);
			printf("%s ", lista.itens[i].modelo);
			printf("%i - ", lista.itens[i].ano);
			printf("R$ %.2f", lista.itens[i].valor);
		}
	}
}

//Função que verifica e retorna a quantidade de automoveis com +20 anos de uso
int acimaVinteAnos(Lista lista){
	int qtd = 0;

	for(int i=0; i<lista.tamanho; i++){
		if((ANO_ATUAL - lista.itens[i].ano) > 20){
			qtd++;
		}
	}
	return qtd;
}

//Função de busca de veículo por montadora como parâmetro
//Nota-se que em .cpp não é possível usar somente char como parâmetro para chama-lo diretamente nos testes, e sim cost char...
int buscaPorMontadora(Lista lista, const char *SearchMontadora){
	int res = -1;

	for(int i=0; i<lista.tamanho; i++){
		if(strcmp(lista.itens[i].montadora, SearchMontadora) == 0){
			res = i; break;
		}
	}
	return res;
}

//Função que remove a primeira ocorrencia de um veículo com o modelo passado por parametro
void removeModel(Lista *lista, const char *SearchModelo){ //Novamente o uso de const char * para passagem direta
	//For que comeca a percorrer a lista para achar o modelo
	for(int i=0; i<lista->tamanho; i++){
		//Condição que compara o modelo da lista com o de passagem direta
		if(strcmp(lista->itens[i].modelo, SearchModelo) == 0){
			//Este segundo loop for é responsável por mover todos os elementos da lista uma posição para trás
			//a partir do índice onde o veículo com o modelo correspondente foi encontrado
			for(int j=i; j<lista->tamanho - 1; j++){
			//j recebe o indice i encontrado pela comparação, enquanto j for menor que o tamanho - 1, j ++
			//Logo inicia um loop onde a posição atual de j, começa a receber tudo a frente, mandando o que foi encontrado para a ultima posição
				lista->itens[j] = lista->itens[j+1];
			}
			//Como o item se encontra em ultima posição, Decrementa um no tamanho e finaliza o loop
			lista->tamanho--; break;
		}
	}
}

//Função que verifica se algum modelo possui como caractere final uma vogal: (1) para sim
int vogModel(Lista *lista){

	//Começa a percorrer a lista diretamente do endereço de memória
	for(int i=0; i<lista->tamanho; i++){
		//Obtendo o tamanho do conjunto modelo referente atual
		int comprimentoModelo = strlen(lista->itens[i].modelo);

		// Verifica se a string do modelo ao menos um caractere
		if(comprimentoModelo > 1){
			//Penultimo pois o último seria o "\n"
			char penultimoCaractere = lista->itens[i].modelo[comprimentoModelo - 1];

			//Verificando se é vogal
			if(penultimoCaractere=='a' || penultimoCaractere=='e' || penultimoCaractere=='i'|| penultimoCaractere=='o' || penultimoCaractere=='u'){
				return 1;
			}
		}
	}
	return 0;
}

//Função que verifica qual lista contém mais itens
int compareSizeList(Lista *lista1, Lista *lista2){
	int l1=0, l2=0;

	for(int i=0; i<S_TAM; i++){
		if(lista1->itens[i].flag == 1){
			l1++;
		}
	}

	for(int i=0; i<S_TAM; i++){
		if(lista2->itens[i].flag == 1){
			l2++;
		}
	}

	printf("\nl1: %i e l2: %i", l1, l2);

	if(l1>l2){
		return 1;
	}else
		if(l2>l1){
			return 2;
		}else{
			return 0;
		}
}

//Realizando testes...
int main(void){

	//criando variáveis de tipo Struct
	struct Veiculo v;
	struct Lista listaDeVeiculos;
	struct Lista listaDeVeiculos2;
	//Iniciando lista pela chamada de função, que é um ponteiro, logo o & define a posição
	initVoidList(&listaDeVeiculos);

	//copiando e inserindo os dados

	//-----------------------------//
	strcpy(v.modelo, "Fusca");
	strcpy(v.montadora, "Volkswagen");
	v.ano = 1986; v.valor = 17000;
	v.flag = 1; //Ativo
	insert(v, &listaDeVeiculos);
	//-----------------------------//

	//-----------------------------//
	strcpy(v.modelo, "Uno");
	strcpy(v.montadora, "Fiat");
	v.ano = 1994; v.valor = 21500;
	v.flag = 1; //Ativo
	insert(v, &listaDeVeiculos);
	//-----------------------------//

	//-----------------------------//
	strcpy(v.modelo, "Opala Sedan");
	strcpy(v.montadora, "Chevrolet");
	v.ano = 1977; v.valor = 25500;
	v.flag = 1; //Ativo
	insert(v, &listaDeVeiculos);
	//-----------------------------//

	//-----------------------------//
	strcpy(v.modelo, "Dart Colection");
	strcpy(v.montadora, "Dodge");
	v.ano = 1973; v.valor = 229000;
	v.flag = 1; //Ativo
	insert(v, &listaDeVeiculos2);
	//-----------------------------//

	impress(listaDeVeiculos);

	//Testanto função de soma de valores de veículos de mesma lista
	printf("\nValor Total da lista: %.2f", calcSumListVal(listaDeVeiculos));

	//Testanto função da média de valores de veículos de mesma lista
	printf("\nMedia de valores da lista: %.2f", calcMedListVal(listaDeVeiculos));

	//Testando a função para contar itens na lista
	printf("\nQuantidade de Itens na lista: %i", qtdItensInList(&listaDeVeiculos));

	//Testando a função para mostrar o item mais caro
	itemDeMaiorValor(listaDeVeiculos);

	//Testanto a função que mostra quantos veículos acima de 20 anos de uso
	printf("\nQuantidade de Veiculos acima de 20 anos de uso: %i", acimaVinteAnos(listaDeVeiculos));

	//Testando a função de busca por montadora, -1 para quando não há e acima e igual a 0 referente as posições
	int posicao = buscaPorMontadora(listaDeVeiculos, "Volksagen");
	(posicao == -1) ? printf("\n( %i ), ou seja, Nenhuma Ocorrencia...", posicao) : printf("\nResultado da busca por montadora: %i\n", posicao);

	//Testando a função de remoção por busca de modelo
	removeModel(&listaDeVeiculos, "Fusca");
	impress(listaDeVeiculos);

	//Testando a função que verifica a existência de uma vogal em última casa de algum veículo no campo modelo
	printf("\nAlgum modelo termina em vogal? (1 - Sim) (0 - Nao): %i", vogModel(&listaDeVeiculos));

	//Função que verifica a quantidade de itens em duas listas, e qual é maior: (1 - Primeira) (2 - Segunda) (0 - Ambas, Mesmo tamanho)
	printf("\nLista maior: %i", compareSizeList(&listaDeVeiculos, &listaDeVeiculos2));

}
