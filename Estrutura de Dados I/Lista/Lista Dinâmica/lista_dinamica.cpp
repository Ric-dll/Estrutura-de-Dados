#include<stdio.h>
#include<string.h>
#include<cstdlib>
#include<float.h>

typedef struct TipoCelula *TipoApontador;

struct TipoItem{
    int codigo;
    char descricao[100];
    float valor;
};

struct TipoCelula{
    struct TipoItem item;
    TipoApontador prox;
};

struct TipoLista{
    TipoApontador primeiro, ultimo;
};

void initVoidList(TipoLista *lista){
    lista->primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

int isVoidList(TipoLista lista){
    return(lista.primeiro == lista.ultimo);
}

void inserirDados(TipoLista *lista, TipoItem novoItem){
    lista->ultimo->prox = (TipoApontador)malloc(sizeof(TipoCelula));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->item = novoItem;
    lista->ultimo->prox = NULL;
}

void remove(TipoApontador posicao, TipoLista *lista, TipoItem *itemParaRemocao){
    TipoApontador temp;
    if(isVoidList(*lista) || posicao==NULL || posicao->prox == NULL){
        printf("ERRO! Lista vazia ou a posicao nao existe");
        return;
    }
    temp = posicao->prox;
    *itemParaRemocao = temp->item;
    posicao->prox = temp->prox;
    if(posicao->prox == NULL){
        lista->ultimo = posicao;
    }
    free(temp);
}

void impress(TipoLista lista){
    TipoApontador auxiliar;
    auxiliar = lista.primeiro->prox;
    while(auxiliar != NULL){
        printf("\t ___________________________\n\t|");
        printf("\n\t|Codigo: %i", auxiliar->item.codigo);
        printf("\n\t|Descricao: %s", auxiliar->item.descricao);
        printf("\n\t|Valor: %.2f\n", auxiliar->item.valor);
        auxiliar = auxiliar->prox;
        printf("\t|___________________________\n");
    }
}

TipoApontador funcao_A(TipoLista lista, const char *ParametroDescricao){
    TipoApontador auxiliar = lista.primeiro->prox;
    TipoApontador p=NULL;
    while(auxiliar != NULL){
        if(strcmp(auxiliar->item.descricao, ParametroDescricao) == 0){
            p = auxiliar;
        }
        auxiliar = auxiliar->prox;
    }
    return p;
}

TipoApontador funcao_B(TipoLista lista, int ParametroCodigo){
    TipoApontador auxiliar = lista.primeiro->prox;
    TipoApontador p=NULL;
    while(auxiliar != NULL){
        if(auxiliar->item.codigo == ParametroCodigo){
            p = auxiliar;
        }
        auxiliar = auxiliar->prox;
    }
    return p;
}

TipoApontador retornaEnderecoPorValor(TipoLista lista, float ParametroVal){
    TipoApontador auxiliar = lista.primeiro->prox;
    TipoApontador posicao=NULL;
    while(auxiliar != NULL){
        if(auxiliar->item.valor == ParametroVal){
            posicao = auxiliar;
        }
        auxiliar = auxiliar->prox;
    }
    return posicao;
}

float funcao_C(TipoLista lista){
    TipoApontador auxiliar = lista.primeiro->prox;
    float somaValItens = 0;
    while(auxiliar != NULL){
        somaValItens += auxiliar->item.valor;
        auxiliar = auxiliar->prox;
    }
    return somaValItens;
}

int funcao_D(TipoLista lista1, TipoLista lista2){
    TipoApontador auxiliar;
    int tam1 = 0, tam2 = 0;
    auxiliar = lista1.primeiro->prox;
    while(auxiliar != NULL){
        if( ( (auxiliar->item.codigo) % 2) == 0){
            tam1++;
        }
        auxiliar = auxiliar->prox;
    }
    auxiliar = lista2.primeiro->prox;
    while(auxiliar != NULL){
        if( ( (auxiliar->item.codigo) % 2) == 0){
            tam2++;
        }
        auxiliar = auxiliar->prox;
    }
    if(tam1 > tam2){
        return 1;
    }else if(tam2 > tam1){
        return 2;
    }else{
        return 0;
    }
}

void funcao_E(TipoLista *lista, TipoApontador posicao, TipoItem novoItem){
    if(posicao == NULL){
        printf("\nPosicao Inexistente");
        return;
    }else if(posicao->prox == NULL){
        inserirDados(lista, novoItem);
    }else{
        TipoApontador p_prox;
        p_prox = posicao->prox;
        posicao->prox = (TipoApontador)malloc(sizeof(TipoCelula));
        posicao->prox->prox = p_prox;
        posicao->prox->item = novoItem;
    }
}

void funcao_F(TipoLista *lista, TipoApontador p, TipoApontador q){
    TipoItem itemAuxiliar = p->item;
    p->item = q->item;
    q->item = itemAuxiliar;
}

void funcao_G(TipoLista *lista, TipoItem itemParametro){
    lista->primeiro->item = itemParametro;
    TipoApontador novaCelulaCabeca = (TipoApontador)malloc(sizeof(TipoCelula));
    novaCelulaCabeca->prox = lista->primeiro;
    lista->primeiro = novaCelulaCabeca;
}

void funcao_H(TipoApontador posicaoPassada, TipoLista *lista, TipoItem *itemParaRemocao){
    if(posicaoPassada == NULL || lista->primeiro == NULL){
        printf("\nPosicao inexistente ou lista Vazia!...");
        return;
    }
    if(lista->primeiro == posicaoPassada){
        lista->primeiro = posicaoPassada->prox;
        if(lista->primeiro == NULL){
            lista->ultimo = NULL;
        }
    }else{
        TipoApontador anterior = lista->primeiro;
        while(anterior != NULL && anterior->prox != posicaoPassada){
            anterior = anterior->prox;
        }
        if(anterior == NULL){
            printf("\nPosicao nao encontrada!...");
            return;
        }
        anterior->prox = posicaoPassada->prox;
        if(posicaoPassada == lista->ultimo){
            lista->ultimo = anterior;
        }
    }
    *itemParaRemocao = posicaoPassada->item;
    free(posicaoPassada);
}

void funcao_I(TipoLista *lista){
    TipoApontador auxiliar = lista->primeiro->prox;
    TipoApontador posicaoInicial = lista->primeiro;
    while(auxiliar != NULL){
        if(auxiliar->item.valor < posicaoInicial->item.valor){
            posicaoInicial = auxiliar;
        }
        auxiliar = auxiliar->prox;
    }
    TipoItem itemAuxiliar;
    itemAuxiliar = posicaoInicial->item;
    posicaoInicial->item = lista->primeiro->item;
    lista->primeiro->item = itemAuxiliar;
}

int funcao_J(TipoLista lista1, TipoLista lista2){
	TipoApontador auxiliar;
	int tam1 = 0, tam2 = 0;

    auxiliar = lista1.primeiro->prox;
	while(auxiliar != NULL){
		tam1++;
		auxiliar = auxiliar->prox;
	}

	auxiliar = lista2.primeiro->prox;
	while(auxiliar != NULL){
		tam2++;
		auxiliar = auxiliar->prox;
	}
	
	if(tam1 > tam2){
		return 1;
	}else 
		if(tam2 > tam1){
			return 2;
	}else{
		return 0;
	}
}

int funcao_K(TipoLista lista){
	if(lista.primeiro->prox == NULL){
		return 1;
	}

	TipoApontador auxiliar = lista.primeiro->prox;
	float valAtual = auxiliar->item.valor;
	
	while(auxiliar != NULL){
		if(auxiliar->item.valor < valAtual){
			return 0;
		}
		valAtual = auxiliar->item.valor;
		auxiliar = auxiliar->prox;
	}
	return 1;
}

void funcao_L(TipoLista *lista){
	if(isVoidList(*lista)){
		printf("\nLista vazia!...");
		return;
	}
	
	TipoApontador auxiliar = lista->primeiro->prox;
	TipoApontador posicao_Do_Menor = NULL;
	float menor = FLT_MAX;	
	
	while(auxiliar != NULL){
		if(auxiliar->item.valor < menor){
			menor = auxiliar->item.valor;
			posicao_Do_Menor = auxiliar;
		}
		auxiliar = auxiliar->prox;
	}
	
	if(posicao_Do_Menor == NULL){
		printf("\nErro ao encontrar o menor item!...");
		return;
	}
	
	if(posicao_Do_Menor != lista->primeiro->prox){
		TipoItem itemRemovido;
		funcao_H(posicao_Do_Menor, lista, &itemRemovido);
		funcao_G(lista, itemRemovido);
		printf("Item com menor valor movido para o início da lista.\n");
		
	}else{
		printf("O item com menor valor já está no início da lista.\n");
	}
}

TipoLista funcao_M(TipoLista *lista1, TipoLista *lista2){
	TipoLista novaLista;
	initVoidList(&novaLista);
	TipoApontador auxiliar;
	TipoItem ItemCopiado;
	
	auxiliar = lista1->primeiro->prox;
	while(auxiliar != NULL){
		ItemCopiado = auxiliar->item;
		inserirDados(&novaLista, ItemCopiado);
		auxiliar = auxiliar->prox;
	}
	
	auxiliar = lista2->primeiro->prox;
	while(auxiliar != NULL){
		ItemCopiado = auxiliar->item;
		inserirDados(&novaLista, ItemCopiado);
		auxiliar = auxiliar->prox;
	}
	return novaLista;
}

TipoLista funcao_N(TipoLista *lista1, TipoLista *lista2){
	TipoLista novaLista;
	initVoidList(&novaLista);
	TipoApontador auxiliar;
	TipoItem ItemCopiado;
	
	auxiliar = lista1->primeiro->prox;
	while(auxiliar != NULL){
		if((auxiliar->item.codigo)%2 != 0){
			ItemCopiado = auxiliar->item;
			inserirDados(&novaLista, ItemCopiado);
		}
		auxiliar = auxiliar->prox;
	}
	
	auxiliar = lista2->primeiro->prox;
	while(auxiliar != NULL){
		if((auxiliar->item.codigo)%2 != 0){
			ItemCopiado = auxiliar->item;
			inserirDados(&novaLista, ItemCopiado);
		}
		auxiliar = auxiliar->prox;
	}
	return novaLista;
}

TipoLista funcao_O(TipoLista *lista1, TipoLista *lista2){
	TipoLista novaLista;
	initVoidList(&novaLista);
	TipoApontador auxiliar1 = lista1->primeiro->prox;
	TipoApontador auxiliar2 = lista2->primeiro->prox;

	while(auxiliar1 && auxiliar2 != NULL){
		if(auxiliar1 != NULL){
			inserirDados(&novaLista, auxiliar1->item);
			auxiliar1 = auxiliar1->prox;
		}
		
		if(auxiliar2 != NULL){
			inserirDados(&novaLista, auxiliar2->item);
			auxiliar2 = auxiliar2->prox;
		}
	}
	return novaLista;
}

int main(void){
	
	//Criando listas e um item para auxiliar na inserção
	struct TipoLista lista1;
	struct TipoLista lista2;
	struct TipoItem item;
	TipoApontador p;
	//Iniciando a lista como vazia
	initVoidList(&lista1);
	initVoidList(&lista2);

	//Definindo os dados para a (lista 1)
	item.codigo = 01;
	strcpy(item.descricao, "Fusca Antigo");
	item.valor = 18000;
	//Inserindo dados na lista	
	inserirDados(&lista1, item);
	
	item.codigo = 02;
	strcpy(item.descricao, "Fusca Novo");
	item.valor = 12000;
	//Inserindo dados na lista	
	inserirDados(&lista1, item);
	
	item.codigo = 03;
	strcpy(item.descricao, "Chevrolet Camaro");
	item.valor = 240000;
	//Inserindo dados na lista	
	inserirDados(&lista1, item);
	
	item.codigo = 04;
	strcpy(item.descricao, "Fiat Uno");
	item.valor = 9000;
	//Inserindo dados na lista	
	inserirDados(&lista1, item);

	item.codigo = -04;
	strcpy(item.descricao, "Fiat Spin");
	item.valor = 120000;
	//Inserindo dados na lista	
	inserirDados(&lista1, item);
	
	//Definindo os dados para a (lista 2)
	item.codigo = 01;
	strcpy(item.descricao, "Honda Civic");
	item.valor = 70000;
	//Inserindo dados na lista	
	inserirDados(&lista2, item);
	
	item.codigo = 02;
	strcpy(item.descricao, "Toyota Supra");
	item.valor = 100000;
	//Inserindo dados na lista	
	inserirDados(&lista2, item);
	
	item.codigo = 03;
	strcpy(item.descricao, "Mercedes Bens");
	item.valor = 400000;
	//Inserindo dados na lista	
	inserirDados(&lista2, item);

	//imprimindo ambas as listas
	printf("\nLista 1 { \n\n");
		impress(lista1);
	printf("\n\n}\n");

	printf("\nLista 2 { \n\n");
		impress(lista2);
	printf("\n}\n\nPressione Enter para continuar...");
	
	getchar();
	system("clear");
	
	//Teste função A
	printf("\n_______ Teste Item A _______\n");
	//p retorna um tipo apontador de TipoCelula para descricao
	p = funcao_A(lista1, "Fusca Antigo");
	printf("\nDescricao: %s\n", p->item.descricao);
	printf("\n\nPressione Enter para continuar...");
	
	getchar();
	system("clear");
	
	//Teste função B
	printf("\n_______ Teste Item b _______\n");
	//p retorna um tipo apontador de TipoCelula para codigo
	p = funcao_B(lista1, 01);
	printf("\nCodigo: %i\n", p->item.codigo);
	printf("\n\nPressione Enter para continuar...");
	
	getchar();
	system("clear");

	printf("\n_______ Teste Item C _______\n");
	//Teste função C
	printf("\n%.2f\n", funcao_C(lista1));
	printf("\n\nPressione Enter para continuar...");
	getchar();
	system("clear");

	//Teste função D
	printf("\n_______ Teste Item D _______\n");
	printf("\n%i", funcao_D(lista1, lista2));
	printf("\n\nPressione Enter para continuar...");

	getchar();
	system("clear");

	//Teste função E
	printf("\n_______ Teste Item E _______\n");
	//Novo Item
	item.codigo = 23;
	strcpy(item.descricao, "Brasilia");
	item.valor = 25000;

	//posicao recebe a função B, que retorna o endereço de uma célula 
	TipoApontador posicao = funcao_B(lista1, 2);

	//Agora que possuimos a posição em sí, devido a função B, pode-se utilizar na função E
	funcao_E(&lista1, posicao, item);

	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
	
	//Teste função F

	//Receberão as posições para trocar de lugar em uma lista específica
	TipoApontador pos1, pos2;

	//Armazena a posicao 2
	pos1 = funcao_B(lista1, 2);
	//Armazena a posicao 3
	pos2 = funcao_B(lista1, 3);
	
	printf("\n_______ Teste Item F _______\n");

	//Realiza a troca de lugares entre pos1 e pos2 da lista 1
	funcao_F(&lista1, pos1, pos2);

	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função G
	
	printf("\n_______ Teste Item G _______\n");

	//Definindo um item diferente
	item.codigo = 77;
	strcpy(item.descricao, "Corsa antigo");
	item.valor = 18000;

	funcao_G(&lista1, item);

	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função H
	
	printf("\n_______ Teste Item H _______\n");

	//Remove a exata posicao passada e não a posterior
	
	//Supondo querer remover o item 77 adicionado em específico
	TipoApontador posicaoParaRemocao = funcao_B(lista1, 77);
	
	//Variável pra armazenar o item removido...
	TipoItem itemRemovido;
	
	funcao_H(posicaoParaRemocao, &lista1, &itemRemovido);

	printf("\nItem Removido: \n\nCódigo:%i\nDescricao: %s\nValor: %.2f\n", itemRemovido.codigo, itemRemovido.descricao, itemRemovido.valor);
	
	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função I
	printf("\n_______ Teste Item I _______\n");

	funcao_I(&lista1);
	
	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função J
	printf("\n_______ Teste Item J _______\n");
	
	printf("\n%i\n", funcao_J(lista1, lista2));
	printf("\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função K
	printf("\n_______ Teste Item K _______\n");
	
	printf("\n%i", funcao_K(lista2));
	printf("\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função L
	printf("\n_______ Teste Item L _______\n");
	
	funcao_L(&lista1);
	
	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");

	
	getchar();
	system("clear");

	//Teste Função M
	printf("\n_______ Teste Item M _______\n");
	
	TipoLista lista3 = funcao_M(&lista1, &lista2);
	
	printf("\nLista {\n\n");
		impress(lista3);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função N
	printf("\n_______ Teste Item N _______\n");
	
	TipoLista lista4 = funcao_N(&lista1, &lista2);
	
	printf("\nLista {\n\n");
		impress(lista4);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");

	//Teste Função O
	printf("\n_______ Teste Item O _______\n");
	
	TipoLista lista5 = funcao_O(&lista1, &lista2);
	
	printf("\nLista {\n\n");
		impress(lista5);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
}
