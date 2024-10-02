#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Definindo um ponteiro responsável por apontar uma struct de TipoCelula
typedef struct TipoCelula *TipoApontador;

struct TipoItem{
	int cod;
	char descricao[100];
	int ano;
	float valor;
};

/*Agora TipoCelula possui 2 ponteiros, um apontará 
  para a proxima lista e um para a anterior*/
struct TipoCelula{
	struct TipoItem item;
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

void inserir(TipoItem novoItem, TipoLista *lista){
	lista->ultimo->prox = (TipoApontador)malloc(sizeof(TipoCelula));
	
	/*Principal diferença na função insere em relação a lista somente 
	  encadeada, onde a celula criada na posicao ant, receberá um apontador
	  que aponta para "ultimo" em lista, ou seja, na posicao anterior a ela*/
	  lista->ultimo->prox->ant = lista->ultimo;
	  
	  lista->ultimo = lista->ultimo->prox;
	  lista->ultimo->item = novoItem;
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
			printf("\n\t| Codigo: %i", auxiliar->item.cod);
			printf("\n\t| Descricao: %s", auxiliar->item.descricao);
			printf("\n\t| Ano: %i", auxiliar->item.ano);
			printf("\n\t| Ano: %f", auxiliar->item.valor);
			
			auxiliar = auxiliar->prox;
		}
	}else //Se a direcao apontada for a partir do final (f)...
		if(direcao_lista == 'f'){
		
		//Outra mudança é por aqui...
		auxiliar = lista.ultimo;
		while(auxiliar != lista.primeiro){
			printf("\n\t ___________________________________");
			printf("\n\t| Codigo: %i", auxiliar->item.cod);
			printf("\n\t| Descricao: %s", auxiliar->item.descricao);
			printf("\n\t| Ano: %i", auxiliar->item.ano);
			printf("\n\t| Ano: %f", auxiliar->item.valor);
			
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

void inserirAposMaisNovo(TipoLista *lista, TipoItem itemX){
	
    TipoApontador aux = (TipoApontador)malloc(sizeof(TipoCelula));
    
    if(aux == NULL){
        printf("Erro ao alocar memória!\n");
        return;
    }

    TipoApontador p = lista->primeiro->prox;
    if(p == NULL){
        printf("Lista vazia!\n");
        free(aux);
        return;
    }

    int ano = p->item.ano;

    while(p != NULL){
        if(p->item.ano > ano) {
            ano = p->item.ano;
        }
        p = p->prox;
    }

    aux->item = itemX;

    p = lista->primeiro->prox;
    while(p != NULL) {
        if(p->item.ano == ano) {
            aux->prox = p->prox;
            aux->ant = p;
            if(p->prox != NULL) {
                p->prox->ant = aux;
            }
            p->prox = aux;

            if(p == lista->ultimo) {
                lista->ultimo = aux;
            }
            return;
        }
        p = p->prox;
    }

    free(aux);
}
	
int main(void){
	
	//Criando lista duplamente encadeada
	struct TipoLista lista1;
	iniciarListaVazia(&lista1);
	
	struct TipoItem item;
	
	
	//Inserindo dados
	item.cod = 1;
	item.ano = 2004;
	item.valor = 14.000;
	strcpy(item.descricao, "Corsa 3");
	inserir(item, &lista1);
	
	//Inserindo dados
	item.cod = 1;
	item.ano = 20022;
	item.valor = 13.000;
	strcpy(item.descricao, "Corsa 2");
	inserir(item, &lista1);
	
	//Inserindo dados
	item.cod = 1;
	item.ano = 1999;
	item.valor = 11.000;
	strcpy(item.descricao, "Corsa");
	inserir(item, &lista1);
	
	inserirAposMaisNovo(&lista1, item);
}
