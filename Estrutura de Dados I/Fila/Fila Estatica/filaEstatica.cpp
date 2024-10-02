#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Definindo o tamanho da Fila, algoritimo Circular
#define MAX_TAM 10

typedef int TipoApontador;

//Definindo um apontador que aponta para uma struct TipoCelula para tipos Pilhas
typedef struct TipoCelula *TipoApontadorParaPilha;

//TipoPilha que recebe um tipo celula que contem um TipoItem
struct TipoPilha{
	//Tipo apontador que aponta pra base e para o topo da pilha
	TipoApontadorParaPilha Base, Topo;
	int Tamanho;
};

//Definindo Tipo item
struct TipoItem{
	int cod;
	float valor;
	const char *operacao; //saque, deposito, pagamento
};

//Definindo o TipoCelula para pilha
struct TipoCelula{
	struct TipoItem Item;
	TipoApontadorParaPilha Prox;
};

//Definindo pilha dinamica + Funções
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
	Pilha->Topo->Item = ItemParametro;
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
	*Item = Auxiliar->Prox->Item;
	
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
void imprimirPilha(TipoPilha pilha){
	//Definindo variável auxiliar para não esvaziar a pilha principal
	TipoApontadorParaPilha Auxiliar = pilha.Topo->Prox;
	
	int cont=0;
	printf("\n");
	//Enquanto a pilha não estiver vazia
	while(Auxiliar != NULL){
		//Imprime a pilha
		printf("\n Cod: %i \n Valor: %.2f \n Operacao: %s\n", Auxiliar->Item.cod, Auxiliar->Item.valor, Auxiliar->Item.operacao);
		
		//Avança para o proximo item
		Auxiliar = Auxiliar->Prox;
		cont++;
	}
}

//Definindo Tipo Fila + Funções
struct TipoFila{
	TipoItem item[MAX_TAM];
	TipoApontador frente, tras;
};

void IniciarFilaVazia(TipoFila *fila){
	//O apontador Frente recebe a posicao posterior 
	//Enquanto Tras recebe tambem 1, para fins de inicio
	fila->frente = 1;
	fila->tras = fila->frente;
}

//verifica se a Fila esta vazia
int isVoidFila(TipoFila fila){
	return(fila.frente == fila.tras);
}

void Enfileirar(TipoItem x, TipoFila *fila){
	//Se a Fila estiver cheia...
	if(fila->tras % MAX_TAM + 1 == fila->frente){
		printf("\nErro! Fila Cheia...");
	}else{
		fila->item[fila->tras-1] = x;
		fila->tras = fila->tras % MAX_TAM + 1;
	}
}

void Desenfileirar(TipoFila *fila, TipoItem *item){
	//Se a Fila estiver vazia
	if(isVoidFila(*fila)){
		printf("\nErro! Fila Vazia");
	}else{
		*item = fila->item[fila->frente - 1];
		fila->frente = fila->frente % MAX_TAM + 1;
	}
}


/*Explicando o laço For
	 * (int i = fila.frente) : O laço começa em i que recebe o valor da primeira posicao válida da fila
	 * 
	 * (i != fila.tras) : O laço continuará enquanto o item da frente for diferente do de tras, ou seja até o fim da fila
	 * 
	 * (i = i % MAX_TAM + 1): Garante o movimento circular da fila, Exemplo:
	 *  Se i for 10 (o máximo permitido), a próxima posição será 1, continuando o laço sem sair dos limites da fila.
	 * 
	 * Supondo que MAX_TAM seja 10: 
	 * 
	 * 		Se i=9, então, 9 % 10 = 9 (+ 1) = 10, ou seja, a próxima posição
	 * 		Se i=10, então, 10%10 = 0 (+ 1) = 1, ou seja, a posição inicial
	 * 
	 * */
	 
void Exibir(TipoFila fila){
	for(int i = fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		printf("\n [ %i' - Na Fila ]\n", i);
		printf(" Cod: %i \n Valor: %.2f \n Operacao: %s", fila.item[i-1].cod, fila.item[i-1].valor, fila.item[i-1].operacao);
		printf("\n\n");
	}
	printf("\n");
}

void LimparTela(){
	printf("\n\nPressione Enter para continuar...");
	getchar();
	system("clear");
	printf("\nLISTA DE EXERCICIOS - FILA ESTATICA\n");
}

//Função que recebe um item e verifica a presença na fila
int verificarItemFila(TipoItem x, TipoFila FilaX){
	for(int i = FilaX.frente; i != FilaX.tras; i = i % MAX_TAM + 1){
		//Se o item passado por parametro corresponder a termo de igualdade em todos os subitens referentes a Fila passada...
		if(x.cod == FilaX.item[i-1].cod && x.operacao == FilaX.item[i-1].operacao && x.valor == FilaX.item[i-1].valor){
			return 1;
		}
	}
	return 0;
}

//Função que recebe uma fila e retorna quantos itens possuem na mesma
int qtdItensFila(TipoFila Fila){
	int cont=0;
	
	for(int i=Fila.frente; i != Fila.tras; i = i % MAX_TAM + 1){
		cont++;	
	}
	
	return cont;
}

//Função que recebe uma fila e um item, e retorna a posição do Array que se encontra
int getPosicaoVetor(TipoFila fila, TipoItem x){
	
	if(isVoidFila(fila)){
		return -1;
	}
	
	for(int i=fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		if(x.cod == fila.item[i-1].cod && strcmp(x.operacao, fila.item[i-1].operacao) == 0 && x.valor == fila.item[i-1].valor){
			return i-1; //Posicao vetorial
		}
	}
	return -1; //Se não encontrado
}

//Função que retorna a posição que o item se encontra na fila
int getPosicaoFila(TipoItem x, TipoFila fila){
	//Começando pela primeira posição da fila
	int pos = 1;
	
	if(isVoidFila(fila)){
		return -1;
	}
	
	for(int i=fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		if (x.cod == fila.item[i-1].cod && strcmp(x.operacao, fila.item[i-1].operacao) == 0 && x.valor == fila.item[i-1].valor) {
            return pos;  // Retorna a posição lógica (posição na fila)
        }
        pos++; //Anda uma posição
	}
	return -1;
}

//Função que retorna o item com maior valor de saque
float getMaiorSaque(TipoFila fila){
	float maiorTemp = 0;
	for(int i=fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		if(strcmp(fila.item[i-1].operacao, "saque") == 0 && fila.item[i-1].valor > maiorTemp){
			maiorTemp = fila.item[i-1].valor;
		}
	}
	return maiorTemp;
}
//Função que retorna o item com maior deposito realizado
float getMaiorDeposito(TipoFila fila){
	float maiorTemp = 0;
	for(int i=fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		if(strcmp(fila.item[i-1].operacao, "deposito") == 0 && fila.item[i-1].valor > maiorTemp){
			maiorTemp = fila.item[i-1].valor;
		}
	}
	return maiorTemp;
}

//Função que retorna quantas operações de pagamento foram realizadas
int getQtdPagamentos(TipoFila fila){
	int cont = 0;
	for(int i=fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		if(strcmp(fila.item[i-1].operacao, "pagamento") == 0 && fila.item[i-1].valor != 0){
			cont++;
		}
	}
	return cont;
}

//Função que recebe uma fila e uma operação e retorna o valor total dos mesmos para a operação escolhida
float getValorTotalOperacao(TipoFila fila, const char *str){
	float total = 0;
	for(int i = fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		if(strcmp(fila.item[i-1].operacao, str) == 0){
			total+= fila.item[i-1].valor;
		}
	}
	return total;
}

//Função que inverte a ordem de uma fila estatica para uma pilha dinamica
void empilharFila(TipoPilha *pilha, TipoFila fila){
	
	for(int i = fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		Empilhar(fila.item[i-1], pilha);
	}
}

//Função que recebe uma fila e retorna 1 em caso de ordem crescente e 0 decrescente
int crescenteOUdecrescente(TipoFila fila){
	int x = -1;
	
	if(isVoidFila(fila)){
		return -1;
	}
	
	for(int i = fila.frente; i != fila.tras; i = i % MAX_TAM + 1){
		if(fila.item[i-1].cod > fila.item[i].cod && fila.tras != fila.frente){
			return 0;
		}else{
			x=1;
		}
	}
	return x;
}

int main(void){
	
	printf("\nLISTA DE EXERCICIOS - FILA ESTATICA\n");
	
	//Definindo a estrutura
	struct TipoFila fila;
	IniciarFilaVazia(&fila);
	
	struct TipoItem item;
	
	//Definindo as operacoes da fila
	item = {1, 250.70, "deposito"}; Enfileirar(item, &fila);
	item = {2, 30.00, "saque"}; Enfileirar(item, &fila);
	item = {3, 58.90, "pagamento"}; Enfileirar(item, &fila);
	item = {4, 20.00, "saque"}; Enfileirar(item, &fila);
	item = {5, 276.80, "deposito"}; Enfileirar(item, &fila);
	item = {6, 70.00, "saque"}; Enfileirar(item, &fila);
	item = {7, 69.00, "saque"}; Enfileirar(item, &fila);
	item = {8, 45.90, "pagamento"}; Enfileirar(item, &fila);
	
	//Mostrando
	Exibir(fila);
	LimparTela();
	
//---------------------------- Item [1] ----------------------------//
	printf("\nTeste Item 1) \n");
	
	//Comparando o item relação a todos os campos
	struct TipoItem itemBusca = {02, 30.00, "saque"};
	if(verificarItemFila(itemBusca, fila)){
		printf("\nO Item esta presente na Fila!");
	}else{
		printf("\nO Item não está presente na Fila");
	}
	
	LimparTela();
//-------------------------- Fim Item [1] --------------------------//

//---------------------------- Item [2] ----------------------------//
	printf("\nTeste Item 2)\n");
	
	printf("\nA Fila possui %i Itens presentes", qtdItensFila(fila));
	LimparTela();
//-------------------------- Fim Item [2] --------------------------//

//---------------------------- Item [3] ----------------------------//
	printf("\nTeste Item 3)\n");
	itemBusca = {02, 30.00, "saque"};
	int x = getPosicaoVetor(fila, itemBusca);
	
	if(x < 0){
		printf("\nO item nao esta presente na fila...");
	}else 
		if(x == 0){
		printf("\nErro! Fila Vazia!...");
	}else{
		printf("\nO item se encontra na [ %i' ] posicao vetorial da fila", x);
	}
	
	LimparTela();
//-------------------------- Fim Item [3] --------------------------//

//---------------------------- Item [4] ----------------------------//
	printf("\nTeste Item 4)\n");
	int y = getPosicaoFila(itemBusca, fila);
	
	if(y < 0){
		printf("\nO item nao esta presente na fila...");
	}else 
		if(y == 0){
		printf("\nErro! Fila Vazia!...");
	}else{
		printf("\nO item se encontra na [ %i' ] posicao da fila", x);
	}
	
	LimparTela();
//-------------------------- Fim Item [4] --------------------------//

//---------------------------- Item [5] ----------------------------//
	printf("\nTeste Item 5)\n");
	printf("\nO Saque de maior valor foi de: %.2f", getMaiorSaque(fila));
	
	LimparTela();
//-------------------------- Fim Item [5] --------------------------//

//---------------------------- Item [6] ----------------------------//
	printf("\nTeste Item 6)\n");
	printf("\nO Maior Deposito foi de: %.2f", getMaiorDeposito(fila));
	
	LimparTela();
//-------------------------- Fim Item [6] --------------------------//

//---------------------------- Item [7] ----------------------------//
	printf("\nTeste Item 7)\n");
	printf("\nForam realizadas [ %i ], operacoes de pagamento...", getQtdPagamentos(fila));
	
	LimparTela();
//-------------------------- Fim Item [7] --------------------------//

//---------------------------- Item [8] ----------------------------//
	printf("\nTeste Item 8)\n");
	char op[] = "saque";
	
	printf("\nO Valor total para [%s] e de: %.2f", op, getValorTotalOperacao(fila, op));
	LimparTela();
//-------------------------- Fim Item [8] --------------------------//

//---------------------------- Item [9] ----------------------------//
	printf("\nTeste Item 9)\n");
	
	struct TipoPilha pilha;
	IniciarPilhaVazia(&pilha);
	
	empilharFila(&pilha, fila);
	imprimirPilha(pilha);
	
	LimparTela();
//-------------------------- Fim Item [9] --------------------------//

//---------------------------- Item [10] ----------------------------//
	printf("\nTeste Item 10)\n");
	int c = crescenteOUdecrescente(fila);
	
	if(c<0){
		printf("\nErro! Fila Vazia");
	}else 
		if(c==0){
			printf("\nA Fila Nao Possui Ordem Crescente!");
	}else{
		printf("\nA Fila Possui Ordem Crescente!");
	}
	LimparTela();
//-------------------------- Fim Item [10] --------------------------//
	printf("\nFIM DOS TESTES");
}
