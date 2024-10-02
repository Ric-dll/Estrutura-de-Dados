#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INICIO_ARRANJO 1 //Indica o início da lista
#define TAM_MAX 20 //Tamanho maximo da lista


//Definindo o tipoItem da Pilha e Lista 
struct TipoItem{
	int Chave;
	char Caractere;
};

//Definindo um apontador que aponta para uma struct TipoCelula
typedef struct TipoCelula *TipoApontador;

//Definindo um apontador para TipoLista
typedef int TipoApontadorLista;


//Definindo o TipoCelula 
struct TipoCelula{
	struct TipoItem Item;
	TipoApontador Prox;
};

//TipoPilha que recebe um tipo celula que contem um TipoItem
struct TipoPilha{
	//Tipo apontador que aponta pra base e para o topo da pilha
	TipoApontador Base, Topo;
	int Tamanho;
};

//Definindo Lista Estatica
	//Definindo o tipo da lista
	struct TipoLista{
		TipoItem itens[TAM_MAX];
		//Esses apontadores são usados para indicar o primeiro e o último elemento da lista
		TipoApontadorLista primeiro;
		TipoApontadorLista ultimo;
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
	int isVoidList(TipoLista lista){
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
	void remove(TipoApontadorLista p, TipoLista *lista, TipoItem *itemParametro){

		//Se a lista estiver vazia, ou, se a posição "p" fornecida é válida
		//Se usar apenas lista ao invés de *lista, estará passando o próprio ponteiro, não o valor apontado por ele. 
		if(isVoidList(*lista) || p >= lista -> ultimo){
			printf("\nErro: Posicao nao existe");
			return; //Encerra a função aqui
		}

		//Item recebe lista que está localizada na posição anterior da posição p passada para exclusão
		//Quando  usa-se *item está acessando o valor apontado pelo ponteiro
		*itemParametro = lista->itens[p-1]; //(p-1) pois o array começa em 0...
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
		printf("\nLista: ");
		for(int i=0; i<lista.ultimo; i++){
			printf(" [ %c ] ", lista.itens[i].Caractere);
		}
	}

//Fim definição de Lista Estática

//Função que inicia uma pilha, inicialmente como vazia, então somente terá função de inicialização
void IniciarPilhaVazia(TipoPilha *Pilha){
	//Pilha que aponta para o topo recebe uma nova instancia de TipoCelula
	Pilha->Topo = (TipoApontador) malloc(sizeof(TipoCelula));
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
	TipoApontador Auxiliar = (TipoApontador) malloc(sizeof(TipoCelula));
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
	TipoApontador Auxiliar;
	
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
void imprimirPilha(TipoPilha Pilha){
	//Definindo variável auxiliar para não esvaziar a pilha principal
	TipoApontador Auxiliar = Pilha.Topo->Prox;
	
	int cont=0;
	printf("\n");
	//Enquanto a pilha não estiver vazia
	while(Auxiliar != NULL){
		//Imprime a pilha
		printf("\n\t| %c | - Cod: %i", Auxiliar->Item.Caractere, Auxiliar->Item.Chave);
		
		//Avança para o proximo item
		Auxiliar = Auxiliar->Prox;
		cont++;
	}
}

void LimparTela(){
	printf("\n\nPressione Enter para continuar...");
	getchar();
	system("clear");
	printf("\nLISTA DE EXERCICIOS - PILHA DINAMICA\n");
}

//Item 1) Verificar se a pilah possui a estrutura: ...Topo ->|p| |x| |p| |x| ...Base
int verificarPadraoXP(TipoPilha Pilha){
	
	TipoItem item;
	
	int cont=0;
	while(!isVoid(Pilha)){
		//Como a função não recebe um ponteiro, é necessário usar & na função, caso contrário não
		//Como o topop está vazio, aguardando um novo item, pode-se começar desempilhando por ele
		Desempilhar(&item, &Pilha);
		
		//Verificando padrão de pilha
		if((item.Caractere != 'p') && (cont%2 != 0)){
			return 0;
		}
		cont++;
	}
	return 1;
}

//Item 2) Recebe duas pilhas e verifica a igualdade das mesmas
int compararPilhas(TipoPilha p1, TipoPilha p2){
	
	//Se já houverem tamanhos divergentes, logo são diferentes
	if(sizeStack(p1) != sizeStack(p2)){
		return 0;
	}
	
	TipoItem item1, item2;
	
	//Caso possuam o mesmo tamanho
	int cont=0;
	
	while(!isVoid(p1) && !isVoid(p2)){
		//Desempilha o topo primeiro, pois o mesmo está vazio
		Desempilhar(&item1, &p1);
		Desempilhar(&item2, &p2);
		
		//Caso houver qualquer divergência logo já encerra o programa
		//Verificando somente o caractere
		if(item1.Caractere != item2.Caractere){
			return 0;
		}
		cont++;
	}
	//Se cont for > 0
	return cont;
}

//Item 03) verificar se os itens da pilha formam um palindromo
int verificarPalindromo(const char *str){
	
	//Pilha que vai receber o char
	TipoPilha pilhaAuxiliar;
	IniciarPilhaVazia(&pilhaAuxiliar);
	
	int tamStr = strlen(str);
	TipoItem item;
	
	//Empilhando a string
	for(int i=0; i<tamStr; i++){
		item.Caractere = str[i];
		Empilhar(item, &pilhaAuxiliar);
	}
	
	//Verificando a string com os caracteres avulsos empilhados
	int cont=0;
	while(!isVoid(pilhaAuxiliar)){
		//Como o Desempilhar começa removendo do topo enquanto a posição começa em 0...
		Desempilhar(&item, &pilhaAuxiliar);
		
		//Verificando na posição [cont], que inicia em 0, enquanto compara com o desempilha, que retira do topo
		//E se já houver alguma contradição na igualdade...	
		if(str[cont] != item.Caractere){
			return 0; //Não é palindromo
		}
		cont++;
	}
	return 1; //É um palindromo
}

//Item 04) retornando o endereço de memoria referente ao item presente passado por parâmetro com o elemento informado
TipoApontador posicaoItem(TipoItem itemParametro, TipoPilha pilhaParametro){
	//Começando com NULL para tratar o caso de não ser encontrado
	TipoApontador Endereco = NULL;
	//Responsável por percorrer a pilha
	TipoApontador posicaoAtual = pilhaParametro.Topo;
	
	while(posicaoAtual != NULL){
		//Usando o caractere como base de comparação
		if(itemParametro.Caractere == posicaoAtual->Item.Caractere){
			Endereco = posicaoAtual;
			break; //Apos encontrar uma ocorrencia, já encerra ...
		}
		//Avança para a proxima posição
		posicaoAtual = posicaoAtual->Prox;
	}
	return Endereco;
}

//Item 05) Função que verifica se a pilha comporta a ordem crescente dos itens
int verificarSeCrescente(TipoPilha pilha){
	//Verifica se está vazia
	if(isVoid(pilha)){
		printf("\nPilha Vazia!...");
		return 0;
	}

	//Criando dois tipos itens para facilitar a comparação
	TipoItem itemAnterior, itemAtual;

	//Desempilha o item do topo para iniciar a comparação
	Desempilhar(&itemAnterior, &pilha);

	while(!isVoid(pilha)){
		//Desempilha o proximo item
		Desempilhar(&itemAtual, &pilha);

		//Se o item anterior for maior que o atual...
		if(itemAnterior.Chave <= itemAtual.Chave){
			return 0;
		}

		//Atualiza o atual para o anterior
		itemAnterior = itemAtual;
	}
	return 1;
}

//Item 06)Função que verifica a presença de um item em duas pilhas
int verificarPresencaDeItem(TipoItem item, TipoPilha p1, TipoPilha p2){
	
	int verP1=0, verP2=0;
	
	TipoItem itemTemporario;
	
	//Primeiro laço, responsável por percorrer a primeira pilha
	while(!isVoid(p1)){
		//Desempilha primeiro o item, pois o mesmo não passa de um espaço vazio atualmente
		Desempilhar(&itemTemporario, &p1);
		
		//Utilizando caractere para comparação
		if(item.Caractere == itemTemporario.Caractere){
			verP1 = 1;
			break;
		}
		
	}
	
	//Segundo laço, responsável por percorrer a segunda pilha
	while(!isVoid(p2)){
		//Desempilha primeiro o item, pois o mesmo não passa de um espaço vazio atualmente
		Desempilhar(&itemTemporario, &p2);
		
		//Utilizando caractere para comparação
		if(item.Caractere == itemTemporario.Caractere){
			verP2 = 1;
			break;
		}
	}
	
	if((verP1 && verP2) != 0){
		return 1;
	}else{
		return 0;
	}
}

//Item 07) Função que retira todos os itens com vogal de uma pilha
//Como vamos trabalhar modificando o item que será passado, precisamos passar o ponteirar ele
void retirarVogais(TipoPilha *pilha){
	//Criando uma pilha para sobrescrever a que contem vogais
	TipoPilha newPilha;
	//Iniciando a mesma como vazia...
	IniciarPilhaVazia(&newPilha);
	
	//Criando um tipoItem auxiliar para remoção e uma string de vogais
	TipoItem item;
	char vogais[] = "aeiouAEIOU"; //10 caracteres
	
	while(!isVoid(*pilha)){
		//Flag de vogal que e recriado a cada laço 
		int vog = 0;
		
		//Desempilhando o primeiro item e verificando...
		Desempilhar(&item, pilha);
		
		for(int i=0; i<10; i++){
			if(item.Caractere == vogais[i]){
				//Marca a flag como vogal e para o laço
				vog = 1;
				break; //Encerra na primeira ocorrencia
			}
		}
		//Se for vogal estará como 1, se estiver como !1 = 0 é consoante
		if(!vog){
			Empilhar(item, &newPilha);
		}
	}//Ao final do laço, pilha se encontra vazia
	
	//Laço para copiar os itens da nova pilha para a pilha original
	while(!isVoid(newPilha)){
		Desempilhar(&item, &newPilha);
		Empilhar(item, pilha);
	}
}

//Item 08) Função responsável por gerar um nó na pilha e inserir um item
void furarPilha(TipoPilha *pilha, TipoApontador posicao, TipoItem item){
	
	//Cria uma nova instancia, um novo nó para um TipoCelula, supondo que sempre há memória disponivel
	TipoApontador newNo = (TipoApontador)malloc(sizeof(TipoCelula));
	
	//O novo nó, onde pode armazenar item, recebe o item passado
	newNo->Item = item;
	
	//Conectando o novo no na pilha
	//O prox de newNo passa a ser o prox da posicao passada
	newNo->Prox = posicao->Prox;
	//E posicao descola seu apontador para newNo
	posicao->Prox = newNo;
	
	//Conodição especificada para caso o novo nó seja a base
	if(pilha->Base == posicao){ //Se a base da pilha for igual a posicao passada
		pilha->Base = newNo;
	}
}

//Item 09) Função que inverte uma frase preservando a ordem das palavras
void espelharPalavras(const char *str){
	//Pilha que receberá a palavra
	TipoPilha pilha;
	IniciarPilhaVazia(&pilha);
	
	//Item auxiliar para funcionamento das funções
	TipoItem item;
	
	//Armazena o tamanho da String
	int tamStr = strlen(str);
	
	//Para percorrer a String usando for, para melhor controle
	for(int i=0; i <= tamStr; i++){
		//Se a palavra não for um espaço e nem o final referenciado por padrão '\0'...
		if((str[i] != ' ') && (str[i] != '\0')){
			//Então item no campo caractere recebe str na posicao i atual
			item.Caractere = str[i];
			//E empilha
			Empilhar(item, &pilha);
		//Após todo o empilhamento...
		}else{
			//Como somente a saída precisa estar espelhada, não modificarei a pilha...
			//Somente printaremos o inverso desempilhando...
			while(!isVoid(pilha)){
				Desempilhar(&item, &pilha);
				printf("%c", item.Caractere);
			}
			//E agora print o espaço
			printf(" ");
		}
	}
	printf("\n");
}

//Item 10) Função que recebe uma lista estática e inverte usando uma pilha dinâmica
void inverterListaComPilha(TipoLista *lista, TipoPilha *pilha){

	//TipoItem auxiliar que ajudará a remover o item
	TipoItem itemAux;
	IniciarPilhaVazia(pilha);
	
	//A ideia é: Enquanto a lista ainda não estiver vazia, retire os itens e os empilhe
	//A partir da lista, vai pra pilha
	while(!isVoidList(*lista)){
		//Removemos um item da mesma, começando do começo
		remove(lista->primeiro, lista, &itemAux);
		//E empilhamos na pilha
		Empilhar(itemAux, pilha);
	}
	
    // Agora, a pilha contém os itens da lista na ordem inversa.
    // Vamos reiniciar a lista e adicionar os itens da pilha de volta
	initVoidList(lista);
	
	//A partir da pilha, vai pra lista
	while(!isVoid(*pilha)){
		//Desempilha o item
		Desempilhar(&itemAux, pilha);
		//Adiciona a lista
		insert(itemAux, lista);
	}
}

//Item 11) Função que recebe uma lista dinâmica com numeros inteiros e gera
//Duas pilhas dinâmicas, uma com par e outra com os valores impares
void gerarPilhasParImpar(TipoLista lista, TipoPilha *pilhaPar, TipoPilha *pilhaImpar){
	
}

int main(void){
	printf("\nLISTA DE EXERCICIOS - PILHA DINAMICA\n");
	
	//TipoItem que sera utilizado sempre para adição de novos itens às pilhas
	struct TipoItem Item;
	
	//Pilha 01
	struct TipoPilha p1, p2;
	IniciarPilhaVazia(&p1);
	
//Modo 01 de definir os itens	
	//Definindo itens e adicionando à pilha p1
		Item = {1, 'p'};
		Empilhar(Item, &p1);
	//Definindo itens e adicionando à pilha p1
		Item = {2, 'x'};
		Empilhar(Item, &p1);
	//Definindo itens e adicionando à pilha p1
		Item = {3, 'p'};
		Empilhar(Item, &p1);
	//Definindo itens e adicionando à pilha p1
		Item = {4, 'x'};
		Empilhar(Item, &p1);
		
	//Imprimindo p1
	imprimirPilha(p1);
	
//-------------------- Teste 01 --------------------//
	printf("\n\nTeste ( 01 )");
	
	if(verificarPadraoXP(p1)){
		printf("\n\nA Pilha possui o padrao");
	}else{
		printf("\n\nA pilha NAO possui o padrao");
	}
	
	LimparTela();
//------------------ Fim Teste 01 ------------------//
	

//-------------------- Teste 02 --------------------//

	printf("\n\nTeste ( 02 )");
	
	//Reiniciando p1 para evitar erros de pilha
	IniciarPilhaVazia(&p1);
	//Iniciando p2 como vazia
	IniciarPilhaVazia(&p2);

//Modo 02 de definir os itens	
	//Definindo itens e adicionando à pilha p1 Novamente
		Item.Caractere = 'b';
		Item.Chave = 1;
		Empilhar(Item, &p1);
	//Definindo itens e adicionando à pilha p1 Novamente
		Item.Caractere = 'o';
		Item.Chave = 2;
		Empilhar(Item, &p1);
	//Definindo itens e adicionando à pilha p1 Novamente
		Item.Caractere = 'b';
		Item.Chave = 3;
		Empilhar(Item, &p1);
	//Definindo itens e adicionando à pilha p2
		Item.Caractere = 'b';
		Item.Chave = 1;
		Empilhar(Item, &p2);
	//Definindo itens e adicionando à pilha p2
		Item.Caractere = 'o';
		Item.Chave = 2;
		Empilhar(Item, &p2);
	//Definindo itens e adicionando à pilha p2
		Item.Caractere = 'b';
		Item.Chave = 3;
		Empilhar(Item, &p2);
	
	//Imprimindo p1
	imprimirPilha(p1);
	//Imprimindo p2
	imprimirPilha(p2);
	
	if(compararPilhas(p1, p2) > 0){
		printf("\n\nAs Pilhas sao Iguais");
	}else{
		printf("\n\nAs pilhas NAO sao Iguais");
	}
	
	LimparTela();
//------------------ Fim Teste 02 ------------------//

//-------------------- Teste 03 --------------------//
	
	printf("\n\nTeste ( 03 )\n");
	
	//Pegando a string digitada de forma direta na função
	//Evitando fgets para teste
	if(verificarPalindromo("subinoonibus")){
		printf("\nE um palindromo");
	}else{
		printf("\nNAO e um palindromo");
	}
	
	LimparTela();
//------------------ Fim Teste 03 ------------------//

//-------------------- Teste 04 --------------------//
	
	printf("\n\nTeste ( 04 )\n");
	
	//Definindo o item de busca
	struct TipoItem itemDeBusca;
	itemDeBusca.Caractere = 'x';
	
	//Utilizando termos de p1
	IniciarPilhaVazia(&p1);
	//Definindo itens novamente, pois foram removidos no ultimo teste
	Item = {0, 'p'}; Empilhar(Item, &p1);
	Item = {0, 'i'}; Empilhar(Item, &p1);
	Item = {0, 'x'}; Empilhar(Item, &p1);
	Item = {0, 'e'}; Empilhar(Item, &p1);
	Item = {0, 'l'}; Empilhar(Item, &p1);
	
	//Armazenando o resultado do endereço obtido pela função
	TipoApontador Endereco = posicaoItem(itemDeBusca, p1);
	
	if(Endereco != NULL){
		printf("\nEndereco referente ao item: [ %c ], está presente na posicao de memoria: [ %p ]\n",Endereco->Item.Caractere, Endereco);
	}else{
		printf("\nItem: [ %c ], não encontrado...", Endereco->Item.Caractere);
	}
	
	LimparTela();
//------------------ Fim Teste 04 ------------------//

//-------------------- Teste 05 --------------------//

	printf("\n\nTeste ( 05 )\n");
	
	imprimirPilha(p1);
	
	if(verificarSeCrescente(p1)){
		printf("\n\nA pilha tem ordem crescente");
	}else{
	printf("\n\nA pilha NAO tem ordem crescente");
	}
	
	LimparTela();
//------------------ Fim Teste 05 ------------------//

//-------------------- Teste 6 --------------------//

	printf("\n\nTeste ( 06 )\n");
	
	//Utilizando termos de p1
	IniciarPilhaVazia(&p1);
	//Definindo itens novamente, pois foram removidos no ultimo teste
	Item = {0, 'p'}; Empilhar(Item, &p1);
	Item = {1, 'i'}; Empilhar(Item, &p1);
	Item = {2, 'x'}; Empilhar(Item, &p1);
	Item = {3, 'e'}; Empilhar(Item, &p1);
	Item = {4, 'l'}; Empilhar(Item, &p1);
	
	//Utilizando termos de p1
	IniciarPilhaVazia(&p2);
	//Definindo itens novamente, pois foram removidos no ultimo teste
	Item = {3, 'T'}; Empilhar(Item, &p2);
	Item = {4, 'i'}; Empilhar(Item, &p2);
	Item = {5, 'm'}; Empilhar(Item, &p2);
	Item = {6, 'e'}; Empilhar(Item, &p2);
	Item = {7, 's'}; Empilhar(Item, &p2);
	
	itemDeBusca.Caractere = 'x';
	
	imprimirPilha(p1); printf("\n");
	imprimirPilha(p2); printf("\n");
	
	if(verificarPresencaDeItem(itemDeBusca, p1,p2)){
		printf("\nO item consta nas duas pilhas");
	}else{
		printf("\nO item NAO consta nas duas pilhas");
	}
	
	LimparTela();
//------------------ Fim Teste 06 ------------------//

//-------------------- Teste 07 --------------------//

	printf("\n\nTeste ( 07 )\n");
	
	//Definindo itens novamente, pois foram removidos no ultimo teste
	IniciarPilhaVazia(&p1);
	Item = {0, 'M'}; Empilhar(Item, &p1);
	Item = {1, 'a'}; Empilhar(Item, &p1);
	Item = {2, 'r'}; Empilhar(Item, &p1);
	Item = {3, 'i'}; Empilhar(Item, &p1);
	Item = {4, 'a'}; Empilhar(Item, &p1);
	
	imprimirPilha(p1);
		printf("\nPila antes da remoção de vogais: ");
	retirarVogais(&p1);
		printf("\nPilha apos a remoção de vogais: ");
	imprimirPilha(p1);
	
	LimparTela();
//------------------ Fim Teste 07 ------------------//

//-------------------- Teste 08 --------------------//

	printf("\n\nTeste ( 08 )\n");
	
	//Testando novo item em uma pilha
	TipoItem newItem = {9, 'y'};
	
	//Definindo itens novamente, pois foram removidos no ultimo teste
	IniciarPilhaVazia(&p1);
	Item = {0, 'Z'}; Empilhar(Item, &p1);
	Item = {1, 'i'}; Empilhar(Item, &p1);
	Item = {2, 'n'}; Empilhar(Item, &p1);
	Item = {3, 'c'}; Empilhar(Item, &p1);
	Item = {4, 'o'}; Empilhar(Item, &p1);
	
	printf("\n");
	imprimirPilha(p1);
	
	//Testando com esses parâmetros, do topo pra base
	furarPilha(&p1, p1.Topo->Prox->Prox->Prox, newItem);
	
	printf("\n");
	imprimirPilha(p1);
	
	LimparTela();
//------------------ Fim Teste 08 ------------------//

//-------------------- Teste 09 --------------------//

	printf("\n\nTeste ( 09 )\n");
	
	const char str[] = "GATO DE BOTAS";
	printf("\nTexto original: %s", str);
	printf("\nTexto espelhado: "); espelharPalavras(str);
	
	LimparTela();
//------------------ Fim Teste 09 ------------------//

//-------------------- Teste 10 --------------------//

	
	printf("\n\nTeste ( 10 )\n");
	
	//Definindo uma lista estatica
	struct TipoLista ListaEstatica;
	initVoidList(&ListaEstatica);
	
	//Inserindo dados
	struct TipoItem itemLista; 
	itemLista = {0, 'A'};
	insert(itemLista, &ListaEstatica);
	
	itemLista = {1, 'L'};
	insert(itemLista, &ListaEstatica);
	
	itemLista = {2, 'E'};
	insert(itemLista, &ListaEstatica);
	
	itemLista = {3, 'C'};
	insert(itemLista, &ListaEstatica);
	
	itemLista = {4, 'R'};
	insert(itemLista, &ListaEstatica);
	
	itemLista = {5, 'I'};
	insert(itemLista, &ListaEstatica);
	
	itemLista = {6, 'M'};
	insert(itemLista, &ListaEstatica);
	
	//Imprimindo o primeiro estado da lista e Reiniciando p1 para uso
	impress(ListaEstatica);
	
	inverterListaComPilha(&ListaEstatica, &p1);
	
	impress(ListaEstatica);
	
	LimparTela();
//------------------ Fim Teste 10 ------------------//
}

