#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Definindo um ponteiro responsável por apontar uma struct de TipoCelula
typedef struct TipoCelula *TipoApontador;

struct TipoFilme{
	char titulo[50];
	char categoria[20];
	float critica;
};

/*Agora TipoCelula possui 2 ponteiros, um apontará 
  para a proxima lista e um para a anterior*/
struct TipoCelula{
	struct TipoFilme filme;
	TipoApontador prox, ant;
};

struct TipoLista{
	TipoApontador primeiro, ultimo;
};


//-------------------CRUD----------------------//

void iniciarListaVazia(TipoLista *lista){
	lista->primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
	lista->ultimo = lista->primeiro;
	
	/*Principal diferença entre a lista somente encadeada, agora o 
	 ponteiro ant, recebe NULL pois não há nada antes desta célula*/
	lista->primeiro->ant = NULL;
	
	lista->primeiro->prox = NULL;
}

void inserir(TipoFilme novoFilme, TipoLista *lista){
	lista->ultimo->prox = (TipoApontador)malloc(sizeof(TipoCelula));
	
	/*Principal diferença na função insere em relação a lista somente 
	  encadeada, onde a celula criada na posicao ant, receberá um apontador
	  que aponta para "ultimo" em lista, ou seja, na posicao anterior a ela*/
	  lista->ultimo->prox->ant = lista->ultimo;
	  
	  lista->ultimo = lista->ultimo->prox;
	  lista->ultimo->filme = novoFilme;
	  lista->ultimo->prox = NULL;
}

int isVoid(TipoLista lista){
	return(lista.primeiro == lista.ultimo);
}

 void imprimir(TipoLista lista, char direcao_lista){
	TipoApontador auxiliar;
	
	//Se a direcao apontada for a partir do inicio (i)...
	if(direcao_lista == 'i'){
		
		auxiliar = lista.primeiro->prox;
		while(auxiliar != NULL){
			printf("\n\t ___________________________________");
			printf("\n\t| Titulo: %s", auxiliar->filme.titulo);
			printf("\n\t| Categoria: %s", auxiliar->filme.categoria);
			printf("\n\t| Crítica(IMDB): %.1f/10\n\n", auxiliar->filme.critica);
			
			auxiliar = auxiliar->prox;
		}
	}else //Se a direcao apontada for a partir do final (f)...
		if(direcao_lista == 'f'){
		
		//Outra mudança é por aqui...
		auxiliar = lista.ultimo;
		while(auxiliar != lista.primeiro){
			printf("\n\t ___________________________________");
			printf("\n\t| Titulo: %s", auxiliar->filme.titulo);
			printf("\n\t| Categoria: %s", auxiliar->filme.categoria);
			printf("\n\t| Crítica(IMDB): %.1f/10\n\n", auxiliar->filme.critica);
			
			auxiliar = auxiliar->ant;
		}
	}
}

/*Outra particularidade é nesta função, onde devemos dar um tipo de tratamento especial*/
void remover(TipoApontador posicao, TipoLista *lista){
	
	//Se a lista estiver vazia ou a posição for nula
	if(isVoid(*lista) || posicao == NULL || posicao == lista->primeiro){
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

//Função que pega a posicao de uma célula baseado no titulo
TipoApontador pegarPosicao(TipoLista lista, const char *parametroTitulo){
	TipoApontador auxiliar = lista.primeiro->prox;
	
	TipoApontador posicao;
	
	while(auxiliar != NULL){
		if(strcmp(auxiliar->filme.titulo, parametroTitulo) == 0){
			posicao = auxiliar;
		}
		auxiliar = auxiliar->prox;
	}
	return posicao;
}

//Função que altera um elemento filme apontado pela posicao
void alterarElemento(TipoLista *lista, TipoApontador posicao, TipoFilme *parametroFilme){
	TipoApontador auxiliar = lista->primeiro->prox;
	
	while(auxiliar != NULL){
		
		if(posicao == NULL){
			printf("\nLista vazia ou não inicializada...");
			return;
		}
		
		if(posicao == auxiliar){
			auxiliar->filme = *parametroFilme;
		}
		auxiliar = auxiliar->prox;
	}
}

//Função que insere o item após a posicao passada como parâmetro
void inserirPorPosicao(TipoApontador posicao, TipoLista *lista, TipoFilme filmeParametro){
	TipoApontador auxiliar = lista->primeiro->prox;
	
	while(auxiliar != NULL){
		if(posicao == NULL){
			printf("\nLista vazia ou não inicializada...");
			return;
		}
		
		if(posicao == auxiliar->prox){
			inserir(filmeParametro, lista);
		}
		auxiliar = auxiliar->prox;
	}
}
int main(void){
	
	//TipoApontador p;
	
	
	//Criando lista duplamente encadeada
	TipoLista lista1;
	iniciarListaVazia(&lista1);
	
	TipoFilme filme;
	
	//Inserindo Elementos ao final da lista
	strcpy(filme.titulo, "Pets");
	strcpy(filme.categoria, "Animacao/comedia");
	filme.critica = 6.5;
	inserir(filme, &lista1);
	
	strcpy(filme.titulo, "Gato de Botas 2");
	strcpy(filme.categoria, "Animacao/Aventura");
	filme.critica = 7.8;
	inserir(filme, &lista1);
	
	strcpy(filme.titulo, "Encanto");
	strcpy(filme.categoria, "Animacao/Aventura");
	filme.critica = 7.2;
	inserir(filme, &lista1);
	
	strcpy(filme.titulo, "Joker");
	strcpy(filme.categoria, "Suspense/Drama");
	filme.critica = 8.4;
	inserir(filme, &lista1);
	
	strcpy(filme.titulo, "godzilla vs kong");
	strcpy(filme.categoria, "Ação/Ficcao");
	filme.critica = 6.3;
	inserir(filme, &lista1);
	
	strcpy(filme.titulo, "Interestelar");
	strcpy(filme.categoria, "Ficcao/aventura");
	filme.critica = 8.7;
	inserir(filme, &lista1);

	//Removendo um item apontado por uma posicao, achada baseado no título
	
	//Primeiro vamos achar a posicao do elemento
	TipoApontador posicao = pegarPosicao(lista1, "Encanto");
	
	//Agora removemos com a função remover
	remover(posicao, &lista1);
	
	//Mostrando elementos na ordem de padrão
	printf("\n____________| Filmes em ordem Padrao |____________\n");
	printf("\nLista {\n\n");
		imprimir(lista1, 'i');
	printf("\n}\n\n");
	
	//Alterar um filme apontado pela posicao
	
	//primeiro pegando a posicao com a função anterior
	TipoApontador posicaoAlterar = pegarPosicao(lista1, "godzilla vs kong");
	
	//Agora definindo o conjunto de dados que será incrementado na posicao 
	strcpy(filme.titulo, "Barbie");
	strcpy(filme.categoria, "Comedia/Fantasia");
	filme.critica = 6.8;
	
	alterarElemento(&lista1, posicaoAlterar, &filme);
	
	//Mostrando elementos na ordem inversa
	printf("\n____________| Filmes na ordem Inversa |____________\n");
	printf("\nLista {\n\n");
		imprimir(lista1, 'i');
	printf("\n}\n\n");
	
}
