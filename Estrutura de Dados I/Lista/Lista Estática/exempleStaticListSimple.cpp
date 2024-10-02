#include<stdio.h>
#include<string.h>

struct Pessoa{
	char nome[100];
	char telefone[21]; //+55 (35) 99999-9999
};

struct Agenda{
	Pessoa contatos[20];
	int tamanho;
};

//Função pra inicializar a lista
//agenda é um ponteiro, e " -> "(aponta/seta) aponta pra tamanho na posição 0
void initVoidList(Agenda *agenda){
	agenda -> tamanho = 0;
}


//Função de inserção que recebe uma pessoa e uma agenda por referência
void insert(Pessoa p, Agenda *agenda){
	if(agenda -> tamanho >= 20){
	//Se agenda apontar para o tamanho e for maior ou igual o limite definido, então ...
	printf("Agenda cheia!..");
	return;
	}
	//Caso ainda não estiver cheia...

	//agenda que é um ponteiro está sendo "setada/apontada" para contatos, que é um vetor que analisa a posição como sendo agenda "setando" em tamanho que recebe o contato (p)
	agenda -> contatos[agenda -> tamanho] = p; //Inicialmente tamanho = 0
	agenda -> tamanho++; //agora tamanho = 1
}

//função de impressão
void impress(Agenda agenda){
	int i;
	for(i=0; i < agenda.tamanho; i++){
		printf("\n_________[Contato]_________\n");
		printf("\nNome: %s", agenda.contatos[i].nome);
		printf("\nTell: %s", agenda.contatos[i].telefone);
		printf("\n___________________________\n");
	}
}

//Função de excluir
void remove(Agenda *agenda, int posicao){
	int i;
	for(i=posicao; i<agenda->tamanho; i++){
		agenda->contatos[i] = agenda->contatos[i+1];
	}
	//Decrementando o tamanho
	agenda -> tamanho--;
}


int main(void){
	//criando variáveis de tipo Struct
	struct Pessoa p;
	struct Agenda agenda;

	//Iniciando lista pela chamada de função, que é um ponteiro, logo o & define a posição
	initVoidList(&agenda);

	//copiando os dados
	strcpy(p.nome, "Jonas");
	strcpy(p.telefone, "+55 (35) 9 1234-5678");
	insert(p, &agenda);


	strcpy(p.nome, "Vitinho");
	strcpy(p.telefone, "+55 (35) 9 9999-9999");
	insert(p, &agenda);

	//Teste de exclusão
	//remove(&agenda, 1);

	//chamando a impressão
	impress(agenda);
}
