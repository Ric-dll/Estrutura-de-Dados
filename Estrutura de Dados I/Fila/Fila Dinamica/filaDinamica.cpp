#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Definindo um apontador que aponta para um endereço TipoCelula
typedef struct TipoCelula *TipoApontador;

//Definindo um apontador que aponta para uma struct TipoCelula
typedef struct TipoCelula *TipoApontadorParaPilha;

//Definição de item
struct TipoItem{
	int cod; //Codigo do item
	char chr; //Item presente, caractere
	int prioridade=0;
};

//Definição de Celula
struct TipoCelula{
	TipoItem item;
	TipoApontador Prox; //prox aponta para a próxima célula de memória
};

//TipoPilha que recebe um tipo celula que contem um TipoItem
struct TipoPilha{
	//Tipo apontador que aponta pra base e para o topo da pilha
	TipoApontador Base, Topo;
	int Tamanho;
};

//Definição de Pilha
struct TipoFila{
	TipoApontador Frente, Tras;
};


//Inicio das Funções básicas para PILHA

	//Função que inicia uma pilha, inicialmente como vazia, então somente terá função de inicialização
	void IniciarPilhaVazia(TipoPilha *Pilha){
		//Pilha que aponta para o topo recebe uma nova instancia de TipoCelula
		Pilha->Topo = (TipoApontadorParaPilha) malloc(sizeof(TipoCelula));
		//Como o objetivo é definir uma pilha vazia, então a base é igual ao topo
		Pilha->Base = Pilha->Topo;
		//Como é dinâmica, a casa prox em pilha->topo recebe um valor nulo até que seja adicionado itens
		Pilha->Topo->Prox = NULL;
		//Variável de controle de tamanho, indica que a pilha está com tamanho 0
		Pilha->Tamanho = 0;
	}

	//Função que verifica se a pilha é vazia
	int isVoid(TipoPilha Pilha){
		return(Pilha.Topo == Pilha.Base);
	}

	//Função respnsável por empilhar itens
	void Empilhar(TipoItem ItemParametro, TipoPilha *Pilha){
		//Auxiliar vai receber a instancia da criação de uma nova Celula
		TipoApontadorParaPilha Auxiliar = (TipoApontadorParaPilha) malloc(sizeof(TipoCelula));
		//Atribui mais um item ao topo da pilha
		Pilha->Topo->item = ItemParametro;
		//Auxiliar recebe as informações de Pilha, ou seja, Prox de Auxiliar recebe o Topo da Pilha
		Auxiliar->Prox = Pilha->Topo;
		//O topo recebe a celula Auxiliar criada
		Pilha->Topo = Auxiliar;
		//O contador de tamanho aumenta
		Pilha->Tamanho++;
	}

	//Função responsável por desempilhar itens
	void Desempilhar(TipoItem *Item, TipoPilha *Pilha){
		//Declara um ponteiro auxiliar para ajudar na manipulação da pilha
		TipoApontadorParaPilha Auxiliar;
		
		//Condição de Erro
		if(isVoid(*Pilha)){
			printf("\nErro! Pilha Vazia..."); return;
		}
		//Auxiliar recebe item presente no topo da pilha
		Auxiliar = Pilha->Topo;
		
		//Atualiza o topo da pilha para o próximo item
		Pilha->Topo = Auxiliar->Prox;
		
		//Copia o item do próximo nó para o item fornecido
		*Item = Auxiliar->Prox->item;
		
		//Libera a memória do nó removido
		free(Auxiliar);
		
		//Diminui o tamanho da pilha
		Pilha->Tamanho--;
	}

	//Função que retorna o tamanho da Pilha
	int sizeStack(TipoPilha Pilha){
		return(Pilha.Tamanho);
	}

	//Função que imprime a pilha
	void imprimirPilha(TipoPilha Pilha){
		//Definindo variável auxiliar para não esvaziar a pilha principal
		TipoApontadorParaPilha Auxiliar = Pilha.Topo->Prox;
		
		int cont=0;
		printf("\n");
		//Enquanto a pilha não estiver vazia
		while(Auxiliar != NULL){
			//Imprime a pilha
			printf("\n\t| %c | - Cod: %i", Auxiliar->item.chr, Auxiliar->item.cod);
			
			//Avança para o proximo item
			Auxiliar = Auxiliar->Prox;
			cont++;
		}
	}

//Inicio das funções básicas da FILA

//Função que inicia uma Fila vaiza em uma região da memória
void IniciarFilaVazia(TipoFila *Fila){
//Cria uma nova instancia de uma célula e atribui o endereço ao campo frente presente em fila
	Fila->Frente = (TipoApontador)malloc(sizeof(TipoCelula));
	Fila->Tras = Fila->Frente; //Como é vazia, então os ponteiros de inicio e fim estão no mesmo lugar
	Fila->Frente->Prox = NULL; //A primeira casa aponta para NULL
}

//Função que verifica se a fila está vazia
int isVoidFila(TipoFila Fila){
	return(Fila.Frente == Fila.Tras);
}

//Função que enfileira os itens na fila
void Enfileirar(TipoItem x, TipoFila *Fila){
	//Cria uma nova conexão atras da primeira já existente, mantendo este espaço
	//A estrutura cresce para trás, obedecendo o esquema de fila
	Fila->Tras->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
	//O campo 'tras' da fila atual, recebe o endereco da celula criada
	Fila->Tras = Fila->Tras->Prox;
	Fila->Tras->item = x; //Então a instancia que foi criada recebe o item
	Fila->Tras->Prox = NULL;
}

//Função que desenfileira os itens, onde o parametro Copia receberá o item retirado para uso opcional
void Desenfileirar(TipoFila *Fila, TipoItem *Copia){
	//Auxiliar que fará o intermédio da retirada do item
	TipoApontador Aux;
	
	//Se estiver vazia
	if(isVoidFila(*Fila)){
		printf("ERRO! Fila Vazia...");
		return;
	}
	
	//Senão
	
	//Auxiliar receberá a primeira posicao da Fila, que está em Fila->Frente para armazenar a informação
	Aux = Fila->Frente;
	//A posição que foi armazenada recebe a próxima da Fila, ou seja, A que está a frente
	Fila->Frente = Fila->Frente->Prox;
	
	//Realiza a Cópia do item para a variável
	*Copia = Fila->Frente->item;
	
	//E libera a posição de memória
	free(Aux);
}

//Função que imprime a fila
void Imprimir(TipoFila Fila){
	//Um Apontador que será responsável por percorrer a Fila
	TipoApontador Aux = Fila.Frente->Prox;
	
	printf("\n");
	
	while(Aux != NULL){
		printf("[ %i' - Item: %c ]\t", Aux->item.cod, Aux->item.chr);
		Aux = Aux->Prox;
	}
}

//Função que Limpa a tela
void LimparTela(){
	printf("\n\nPressione Enter para continuar...");
	getchar();
	system("clear");
	printf("\nLISTA DE EXERCICIOS - FILA ESTATICA\n");
}

//Função que verifica se um item está presente na fila
int getItemFila(TipoItem item, TipoFila fila){
	
	if(isVoidFila(fila)){
		return -1;
	}
	
	TipoApontador Aux = fila.Frente->Prox;
	
	while(Aux != NULL){
		if(Aux->item.chr == item.chr && Aux->item.cod == item.cod){
			return 1;
		}
		Aux = Aux->Prox;
	}
	return 0;
}

//Função que Simula um furo na fila com um TipoItem, na primeira posição
void FurarFila(TipoFila *fila, TipoItem x){
	
	if(isVoidFila(*fila)){
		printf("\nErro, Fila Vazia...");
		return;
	}
	
	//Criando uma nova instância de uma nova célula
	TipoApontador newCelula = (TipoApontador)malloc(sizeof(TipoCelula));
	
	//A nova célula criada recebe o item do parâmetro
	newCelula->item = x;
	//O prox da célula aponta para a que está após a Frente, no caso a primeira válida
	newCelula->Prox = fila->Frente->Prox;
	//E o campo que localiza a região de fila, no caso a primeira não valida, recebe o endereço da nova célula
	fila->Frente->Prox = newCelula;
	
	printf("\nFila Furada Com Sucesso!...\n");
}

//Função que Simula um furo na fila que insere após a posição apontada por parâmetro
void FurarFilaP(TipoFila *fila, TipoApontador p, TipoItem x){
	
	if(p == NULL){
		printf("\nErro, Posicao Invalida...");
		return;
	}
	
	if(isVoidFila(*fila)){
		printf("\nErro, Fila Vazia...");
		return;
	}
	
	//Criando uma nova instância de uma nova célula
	TipoApontador newCelula = (TipoApontador)malloc(sizeof(TipoCelula));
	
	//O item da nova célula recebe o item passado por parâmetro
	newCelula->item = x;
	
	//A posicao prox da nova celula recebe
	//Como 'p' é um tipoApontador, ele receberá uma posição de memória
	newCelula->Prox = p->Prox;
	
	//Prox de 'p' recebe o endereço apontado de newCelula
	p->Prox = newCelula;
	
}

//Função que verifica se os itens estão enfileirados em ordem crescente ou decrescente
int CrescenteOuDecrescente(TipoFila fila){
	if(isVoidFila(fila)){
		return -1;
	}
	
	TipoApontador Aux = fila.Frente->Prox;
	
	while(Aux != NULL && Aux->Prox != NULL){
		if(Aux->item.cod > Aux->Prox->item.cod){ 
			return 0; //Não está em ordem crescente
		}
		Aux = Aux->Prox;
	}
	return 1; //Está em ordem crescente
}

//Função que recebe uma Fila de chr não ordenada por cod e manda o maior pro inicio da Fila
void Batatinha(TipoFila *Fila){
	
	if(isVoidFila(*Fila)){
		printf("\nErro! Fila Vazia..."); 
		return;
	}
	
	//Apontador aux que irá percorrer a Fila
	TipoApontador Aux = Fila->Frente->Prox;
	//Inicializa 'MaiorIndiceAnterior' como o primeiro elemento da Frente e 'Maior' como o primeiro item valido da fila
	TipoApontador MaiorIndiceAnterior = Fila->Frente;
	TipoApontador Maior = Aux;
	
	while(Aux->Prox != NULL){
		//Se o item atual tiver o cod maior que o cod presente em Maior
		if(Aux->Prox->item.cod > Maior->item.cod){
			//A Variavel Aponta para Aux que agora é o anterior Maior
			MaiorIndiceAnterior = Aux;
			//Enquanto a variável 'Maior' recebe o item tal qual possui maior cod
			Maior = Aux->Prox;
		}
		Aux=Aux->Prox;
	}
	//Verifica se o primeiro já está na primeira posição, e se sim, acaba por aqui
	if(Maior == Fila->Frente->Prox){
		return;
	}
	
	//Caso não
	
	//O Anterior em prox, recebe o prox do Maior Obtido, removendo o maior item da sua posição original
	MaiorIndiceAnterior->Prox = Maior->Prox; //O item anterior agora aponta para o próximo item após o maior
	
	//Agora se o Maior era o último...
	if(Maior == Fila->Tras){
		//Se caso fosse o último, o anterior ao mesmo que irá pra tras
		Fila->Tras = MaiorIndiceAnterior; //'Tras' agora aponta para o 'MaiorIndiceAnterior', pois o maior foi removido
	}
	
	//Agora Insere o maior na frente
	///Maior em prox recebe o ponteiro de fila na posicao a frente e em prox
	Maior->Prox = Fila->Frente->Prox;
	//Enquanto fila na posicao frente e em prox recebe um ponteiro pra Maior
	Fila->Frente->Prox = Maior;
}

//Função que recebe duas Filas e retorna uma terceira com os itens não pertencentes a segunda
void gerarDiferencaFila(TipoFila f1, TipoFila f2, TipoFila *f3){
	
	TipoApontador Aux = f1.Frente->Prox;
	//TipoApontador Aux2 = f2.Frente->Prox;
	TipoItem item;
	
	//Se alguma estiver vazia, será incapaz de realizar a função
	if(isVoidFila(f1)){
		printf("\nERRO! A Primeira Fila Esta Vazia...");
		return;
	}
	
	if(isVoidFila(f2)){
		printf("\nA Segunda Fila Esta Vazia, Entao Todos os Itens da Primeira serao copiados");
		
		while(Aux != NULL){
			Enfileirar(Aux->item, f3);
			Aux=Aux->Prox;
		}
		return;
	}
	
	//Aux percorre a primeira verificando pela função criada anteriormente se o item está presente na segunda fila
	while(Aux != NULL){
		//Item recebe o item atual do laço para comparação
		item = Aux->item;
		
		//Comparação, se o item da fila NAO estiver presente na 2
		if(!getItemFila(item, f2)){
			Enfileirar(item, f3);
		}
		Aux=Aux->Prox;
	}
}

//Função que recebe duas Filas e retorna uma terceira com os itens Que estão presentes em ambas
void gerarIntersecaoFila(TipoFila f1, TipoFila f2, TipoFila *f3){
	
	TipoApontador Aux = f1.Frente->Prox;
	//TipoApontador Aux2 = f2.Frente->Prox;
	TipoItem item;
	
	//Se alguma estiver vazia, será incapaz de realizar a função
	if(isVoidFila(f1)){
		printf("\nERRO! A Primeira Fila Esta Vazia...");
		return;
	}
	
	if(isVoidFila(f2)){
		printf("\nERRO! A Segunda Fila Esta Vazia...");
		return;
	}
	
	//Aux percorre a primeira verificando pela função criada anteriormente se o item está presente na segunda fila
	while(Aux != NULL){
		//Item recebe o item atual do laço para comparação
		item = Aux->item;
		
		//Comparação, se o item da fila NAO estiver presente na 2
		if(getItemFila(item, f2)){
			Enfileirar(item, f3);
		}
		Aux=Aux->Prox;
	}
}

//Função que desenfileira itens com prioridade == 1
void DesenfileirarPorPrioridade(TipoFila *Fila, TipoItem *Copia){
	//verifica se está vazia
	if(isVoidFila(*Fila)){
		printf("\nErro! Fila Vazia...");
		return;
	}
	
	TipoApontador Aux = Fila->Frente;
	TipoApontador Prioridade = NULL;
	
	//Percorrendo até achar o primeiro item com prioridade == 1
	while(Aux->Prox != NULL){
		//Se achar a primeira ocorrência
		if(Aux->Prox->item.prioridade == 1){
			//Recebe o endereço de memória de Aux
			Prioridade = Aux;
			break; //E para
		}
		Aux = Aux->Prox;
	}
	
	//Caso não houver item com prioridade
	if(Prioridade == NULL){
		printf("\nNao Ha Nenhum Item Enfileirado Com Prioridade!");
		return;
	}else{//Porém se encontrou algo
		//Aux recebe prox do item obtido
		Aux = Prioridade->Prox;
		//O prox do item recebe o prox de Aux
		Prioridade->Prox = Aux->Prox;
		//O endereço de memória de Copia recebe o item presente em Aux
		*Copia = Aux->item;
		free(Aux);
	}
}

//Função que ivnerte a ordem de uma fila recebida usando uma pilha...
void inverterFilaComPilha(TipoFila *f1, TipoPilha *pAux){
	
	TipoApontador Aux = f1->Frente->Prox;
	TipoItem item;
	
	if(isVoidFila(*f1)){
		printf("\nErro! Fila Vazia..."); return;
	}
	
	while(Aux != NULL){
		item = Aux->item;
		//Empilhando os itens da fila na pilha
		Empilhar(item, pAux);
		Aux=Aux->Prox;
	}
	
	//Reiniciando a Fila
	IniciarFilaVazia(f1);
	printf("\nInvertendo a Ordem da Fila...\n");
	
	while(!isVoid(*pAux)){
		//Desempilha e faz uma copia para o parametro item 
		Desempilhar(&item, pAux);
		Enfileirar(item, f1);
	}
}

int main(void){
	
	printf("\nLISTA DE EXERCICIOS - FILA ESTATICA\n");
	//Criando e inicializando a Fila
	struct TipoFila fila;
	IniciarFilaVazia(&fila);
	//Teste
	struct TipoItem item;
	item = {1, 'a'}; Enfileirar(item, &fila);
	item = {2, 'b'}; Enfileirar(item, &fila);
	item = {3, 'c'}; Enfileirar(item, &fila);
	item = {4, 'd'}; Enfileirar(item, &fila);
	Imprimir(fila);
	LimparTela();
	
//---------------------- ITEM 02 ----------------------//
	printf("\nTeste - [ Item 2 ]\n");
	
	//Definindo o item de busca
	item = {3, 'c'}; 
	int x = getItemFila(item, fila);
	
	if(x<0){
		printf("\nErro! Pilha Vazia...");
	}else 
		if(x==0){
			printf("\nO Item Não Esta Presente Na Fila");
	}else{
		printf("\nO Item Está Presente Na Fila");
	}
	
	LimparTela();
//---------------------- FIM 02 ----------------------//

//---------------------- ITEM 03 ----------------------//
	printf("\nTeste - [ Item 3 ]\n");
	
	FurarFila(&fila, item);
	Imprimir(fila);
	
	LimparTela();
//---------------------- FIM 03 ----------------------//

//---------------------- ITEM 04 ----------------------//
	printf("\nTeste - [ Item 4 ]\n");
	
	item = {0, 'u'};
	TipoApontador p = fila.Frente->Prox->Prox->Prox;
	FurarFilaP(&fila, p, item);
	Imprimir(fila);
	
	LimparTela();
//---------------------- FIM 04 ----------------------//

//---------------------- ITEM 05 ----------------------//
	printf("\nTeste - [ Item 5 ]\n");
	
	int y = CrescenteOuDecrescente(fila);
	if(y < 0){
		printf("\nErro! Fila Vazia...");
	}else 
		if(y == 0){
			printf("\nA Fila Nao Possui Ordem Crescente...");
	}else{
		printf("\nA Fila Possui Ordem Crescente...");
	}
	
	LimparTela();
//---------------------- FIM 05 ----------------------//

//---------------------- ITEM 06 ----------------------//
	printf("\nTeste - [ Item 6 ]\n");
	
	struct TipoFila fila2; IniciarFilaVazia(&fila2);
	item = {5, 'a'}; Enfileirar(item, &fila2);
	item = {2, 'b'}; Enfileirar(item, &fila2);
	item = {4, 'c'}; Enfileirar(item, &fila2);
	item = {6, 'd'}; Enfileirar(item, &fila2);
	item = {9, 'e'}; Enfileirar(item, &fila2);
	item = {4, 'f'}; Enfileirar(item, &fila2);
	
	printf("\nFila Antes...\n");
	Imprimir(fila2);
	
	printf("\nFila Apos...\n");
	Batatinha(&fila2);
	Imprimir(fila2);
	
	LimparTela();
//---------------------- FIM 06 ----------------------//

//---------------------- ITEM 07 ----------------------//
	printf("\nTeste - [ Item 7 ]\n");
	
	//Criando as filas para teste
	TipoFila f1, f2, f3;
	IniciarFilaVazia(&f1);
	IniciarFilaVazia(&f2);
	IniciarFilaVazia(&f3); //Continuará vazia até a chamada da função
	
	item = {0, 'a'}; Enfileirar(item, &f1);
	item = {1, 'b'}; Enfileirar(item, &f1);
	item = {2, 'x'}; Enfileirar(item, &f1);
	item = {3, 'd'}; Enfileirar(item, &f1);
	item = {4, 'y'}; Enfileirar(item, &f1);
	item = {5, 'z'}; Enfileirar(item, &f1);
	
	item = {0, 'a'}; Enfileirar(item, &f2);
	item = {1, 'b'}; Enfileirar(item, &f2);
	item = {2, 'c', 1}; Enfileirar(item, &f2);
	item = {3, 'd'}; Enfileirar(item, &f2);
	item = {4, 'e'}; Enfileirar(item, &f2);
	item = {5, 'f', 1}; Enfileirar(item, &f2);
	
	gerarDiferencaFila(f1, f2, &f3);
	
	printf("\nFila 3)\n");
	Imprimir(f3);
	
	LimparTela();
//---------------------- FIM 07 ----------------------//

//---------------------- ITEM 08 ----------------------//
	printf("\nTeste - [ Item 8 ]\n");
	
	printf("\nFila 4)\n");
	TipoFila f4; IniciarFilaVazia(&f4);
	gerarIntersecaoFila(f1,f2,&f4);
	Imprimir(f4);
	
	LimparTela();
//---------------------- FIM 08 ----------------------//

//---------------------- ITEM 09 ----------------------//
	printf("\nTeste - [ Item 9 ]\n");
	
	TipoItem itemZ;
	
	TipoApontador Auxiliar = f2.Frente->Prox;
	while(Auxiliar != NULL){
		DesenfileirarPorPrioridade(&f2, &itemZ);
		Auxiliar=Auxiliar->Prox;
	}
	Imprimir(f2);
	
	LimparTela();
//---------------------- FIM 09 ----------------------//

//---------------------- ITEM 10 ----------------------//
	printf("\nTeste - [ Item 10 ]\n");
	//Criando uma pilha
	TipoPilha pilha; IniciarPilhaVazia(&pilha);
	
	inverterFilaComPilha(&f2, &pilha);
	Imprimir(f2);
	
	LimparTela();
//---------------------- FIM 10 ----------------------//

}


































