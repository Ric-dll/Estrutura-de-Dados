#include<stdio.h>
#include<string.h>
#include<cstdlib>
#include<float.h>
//Define uma variável tipoCelula referente a célula de memória criada posteriormente
//que fará o controle do início do ponteiro ao final...
typedef struct TipoCelula *TipoApontador;

//Definindo uma Struct de tipo item que será o item em sí da célula
struct TipoItem{
	int codigo;
	char descricao[100]; //= "";
	float valor;
};

//Definindo uma struct de tipo célula que armazenará o conteúdo
struct TipoCelula{
	//Bloco para armazenar as informações de um item na célula
	struct TipoItem item;
	
	//Bloco para armazenar a vinculação de outra celula
	TipoApontador prox;
};

//Uma struct de tipo lista para que possa armazenar a primeira celula e piscar na ultima
struct TipoLista{
	TipoApontador primeiro, ultimo;
};


//INICIO CRUD

	//Função que inicia a lista, vazia inicialmente
	void initVoidList(TipoLista *lista){
		//lista que aponta para a primeira posicao, recebe malloc(Uma nova alocacao)
		//sizeof mede o tamanho da struct de TipoCelula para alocar sempre novas de mesmo tamanho
		//(TipoApontador) é um cast, ou seja, um aviso que receberá um tipo específico, no caso apontador
		lista->primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
	
		//Como a lista está vazia, o primeiro e ultimo estão na mesma posicao, logo o ultimo recebe o primeiro
		lista->ultimo = lista->primeiro;
	
		//O prox da celula recebe nulo pois não há mais nada a ser vinculado a partir dai.
		lista->primeiro->prox = NULL;
	}
	
	//Função que verifica se está vazia
	int isVoidList(TipoLista lista){
		return(lista.primeiro == lista.ultimo);
	}
	
	//Função que insere dados na lista dinâmica, utilizando o prox
	void inserirDados(TipoLista *lista, TipoItem novoItem){
		//lista aponta para ultima posicao, que aponta para o bloco prox responsável por atribuir uma nova chamada de malloc
		lista->ultimo->prox = (TipoApontador)malloc(sizeof(TipoCelula)); //Note que sempre aponta para o ultimo para alocação
	
		//O piscador ultimo da lista, recebe um novo valor apontado pela lista em ultimo e em prox...
		//Prox é o endereço de memória da alocação dinamica do outro bloco
		lista->ultimo = lista->ultimo->prox;
	
		//Item da lista, recebe o novo item na ultima posicao apontada
		lista->ultimo->item = novoItem;
	
		//lista aponta para o novo ultimo, que aponta para prox receber um valor nulo, simbolizando o ultimo item da lista, sem mais caminhos
		lista->ultimo->prox = NULL;
	}
	
	//Função para remover Celulas da lista, faz a remoção de um nó, sempre após a posição apontada por posicao
	//A posicao removida é sempre uma a frente do parâmetro passado posicao
	void remove(TipoApontador posicao, TipoLista *lista, TipoItem *itemParaRemocao){
		//Lembrando que é importante a utilização de ponteiros para que haja alterações no argumento original(main) passado para a função
		//Tipo Apontador auxiliar, que será utilizada para armazenar temporariamente a posição da célula a ser removida.
		TipoApontador temp;
	
		//Verifica se a lista está vazia, ou se a posicao é nula ou se a posicao em prox é nula...
		if(isVoidList(*lista) || posicao==NULL || posicao->prox == NULL){
			printf("ERRO! Lista vazia ou a posicao não existe");
			return;
		}//Caso estiver tudo correto...
	
		//temp recebe e armazena a o ponteiro para a celula que será removida...
		temp = posicao->prox;
	
		//O conteúdo do item armazenado na célula que será removida é copiado para a variável, permitindo que seja mantida uma referência do item removido
		//É necesário desreferenciá-lo, utilizando o * antes, para acessar o item ao qual ele aponta...
		*itemParaRemocao = temp->item;
	
		//A prox de posicao recebe a prox de temp
		//O ponteiro prox da célula em "posição" é atualizado para apontar para a célula seguinte à que foi removida, ignorando-a na lista
		posicao->prox = temp->prox;
	
		//Se a célula removida era a última da lista, atualiza o ponteiro ultimo da lista para apontar para a célula que agora é a última (a célula anterior à que foi removida)
		if(posicao->prox == NULL){
			lista->ultimo = posicao;
		}
	
		//Libera a memória ocupada pela célula removida
		free(temp);
	}
	
	//Função que imprime os dados 
	void impress(TipoLista lista){
		//Variável auxiliar para percorrer a lista
		TipoApontador auxiliar;
		
		//auxiliar recebe lista (que inicialmente só possui os dois ponteiros), no primeiro ponteiro, que aponta para prox(primeiro conjunto de dados da lista)
		auxiliar = lista.primeiro->prox;
		
		
		while(auxiliar != NULL){
			//printa o código do item
			printf("\t ___________________________\n\t|");
			printf("\n\t|Codigo: %i", auxiliar->item.codigo);
			printf("\n\t|Descricao: %s", auxiliar->item.descricao);
			printf("\n\t|Valor: %.2f\n", auxiliar->item.valor);
			
			//auxiliar recebe a próxima posição provinda da posição atual +1
			auxiliar = auxiliar->prox;
			printf("\t|___________________________\n");
		}
	}
	
//FIM CRUD

//Função que retorna a descrição de um item, baseado no retorno do endereço da célula(prox) de memória...
TipoApontador funcao_A(TipoLista lista, const char *ParametroDescricao){
	//auxiliar vai receber a o valor de "primeiro" na pirmeira lista(primeira celula vazia) que apnota para a prox dela
	TipoApontador auxiliar = lista.primeiro->prox;	
	//p está aguardando receber um endereço
	TipoApontador p=NULL;
	
	while(auxiliar != NULL){
		//compara se o atual da lista é igual ao passado por parametro
		if(strcmp(auxiliar->item.descricao, ParametroDescricao) == 0){
			p = auxiliar; //Armazena um bloco inteiro contendo todo o conteúdo
		}
		auxiliar = auxiliar->prox;
	}
	return p;
}


//Função que retorna o código de um item, baseado no retorno do endereco da célula(Prox) de memória...
TipoApontador funcao_B(TipoLista lista, int ParametroCodigo){
	//auxiliar recebe lista que aponta para prox em primeiro(Primeira celula esta vazia) então aponta para a prox dela
	TipoApontador auxiliar = lista.primeiro->prox;
	//p está aguardando receber um endereço
	TipoApontador p=NULL;
	
	while(auxiliar != NULL){
		//compara se o atual da lista é igual ao passado por parâmetro
		if(auxiliar->item.codigo == ParametroCodigo){
			p = auxiliar; //Armazena um bloco inteiro contendo todo o conteúdo
		}
		auxiliar = auxiliar->prox;
	}
	return p;
}

//Função que retorna o valor de um item, baseado no retorno do endereco da célula(Prox) de memória...
TipoApontador retornaEnderecoPorValor(TipoLista lista, float ParametroVal){
	//auxiliar recebe lista que aponta para prox em primeiro(Primeira celula esta vazia) então aponta para a prox dela
	TipoApontador auxiliar = lista.primeiro->prox;
	//p está aguardando receber um endereço
	TipoApontador posicao=NULL;
	
	while(auxiliar != NULL){
		//compara se o atual da lista é igual ao passado por parâmetro
		if(auxiliar->item.valor == ParametroVal){
			posicao = auxiliar; //Armazena um bloco inteiro contendo todo o conteúdo
		}
		auxiliar = auxiliar->prox;
	}
	return posicao;
}

//Função que recebe uma lista e retorna a soma do valor de todos os itens
float funcao_C(TipoLista lista){
	//Variável auxiliar para percorrer a lista, que recebe no primeiro ponteiro, o prox(que referencia a célula)....
	TipoApontador auxiliar = lista.primeiro->prox;
	
	//Variavel de soma
	float somaValItens = 0;
	
	//Inicia o loop
	while(auxiliar != NULL){
		somaValItens += auxiliar->item.valor;
		
		//auxiliar recebe a próxima posição provinda da posição atual +1
		auxiliar = auxiliar->prox;
	}
	return somaValItens;
}

//Função que recebe duas listas e retorna a com a maior quantidade de itens com o código par. (1) lista 1 (2) lista 2 (0) Empate
int funcao_D(TipoLista lista1, TipoLista lista2){
	//Variável auxiliar para percorrer a lista, que recebe no primeiro ponteiro, o prox(que referencia a célula)....
	TipoApontador auxiliar;
	
	//Contadores de tamanho para comparação...
	int tam1 = 0, tam2 = 0;

    //Para a primeira lista o TipoApontador auxiliar recebe a lista1 para percorrer o laço
    auxiliar = lista1.primeiro->prox;
	while(auxiliar != NULL){
	//Verifica se o código em item apontado por auxiliar é par, se sim, contara um para tam1. Percorrerá até o final assim...
		if( ( (auxiliar->item.codigo) % 2) == 0){
			tam1++;
		}
		auxiliar = auxiliar->prox;
	}

	//Para a segunda lista vamos reaproveitar o TipoApontador auxiliar reatribuindo a lista2 a ele
	auxiliar = lista2.primeiro->prox;
	while(auxiliar != NULL){
	//Verifica se o código em item apontado por auxiliar é par, se sim, contara um para tam2. Percorrerá até o final assim...
		if( ( (auxiliar->item.codigo) % 2) == 0){
			tam2++;
		}
		auxiliar = auxiliar->prox;
	}
	
	//Compara os tamanhos
	if(tam1 > tam2){
		return 1;
	}else 
		if(tam2 > tam1){
			return 2;
	}else{
		return 0;
	}
	
}

//Função que receberá uma posicao p de memória e insere um item após ela
void funcao_E(TipoLista *lista, TipoApontador posicao, TipoItem novoItem){

	//Se a posicao logo de inicio for nula
	if(posicao == NULL){
		printf("\nPosicao Inexistente");
		return;
	}else
	//Se caso a posicao após a ela for nula, significa que é a ultima, podemos somente inserir...
		if(posicao->prox == NULL){
			inserirDados(lista, novoItem);
		}
		//Caso não for nenhuma das anteriores, significa que há mais itens após a posição passada, logo devemos manipular...
		else{
			//Cria uma variável temporária para ajudar no auxilio
			TipoApontador p_prox;

			//p_prox recebe a posição que aponta pra prox, ou seja, recebe o endereço da célula após a posicao informada e armazena...
			p_prox = posicao->prox;

			//A mesma posicao que p_prox armazenou, agora cria uma nova com a função malloc
			posicao->prox = (TipoApontador)malloc(sizeof(TipoCelula));

			//Posicao de prox que havia criado uma nova célula, entra dentro da mesma e atribui ao prox dela o que foi armazenado
			//anteriormente em p_prox... Fazendo assim com que a nova fique entre ambas...
			posicao->prox->prox = p_prox;

			//A nova posição que aponta pra prox criada com malloc, aponta para item que recebe o novo item...
			posicao->prox->item = novoItem;
			
		}
}

//Função que receberá dois parâmetros sendo a posição dos (itens), e os trocarão de lugar na lista
void funcao_F(TipoLista *lista, TipoApontador p, TipoApontador q){
	
	//Variável auxiliar que recebe o item apontado pela posicao p e armazena-o
	TipoItem itemAuxiliar = p->item;

	//Realizando a troca
	p->item = q->item;
	q->item = itemAuxiliar;
}

//Função que recebe um item e insere o mesmo na célula cabeça(A que é apontada por primeiro em lista)
void funcao_G(TipoLista *lista, TipoItem itemParametro){

	//Inicialmente a o item da primeira posição da lista receberá o novo item
	lista->primeiro->item = itemParametro;

	//Criando uma nova celula para ocupar a primeira posição
	TipoApontador novaCelulaCabeca = (TipoApontador)malloc(sizeof(TipoCelula));

	//O prox da nova celula recebe o primeiro de lista, que aponta para a primeira celula, assim apontando
	//para a primeira célula apontada por lista...
	novaCelulaCabeca->prox = lista->primeiro;

	//Por fim primeiro em lista recebe a nova célula, em específico o endereço da mesma...
	lista->primeiro = novaCelulaCabeca;
}

//Função que remove a celula da posição passada, note que a função remove anterior, sempre remove uma a frente, e não a passada realmente...
//Basicamente iremos criar outra função de remove remove...
void funcao_H(TipoApontador posicaoPassada, TipoLista *lista, TipoItem *itemParaRemocao){
	
	//Primeiro verifica uma condição de existência da lista...
	if(posicaoPassada == NULL || lista->primeiro == NULL){
		printf("\nPosicao inexistente ou lista Vazia!...");
		return;
	}
	
	//Se a posicao for o primeiro elemento...
	if(lista->primeiro == posicaoPassada){
		//Primeiro em lista recebe prox de posicao
		lista->primeiro = posicaoPassada->prox;
		
		//Entretanto e se a lista ficar vazia ?
		if(lista->primeiro == NULL){ //Se a lista ficar vazia após a remoção...
			lista->ultimo = NULL; //Significa que não há itens e o ponteiro de ultimo deve deixar a célula removida e apontar pra NULL
		}
	}else{
		//Caso não esteja nula e nem seja a ultima posicao, estará entre outras, neste caso:
		
		//Criando uma variável pra receber a primeira posicao, que pega o conteudo em primeiro de lista
		TipoApontador anterior = lista->primeiro;
		
		//Enquanto for diferente de nulo e da posicao passada como parâmetro...
		while(anterior != NULL && anterior->prox != posicaoPassada){
			//Ele continua procurando...
			anterior = anterior->prox;
		}
		
		//Se caso mesmo assim a posição não for encontrada, chegará ao final que recebera por fim: NULL
		if(anterior == NULL){
			printf("\nPosição não encontrada!...");
			return;
		}
		
		//Se caso encontrar, então:
		//Prox de anterior recebe o prox da posicao que será apagada, ou seja pra onde ela aponta...
		anterior->prox = posicaoPassada->prox;
		
		//Se o que foi removido for o ultimo, é necessário apontar o ultimo
		if(posicaoPassada == lista->ultimo){
			//Ou seja, ultimo em lista recebe o endereço de da célula "anterior"
			lista->ultimo = anterior;
		}
	}
	//Copia o item armazenado na célula que será removida para caso queira mostrar ou fazer algo depois...
	*itemParaRemocao = posicaoPassada->item;

	free(posicaoPassada);
}

//Função que retira todas as células com itens.codigo que possui o valor negativo...
void funcao_I(TipoLista *lista){
	
	//auxiliar ira percorrer a lista
	TipoApontador auxiliar = lista->primeiro->prox;
	
	//Esse irá acompanhar o auxiliar para quando encontrar algo, passar a posição exata para funcao_H
	TipoApontador posicaoInicial = lista->primeiro;
	
	while(auxiliar != NULL){
		if(auxiliar->item.codigo < 0){
			
			//Marca a posicao para remoção
			TipoApontador posicao_A_Remover = auxiliar;
			
			//Ao avançar o ponteiro auxiliar antes de chamar funcao_H, garantimos que posicaoInicial ainda aponte 
			//para a posição anterior ao item que será removido
			auxiliar = auxiliar->prox;
			
			//Como temos a posicao anterior e a atual...
			
			//Chamando a função_H
			funcao_H(posicaoInicial->prox, lista, &posicao_A_Remover->item);
			
			
		}else{
			posicaoInicial = posicaoInicial->prox;
			auxiliar = auxiliar->prox;
		}
	}
}

//Função que compara a quantidade de itens em cada lista e retorna (1)Lista1, (2)Lista2 ou (0)Empate
int funcao_J(TipoLista lista1, TipoLista lista2){
	//Variável auxiliar para percorrer a lista, que recebe no primeiro ponteiro, o prox(que referencia a célula)....
	TipoApontador auxiliar;
	
	//Contadores de tamanho para comparação...
	int tam1 = 0, tam2 = 0;

    //Para a primeira lista o TipoApontador auxiliar recebe a lista1 para percorrer o laço
    auxiliar = lista1.primeiro->prox;
	while(auxiliar != NULL){
		tam1++;
		auxiliar = auxiliar->prox;
	}

	//Para a segunda lista vamos reaproveitar o TipoApontador auxiliar reatribuindo a lista2 a ele
	auxiliar = lista2.primeiro->prox;
	while(auxiliar != NULL){
		tam2++;
		auxiliar = auxiliar->prox;
	}
	
	//Compara os tamanhos
	if(tam1 > tam2){
		return 1;
	}else 
		if(tam2 > tam1){
			return 2;
	}else{
		return 0;
	}
}


//Função que verifica se a lista está ordenada em ordem crescente (Baseado no valor em item.valor)
int funcao_K(TipoLista lista){
	
	//Primeiramente, se a lista só conter 1 elemento, teoricamente será crescente...
	if(lista.primeiro->prox == NULL){
		return 1;
	}

	//Auxiliar que irá percorrer
	TipoApontador auxiliar = lista.primeiro->prox;
	
	//Auxiliar que irá armazenar o valor atual para comparação
	float valAtual = auxiliar->item.valor;
	
	while(auxiliar != NULL){
		
		//Se o valor do elemento atual for menor que o valor anterior, isso significa que a lista não está em ordem crescente
		if(auxiliar->item.valor < valAtual){
			return 0; //Logo pode parar por ai...
		}
		
		//Pega o valor do próximo item já
		valAtual = auxiliar->item.valor;
		auxiliar = auxiliar->prox;
	}
	return 1;
}

//Função que move o item com menor valor pro inicio de uma lista
void funcao_L(TipoLista *lista){
	
	//Primeiro verificando se a lista está vazia
	if(isVoidList(*lista)){
		printf("\nLista vazia!...");
		return;
	}
	
	//Irá percorrer  a lista
	TipoApontador auxiliar = lista->primeiro->prox;
	TipoApontador posicao_Do_Menor = NULL;
	
	//Variável que armazenará o código do item de maior valor possível
	float menor = FLT_MAX;	
	
	while(auxiliar != NULL){
		
		//Verifica se o valor do item da lista é menor que a variável menor
		if(auxiliar->item.valor < menor){
			menor = auxiliar->item.valor;
		
			//Armazena a posição do item de menor valor
			posicao_Do_Menor = auxiliar;
		}
		auxiliar = auxiliar->prox;
	}
	
	//Verifica se caso a posicao não foi encontrada
	if(posicao_Do_Menor == NULL){
		printf("\nErro ao encontrar o menor item!...");
		return;
	}
	
	//Se a posicao do menor item não for a primeira, então realiza a troca...
	if(posicao_Do_Menor != lista->primeiro->prox){
		//Cria um novo tipoItem para armazenar o item removido após a chamada da função remove
		TipoItem itemRemovido;
		funcao_H(posicao_Do_Menor, lista, &itemRemovido);
		
		//Agora insere na primeira posicao...
		funcao_G(lista, itemRemovido);
		printf("Item com menor valor movido para o início da lista.\n");
		
	}else{
		printf("O item com menor valor já está no início da lista.\n");
	}
}

//Função TipoLista que recebe 3 listas e retorna uma terceira com a união do conteúdo das duas anteriores, uma após a outra
TipoLista funcao_M(TipoLista *lista1, TipoLista *lista2){
	
	//Criando uma nova lista e iniciando-a como vazia inicialmente
	TipoLista novaLista;
	initVoidList(&novaLista);
	
	//Auxiliar que irá percorrer para fazer as cópias
	TipoApontador auxiliar;
	
	//Variável que vai armazenar cada item de cada célula e atuar junto ai insert
	TipoItem ItemCopiado;
	
	//Começando pela primeira lista
	auxiliar = lista1->primeiro->prox;
	while(auxiliar != NULL){
		
		//A cada laço será atribuido um item relativo ao avanço
		ItemCopiado = auxiliar->item;
		
		//Insere na nova lista o item que foi copiado da lista2
		inserirDados(&novaLista, ItemCopiado);
		
		auxiliar = auxiliar->prox;
	}
	
	auxiliar = lista2->primeiro->prox;
	while(auxiliar != NULL){
		
		//A cada laço será atribuido um item relativo ao avanço
		ItemCopiado = auxiliar->item;
		
		//Insere na nova lista o item que foi copiado da lista2
		inserirDados(&novaLista, ItemCopiado);
		
		auxiliar = auxiliar->prox;
	}
	return novaLista;
}

//Função que recebe duas listas e retorna uma terceira contendo somente os itens de código impar
TipoLista funcao_N(TipoLista *lista1, TipoLista *lista2){
	//Criando uma nova lista e iniciando-a como vazia inicialmente
	TipoLista novaLista;
	initVoidList(&novaLista);
	
	//Auxiliar que irá percorrer para fazer as cópias
	TipoApontador auxiliar;
	
	//Variável que vai armazenar cada item de cada célula e atuar junto ai insert
	TipoItem ItemCopiado;
	
	//Começando pela primeira lista
	auxiliar = lista1->primeiro->prox;
	while(auxiliar != NULL){
		
		//Basicamente é a mesma ideia da anterior, somente com um acrescimo de um if que verifica se o cod é impar
		if((auxiliar->item.codigo)%2 != 0){
			
		//A cada laço será atribuido um item relativo ao avanço
		ItemCopiado = auxiliar->item;
		
		//Insere na nova lista o item que foi copiado da lista2
		inserirDados(&novaLista, ItemCopiado);
		}
		auxiliar = auxiliar->prox;
	}
	
	auxiliar = lista2->primeiro->prox;
	while(auxiliar != NULL){
		
		if((auxiliar->item.codigo)%2 != 0){
		//A cada laço será atribuido um item relativo ao avanço
		ItemCopiado = auxiliar->item;
		
		//Insere na nova lista o item que foi copiado da lista2
		inserirDados(&novaLista, ItemCopiado);
		}
		auxiliar = auxiliar->prox;
	}
	return novaLista;
}

//Função que recebe duas listas e retorna uma terceira de forma intercalada
TipoLista funcao_O(TipoLista *lista1, TipoLista *lista2){
	
	//Criando uma nova lista e iniciando-a	
	TipoLista novaLista;
	initVoidList(&novaLista);
	
	//Variáveis ponteiros que vão fazer a intercalação e copia na nova lista
	TipoApontador auxiliar1 = lista1->primeiro->prox;
	TipoApontador auxiliar2 = lista2->primeiro->prox;

	//Enquando ambas as listas foram diferente de NULL
	while(auxiliar1 && auxiliar2 != NULL){
		
		//Se a a lista1 ainda houver itens, então adicione...
		if(auxiliar1 != NULL){
			//Insere o dado atual da lista 1 na nova lista
			inserirDados(&novaLista, auxiliar1->item);
			auxiliar1 = auxiliar1->prox;
		}
		
		//Se a a lista2 ainda houver itens, então adicione...
		if(auxiliar2 != NULL){
			//Insere o dado atual da lista 2 na nova lista, após o acrescimo do anterior...
			inserirDados(&novaLista, auxiliar2->item);
			auxiliar2 = auxiliar2->prox;
		}
	}
	return novaLista;
}

int main(void){
	
/*-----------------------------------------------------------*/	
	
	//Criando listas e um item para auxiliar na inserção
	struct TipoLista lista1;
	struct TipoLista lista2;
	struct TipoItem item;
	TipoApontador p;
	//Iniciando a lista como vazia
	initVoidList(&lista1);
	initVoidList(&lista2);

/*-----------------------------------------------------------*/
	
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
	
/*-----------------------------------------------------------*/
	
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
/*-----------------------------------------------------------*/
	
	//Teste função A
	printf("\n_______ Teste Item A _______\n");
	//p retorna um tipo apontador de TipoCelula para descricao
	p = funcao_A(lista1, "Fusca Antigo");
	printf("\nDescricao: %s\n", p->item.descricao);
	printf("\n\nPressione Enter para continuar...");
	
	getchar();
	system("clear");
/*-----------------------------------------------------------*/
	
	//Teste função B
	printf("\n_______ Teste Item b _______\n");
	//p retorna um tipo apontador de TipoCelula para codigo
	p = funcao_B(lista1, 01);
	printf("\nCodigo: %i\n", p->item.codigo);
	printf("\n\nPressione Enter para continuar...");
	
	getchar();
	system("clear");
/*-----------------------------------------------------------*/
	printf("\n_______ Teste Item C _______\n");
	//Teste função C
	printf("\n%.2f\n", funcao_C(lista1));
	printf("\n\nPressione Enter para continuar...");
	getchar();
	system("clear");
/*-----------------------------------------------------------*/

	//Teste função D
	printf("\n_______ Teste Item D _______\n");
	printf("\n%i", funcao_D(lista1, lista2));
	printf("\n\nPressione Enter para continuar...");

	getchar();
	system("clear");
/*-----------------------------------------------------------*/

	//Teste função E
	printf("\n_______ Teste Item E _______\n");
	//Novo Item
	item.codigo = 23;
	strcpy(item.descricao, "Brasilia");
	item.valor = 25000;

	//posicao recebe a função B, que retorna o endereço de uma célula 
	TipoApontador posicao = funcao_B(lista1, 2);

	//Agora que possuimos a posição em sí, deviso a função B, pode-se utilizar na função E
	funcao_E(&lista1, posicao, item);

	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
/*-----------------------------------------------------------*/

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
/*-----------------------------------------------------------*/

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

/*-----------------------------------------------------------*/

	//Teste Função H
	
	printf("\n_______ Teste Item H _______\n");

	//Remove a exata posicao passada e nãoa posterior
	
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
/*-----------------------------------------------------------*/

	//Teste Função I
	printf("\n_______ Teste Item I _______\n");

	funcao_I(&lista1);
	
	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
	
/*-----------------------------------------------------------*/

	//Teste Função J
	printf("\n_______ Teste Item J _______\n");
	
	printf("\n%i\n", funcao_J(lista1, lista2));
	printf("\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
	
/*-----------------------------------------------------------*/

	//Teste Função K
	printf("\n_______ Teste Item K _______\n");
	
	printf("\n%i", funcao_K(lista2));
	printf("\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
	
/*-----------------------------------------------------------*/

	//Teste Função L
	printf("\n_______ Teste Item L _______\n");
	
	funcao_L(&lista1);
	
	printf("\nLista {\n\n");
		impress(lista1);
	printf("\n}\n\n Pressione Enter para continuar...");

	
	getchar();
	system("clear");
	
/*-----------------------------------------------------------*/

	//Teste Função M
	printf("\n_______ Teste Item M _______\n");
	
	TipoLista lista3 = funcao_M(&lista1, &lista2);
	
	printf("\nLista {\n\n");
		impress(lista3);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
	
/*-----------------------------------------------------------*/

	//Teste Função N
	printf("\n_______ Teste Item N _______\n");
	
	TipoLista lista4 = funcao_N(&lista1, &lista2);
	
	printf("\nLista {\n\n");
		impress(lista4);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
	
/*-----------------------------------------------------------*/

	//Teste Função O
	printf("\n_______ Teste Item O _______\n");
	
	TipoLista lista5 = funcao_O(&lista1, &lista2);
	
	printf("\nLista {\n\n");
		impress(lista5);
	printf("\n}\n\n Pressione Enter para continuar...");
	
	getchar();
	system("clear");
	
/*-----------------------------------------------------------*/
}
