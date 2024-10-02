#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cstdlib>
#include<float.h>

//Definições
#define MAX_TAM 1000

//------------------ Definindo Pilha Estatica------------------//
typedef int TipoApontador;
typedef int CodigoPilha;

//Definição TipoItem
struct TipoItem{
	CodigoPilha cod = 0;
	char itemEmpilhado;
};

//Definição TipoPilha
struct TipoPilha{
	TipoItem itens[MAX_TAM];
	TipoApontador topo;
};


//Criando e inicializando uma pilha vazia
void definirPilhaVazia(TipoPilha *pilha){
	pilha->topo = 0;
}

//Verificando se a pilha esta vazia
int isVoidStack(TipoPilha pilha){
	return(pilha.topo == 0);
}

//Função que empilha os itens na posição abaixo do apontador do topo
void empilharItem(TipoItem item, TipoPilha *pilha){
	if(pilha->topo == MAX_TAM){
		printf("\nERRO!, Pilha Vazia");
	}else{
		//O apontador do topo da pilha aponta para a casa de cima
		pilha->topo++;
		//Pilha que está na posicao abaixo do topo recebe o item passado
		pilha->itens[pilha->topo-1] = item;
		//pilha->itens[pilha->topo-1].cod = pilha->topo; //Funcionalidade especifica do item desde programa
	}
}

//Função que desempilha o item do topo-1, referenciando o item para apontar de forma certeira ao endereço
void desempilharItem(TipoPilha *pilha, TipoItem *item){
	//Usando (*) para desreferenciar (*pilha), para se adequar a função de verificação
	if(isVoidStack(*pilha)){
		printf("\nERRO!, Pilha Vazia");
	}else{
		//Desreferenciando o item para modificar o mesmo e não modificar o endereço 
		*item = pilha->itens[pilha->topo-1];
		pilha->topo--;
	}
}

//Verificando o tamanho da pilha
int sizeStack(TipoPilha pilha){
	return(pilha.topo);
}

void impressStack(TipoPilha pilha){
	for(int i = pilha.topo-1; i>=0; i--){
		printf("\n\t| %c | ", pilha.itens[i].itemEmpilhado);
		printf("- Cod: %i", pilha.itens[i].cod);
	}
}

//------------------ Fim definicao de Pilhas ------------------//

//------------------ Definindo Lista Dinamica ------------------//

typedef struct TipoCelula *ApontadorParaTipoCelula;

struct TipoCelula{
	struct TipoItem itemDaLista;
	ApontadorParaTipoCelula prox, ant; //Armazenara o endereço de outra celula
};

struct TipoLista{
	ApontadorParaTipoCelula primeiro, ultimo;
};

void initVoidList(TipoLista *lista){
    lista->primeiro = (ApontadorParaTipoCelula)malloc(sizeof(TipoCelula));
	lista->ultimo = lista->primeiro;
	
	/*Principal diferença entre a lista somente encadeada, agora o 
	 ponteiro ant, recebe NULL pois não há nada antes desta célula*/
	lista->primeiro->ant = NULL;
	
	lista->primeiro->prox = NULL;
}

int isVoidList(TipoLista lista){
    return(lista.primeiro == lista.ultimo);
}

void inserirDados(TipoLista *lista, TipoItem novoItem){
    lista->ultimo->prox = (ApontadorParaTipoCelula)malloc(sizeof(TipoCelula));
	
	/*Principal diferença na função insere em relação a lista somente 
	  encadeada, onde a celula criada na posicao ant, receberá um apontador
	  que aponta para "ultimo" em lista, ou seja, na posicao anterior a ela*/
	  lista->ultimo->prox->ant = lista->ultimo;
	  
	  lista->ultimo = lista->ultimo->prox;
	  lista->ultimo->itemDaLista = novoItem;
	  lista->ultimo->prox = NULL;
}

void remover(ApontadorParaTipoCelula posicao, TipoLista *lista){
	
	//Se a lista estiver vazia ou a posição for nula
	if(isVoidList(*lista) || posicao == NULL || posicao == lista->primeiro){
		printf("Há algo de errado com a lista!..."); 
		return;
	}
	
	//Se posicao em prox for nula, significa que ela é a ultima... logo:
	if(posicao->prox == NULL){
		
		//Então ultimo em lista, recebe a posicao anterior(posicao em ant)
		lista->ultimo = posicao->ant;
		
		//Entrando em lista e em ultimo, prox receberá NULL, significando que não há mais nada além
		lista->ultimo->prox = NULL;
		free(posicao);
	}else{ //Senão, o item provavelmente estará aos meios...
		
		//posicoa que aponta para a celula anterior, entrando em prox, recebe a posicao da próxima após a atual que será removida
		posicao->ant->prox = posicao->prox;
		//Faz o inverso da instrucao acima...
		posicao->prox->ant = posicao->ant;
		
		free(posicao);
	}
}

 void imprimir(TipoLista lista, char direcao_lista){
	ApontadorParaTipoCelula auxiliar;
	
	//Se a direcao apontada for a partir do inicio (i)...
	if(direcao_lista == 'i'){
		
		auxiliar = lista.primeiro->prox;
		while(auxiliar != NULL){
			printf("\n");
			printf("\n\t|Codigo: %i", auxiliar->itemDaLista.cod);
			printf("\n\t|Item: %c", auxiliar->itemDaLista.itemEmpilhado);
			auxiliar = auxiliar->prox;
			printf("\n");
		}
	}else //Se a direcao apontada for a partir do final (f)...
		if(direcao_lista == 'f'){
		
		//Outra mudança é por aqui...
		auxiliar = lista.ultimo;
		while(auxiliar != lista.primeiro){
			printf("\n");
			printf("\n\t|Codigo: %i", auxiliar->itemDaLista.cod);
			printf("\n\t|Item: %c", auxiliar->itemDaLista.itemEmpilhado);
			auxiliar = auxiliar->ant;
			printf("\n");
		}
	}
}


//------------------ Fim definicao de Lista dinamica ------------------//

void reiniciarTela(){
	printf("\n\nPressione Enter para continuar...");
	getchar();
	system("clear");
	printf("\nLISTA DE EXERCICIOS - PILHA ESTATICA\n");
}

//Item 01) Verificado paridade de '( )' Parenteses 
int verParidadeString(const char *str, TipoPilha *pilhaAuxiliar){
	
	struct TipoItem itemAux;
	
	//Armazena o tamanho da String e verifica se contem "\n" ao fim
	int tamString = strlen(str);
	if(str[tamString - 1] == '\n'){ //Se sim, então redimensiona
		tamString--;
	}
	
	//Verifica se a String está vazia
	if(str[0] == '\0'){
		printf("\nString Vazia!...");
		return 0;
	}else{
		for(int i=0; i<tamString; i++){
			// Compara caracteres com (
			if(str[i] == '('){ 
				empilharItem(itemAux, pilhaAuxiliar);
			}
			
			//Se houver algum caractere ) sem par correspondente
			if(str[i] == ')'){
				if(isVoidStack(*pilhaAuxiliar)){
					printf("\nErro: parentese fechado sem par correspondente!...");
                    return 0;
				}else{ //Caso não houver, irá parar logo acima, porem caso houver...
					desempilharItem(pilhaAuxiliar, &itemAux);
				}
			}
		}
	}
	return 1;
}

//Item 02) Montando uma pilha somente com as vogais de uma String de tamanho[50]
void empilharVogais(char palavra[50], TipoPilha *pilhaAuxiliar){
	
	const char *strVogais = "aeiouAEIOU";
	struct TipoItem itemAux;
	
	if(palavra[0] == '\0'){
		printf("\nString Vazia!...");
		return;
	}else{
		for(int i=0; i<50; i++){
			for(int j=0; j<10; j++){
				if(palavra[i] == strVogais[j]){
					itemAux.itemEmpilhado = palavra[i];
					itemAux.cod +=1; 
					empilharItem(itemAux, pilhaAuxiliar);
				}
			}
		}
		impressStack(*pilhaAuxiliar);
	}
}

//Item 03) Invertendo a ordem de uma String[50] com Pilha
void inverterString(char palavra[50], TipoPilha *pilhaAuxiliar){
	struct TipoItem itemAux;
	
	if(palavra[0] == '\0'){
		printf("\nString Vazia!...");
		return;
	}else{
		for(int i=0; palavra[i]!='\0' ; i++){
			itemAux.itemEmpilhado = palavra[i];
			empilharItem(itemAux, pilhaAuxiliar);
		}
	}
	printf("\nPalavra invertida: ");
	for(int i = pilhaAuxiliar->topo-1 ; i>=0; i--){
		printf("%c", pilhaAuxiliar->itens[i].itemEmpilhado);
	}
}

//Item 04) Verificando se duas pilhas são iguais 
int verificarIgualdadeDePilhas(TipoPilha pilha1, TipoPilha pilha2){
	
	//Verificando diferença por vazio
	if(isVoidStack(pilha1) && isVoidStack(pilha2)){
		printf("\nAmbas as Pilhas Vazias!... Adicione itens");
		return 0;
	}
	
	//Verificando diferença por tamanho
	if(sizeStack(pilha1) != sizeStack(pilha2)){
		printf("\nAs Pilhas possuem tamanhos diferentes, logo sao Diferentes!...");
		return 0;
	}else{
	
		//Se possuir o mesmo tamanho e !vazias -> entra no loop
		for(int i=0; i<pilha1.topo; i++){
			//Agora compara cada item, e se tambem houver algum diferente...
			if(pilha1.itens[i].itemEmpilhado != pilha2.itens[i].itemEmpilhado){
				return 0;
			}
		}
		//Caso passe por todos os testes e ainda estiver OK!
		return 1;
	}
}

//Função auxiliar que copia uma pilha pra outra, p1 manda e p2 recebe
void copiarPilha(TipoPilha *p1, TipoPilha *p2){
	
	struct TipoItem itemAux;
	//Como p2 já é um ponteiro, logo nao precisa de & na função
	definirPilhaVazia(p2);
	
	for(int i=0; i<p1->topo; i++){
		itemAux.itemEmpilhado = p1->itens[i].itemEmpilhado;
		empilharItem(itemAux, p2);
	}
	///printf("\nPilha copiada com Sucesso!...");
}

//Item 05) Função que insere um item abaixo de uma posição P
void erguePilha(TipoPilha *pilha, TipoApontador p, TipoItem item){
	
	//Testes de invalidacao
	if(p < 0 || p > pilha->topo){
		printf("\nErro! Posicao invalida...");
	}
	if(pilha->topo == MAX_TAM){
		
	}
	
	//Responsável por armazenar o restante da pilha a partir de 'p' para retornar após a adição
	struct TipoPilha pilhaAuxiliar;
	definirPilhaVazia(&pilhaAuxiliar);
	
	//Backup da pilha	
	copiarPilha(pilha, &pilhaAuxiliar);
	
	//Fazendo o topo da pilha ser a posição 'p' passada
	pilha->topo = p;
	
	//Empilhando item na posição 'p' desejada
	empilharItem(item, pilha);
	
	//Empilhando todos os itens partindo da posição 'p' da pilha copiada
	for(int i=p; i<pilhaAuxiliar.topo; i++){
		
		//Passando o item presente em pilhaAuxiliar para pilha
		empilharItem(pilhaAuxiliar.itens[i], pilha);
	}
}

//Item 06) Função que verifica a ordem composta na pilha, crescente ou decrescente utilizando desempilha
int isCrescente(TipoPilha *pilha){
	if(isVoidStack(*pilha)){
		return 1;
	}
	
	struct TipoPilha pilhaAux;
	definirPilhaVazia(&pilhaAux);
	
	copiarPilha(pilha, &pilhaAux);
	
	struct TipoItem itemAux;
	
	for(int i=0; i<pilhaAux.topo; i++){
		if(pilhaAux.itens[i].cod < pilhaAux.itens[i+1].cod){
			desempilharItem(&pilhaAux, &itemAux);
		}else{
			return 0;
		}
	}
	
	return 1;
}

//Item 07) Função que verifica se um dado Item está presente em duas pilhas
int verificarSePossuiItem(TipoItem itemPassado, TipoPilha p1, TipoPilha p2){
	
	int verP1=0, verP2=0;
	
	for(int i=0; i<p1.topo; i++){
		if(itemPassado.itemEmpilhado == p1.itens[i].itemEmpilhado){
			verP1 = 1;
			break;
		}
	}
	
	for(int i=0; i<p2.topo; i++){
		if(itemPassado.itemEmpilhado == p2.itens[i].itemEmpilhado){ 
			verP2 = 1;
			break;
		}
	}
	
	if(verP1 && verP2){
		return 1;
	}else{
		return 0;
	}
}

//Função que inverte a ordem dos itens presentes na lista para a pilha
void inverterDaListaPraPilha(TipoLista *lista, TipoPilha *pilha){
	//Auxiliar que recebe a ultima posição em lista
	ApontadorParaTipoCelula auxiliar = lista->ultimo;
	
	//Enquanto auxiliar for diferente da primeira celula...
	while(auxiliar != lista->primeiro){
		//Empilhando os itens da lista na pilha
		empilharItem(auxiliar->itemDaLista, pilha);
		
		//Iterando...
		auxiliar = auxiliar->ant;
	}
}

//Função que separa vogais de consoantes em duas pilhas pela lista
void vogaisConsoantes(TipoLista *lista, TipoPilha *p1, TipoPilha *p2) {
    // Auxiliar que recebe onde a primeira célula de lista está
    ApontadorParaTipoCelula auxiliar = lista->primeiro->prox;

    char vogais[] = "aeiouAEIOU";

    // Neste caso auxiliar pode ser diferente de NULL pois percorre em ordem
    while(auxiliar != NULL) {
        int isVogal = 0;
        
        // Verificando se o caractere é uma vogal
        for(int i = 0; i < 10; i++) {
            if(auxiliar->itemDaLista.itemEmpilhado == vogais[i]) {
                isVogal = 1;
                break;
            }
        }

        if(isVogal){
            // Empilhar item na pilha de vogais
            empilharItem(auxiliar->itemDaLista, p1);
        }else{
            // Empilhar item na pilha de consoantes
            empilharItem(auxiliar->itemDaLista, p2);
        }
        // Iterando para a próxima célula
        auxiliar = auxiliar->prox;
    }
}

//Funcao Principal
int main(void){
	
	printf("\nLISTA DE EXERCICIOS - PILHA ESTATICA\n");
	
	//Criando a pilha vazia e o item
	struct TipoPilha pilha1;
	definirPilhaVazia(&pilha1);
	struct TipoItem item;
	
	printf("\nTeste de Empilhamento:\n");
	//Empilhando itens
	item.itemEmpilhado = 'a';
	empilharItem(item, &pilha1);
	
	item.itemEmpilhado = 'b';
	empilharItem(item, &pilha1);
	
	item.itemEmpilhado = 'c';
	empilharItem(item, &pilha1);
	
	//Imprimindo a pilha
	impressStack(pilha1);
	reiniciarTela();
	
//------------ Testando paridade - Item 01 ------------//
	struct TipoPilha pilhaTeste;
	definirPilhaVazia(&pilhaTeste);
	
	const char *str = "((X+Y)+Z)/2";
	
	printf("\nTeste - [ Item 01 ]\n");
	
	if(verParidadeString(str, &pilhaTeste)){
			printf("\nA string possui paridade equivalente...\n");
	}else{
		printf("\nA string NAO possui paridade equivalente...\n");
	}
	
//---------------- Fim Teste - Item 01 ----------------//

	reiniciarTela();

//------------ Testando Vogais  -  Item 02 ------------//]

	printf("\nTeste - [ Item 02 ]\n");
	char palavra[50] = "Jurubeba";
	empilharVogais(palavra, &pilhaTeste);

//---------------- Fim Teste - Item 02 ----------------//
	
	//Limpando a pilha
	definirPilhaVazia(&pilhaTeste);
	reiniciarTela();
	
//------------ Testando Inversao - Item 03 ------------//
	
	printf("\nTeste - [ Item 03 ]\n");
	inverterString(palavra, &pilhaTeste);

//---------------- Fim Teste - Item 03 ----------------//

	reiniciarTela();
	
//---------- Verificando Igualdade - Item 04 -----------//
	
	printf("\nTeste - [ Item 04 ]\n");
	//Definindo variaveis de teste
	struct TipoPilha pilha01, pilha02;
	definirPilhaVazia(&pilha01);
	definirPilhaVazia(&pilha02);
	
	//Utilizando a função de inverter String para teste
	//Para agilizar o processo de empilhamento
	
	char palavra01[50] = "abeburuJ";
	char palavra02[50] = "Jurubeba";
		
	inverterString(palavra01, &pilha01);
	inverterString(palavra02, &pilha02);
	
	printf("\n");
	
	if(verificarIgualdadeDePilhas(pilha01, pilha02) == 0){
		printf("\nAs Pilhas NAO sao iguais");
	}else{
		printf("\nAs Pilhas sao Iguais");
	}
	
//---------------- Fim Teste - Item 04 ----------------//

	reiniciarTela();

//--------- ADD item pela Posicao - Item 05 -----------//
	
	printf("\nTeste - [ Item 05 ]\n\n");
	printf("\nPilha 01 - Antes\n");
	impressStack(pilha01);

	//Novo item a ser inserido
	struct TipoItem itemDoMeio = {4, 's'};
	
	erguePilha(&pilha01, 4, itemDoMeio);
	
	printf("\n\nPilha Apos a insercao\n");
	impressStack(pilha01);
	
//---------------- Fim Teste - Item 05 ----------------//

	reiniciarTela();

//--------- ADD item pela Posicao - Item 06 -----------//
	printf("\nTeste - [ Item 06 ]\n");
	
	struct TipoPilha pilhaDecrescente;
	definirPilhaVazia(&pilhaDecrescente);
	
	item = {1, 'a'};
	empilharItem(item, &pilhaDecrescente);
	item = {2, 'b'};
	empilharItem(item, &pilhaDecrescente);
	item = {3, 'c'};
	empilharItem(item, &pilhaDecrescente);
	item = {1, 'd'};
	empilharItem(item, &pilhaDecrescente);
	
	impressStack(pilhaDecrescente);
	if(isCrescente(&pilhaDecrescente)){
		printf("\nA Pilha Possui ordem Crescente...");
	}else{
		printf("\nA Pilha NAO Possui ordem Crescente...");
	}

//---------------- Fim Teste - Item 06 ----------------//
	
	reiniciarTela();
	
//--------- ADD item pela Posicao - Item 07 -----------//
	
	printf("\nTeste - [ Item 07 ]\n");
	//Usando variaveis ja existentes pra teste
	//E limpando-as para adição de novos itens
	definirPilhaVazia(&pilha01);
	definirPilhaVazia(&pilha02);
	
	char palavra001[50] = "abeburuJ";
	inverterString(palavra001, &pilha01);
	
	char palavra002[50] = "abeburuJ";
	inverterString(palavra002, &pilha02);
	
	struct TipoItem itemTeste;
	itemTeste.itemEmpilhado = 'a';
	
	if(verificarSePossuiItem(itemTeste, pilha01, pilha02)){
		printf("\n\nO item '%c' esta presente em ambas as Pilhas", itemTeste.itemEmpilhado);
	}else{
		printf("\n\nO item '%c' NAO esta presente em ambas as Pilhas", itemTeste.itemEmpilhado);
	}
	
//---------------- Fim Teste - Item 07 ----------------//

	reiniciarTela();

//--------- Mesclando Listas dinamicas - Item 08/09 -----------//
	printf("\nTeste - [ Itens 08 - 09 ]\n");
	
	//Criando listas e um item para auxiliar na inserção
	struct TipoLista lista01;
	struct TipoPilha pilhaInvertida;
	
	//ApontadorParaTipoCelula p;
	//Iniciando a lista e pilha como vazia
	initVoidList(&lista01);
	definirPilhaVazia(&pilhaInvertida);
	
	//Definindo os dados para a (lista 1)
	item = {101, 'C'};
	inserirDados(&lista01, item);
	item = {102, 'a'};
	inserirDados(&lista01, item);
	item = {103, 'f'};
	inserirDados(&lista01, item);
	item = {104, 'e'};
	inserirDados(&lista01, item);
	item = {105, 'z'};
	inserirDados(&lista01, item);
	item = {106, 'i'};
	inserirDados(&lista01, item);
	item = {106, 'n'};
	inserirDados(&lista01, item);
	item = {107, 'h'};
	inserirDados(&lista01, item);
	item = {108, 'o'};
	inserirDados(&lista01, item);
	
	printf("\nImprimindo a lista: "); imprimir(lista01, 'i');
	
	//Invertendo a ordem na pilha
	printf("\nPilha invertida: \n");
	inverterDaListaPraPilha(&lista01, &pilhaInvertida);
	
	impressStack(pilhaInvertida);
	
	//Fazendo a separação de vogais e consoantes em duas pilhas
	struct TipoPilha pilhaVogais, pilhaConsoantes;
	definirPilhaVazia(&pilhaVogais);
	definirPilhaVazia(&pilhaConsoantes);
	
	//Chamando a função
	vogaisConsoantes(&lista01, &pilhaVogais, &pilhaConsoantes);
	
	printf("\n\nPilha de Vogais: \n");
	impressStack(pilhaVogais);
	
	printf("\n\nPilha de Vogais: \n");
	impressStack(pilhaConsoantes);
	
//---------------- Fim Teste - Item 08/09 ----------------//

}
