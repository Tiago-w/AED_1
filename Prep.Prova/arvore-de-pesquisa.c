#include <stdio.h>
#include <stdlib.h>

struct no {
	int		   valor;
	struct no* esquerda;
	struct no* direita;
};

struct no* criarNo( int valor ) {
	struct no* novo = ( struct no* )malloc( sizeof( struct no ) );
	novo->valor		= valor;
	novo->esquerda	= NULL;
	novo->direita	= NULL;
	return novo;
}

struct no* inserir( struct no* raiz, int valor ) {
	if( raiz == NULL ) {
		return criarNo( valor );
	}

	if( valor < raiz->valor ) {
		raiz->esquerda = inserir( raiz->esquerda, valor );
	} else if( valor > raiz->valor ) {
		raiz->direita = inserir( raiz->direita, valor );
	}
	return raiz;
}
void imprimirOrdemCentral( struct no* raiz ) {
	if( raiz != NULL ) {
		imprimirOrdemCentral( raiz->esquerda );
		printf( "%d ", raiz->valor );
		imprimirOrdemCentral( raiz->direita );
	}
}
struct no* encontrarMenor( struct no* raiz ) {
	while( raiz->esquerda != NULL ) {
		raiz = raiz->esquerda;
	}
	return raiz;
}

struct no* remover( struct no* raiz, int valor ) {
	if( raiz == NULL ) {
		printf( "valor nao encontrado\n" );
		return NULL;
	}

	if( valor < raiz->valor ) {	
		raiz->esquerda = remover( raiz->esquerda, valor );
	} else if( valor > raiz->valor ) {
		raiz->direita = remover( raiz->direita, valor );   //procura o valor que queremos remover
	} else {
		if( raiz->esquerda == NULL && raiz->direita == NULL ) {  //se é folha, só remove a raiz
			free( raiz );
			printf( "elemento removido\n" );
			return NULL;
		} else if( raiz->esquerda == NULL ) {           //se tem algo no lado direito e nao no esquerdo
			struct no* aux = raiz->direita;				//então coloca o valor do lado direito em uma variavel temporaria
			free( raiz );								//e tira esse nó
			printf( "elemento removido\n" );
			return aux;
		} else if( raiz->direita == NULL ) {           //se nao tem no lado direito e tem no lado esquerdo, az a mesma coisa
			struct no* aux = raiz->esquerda;			//coloca esse valor numa variavel temporaria e tira o nó e retorna 
			free( raiz );								//o valor temporario
			printf( "elemento removido\n" );
			return aux;
		} else {
			struct no* sucessor = encontrarMenor( raiz->direita );      //se é um nó que tem dois filhos, precisamos achar o menor, n entendi
			raiz->valor			= sucessor->valor;
			raiz->direita		= remover( raiz->direita, sucessor->valor );
		}
	}
	return raiz;
}

int main() {

	struct no* raiz = NULL;
	int		   num, op;

	printf( "Digite a raiz ( numero ): " );
	scanf( "%d", &num );
	raiz = inserir( raiz, num );
	printf( "digite o restante dos numeros ( digite 0 para sair ): \n" );
	do {

		scanf( "%d", &num );
		if( num == 0 ) {
			break;
		}
		inserir( raiz, num );
	} while( num != 0 );

	printf( "numeros da arvore em ordem crescente:\n" );
	imprimirOrdemCentral( raiz );
	printf( "\n" );

	do {
		printf( "\ndigite 1 para remover um número ou 2 para sair" );
		scanf( "%d", &op );
		if( op == 1 ) {
			printf( "digite o número a remover: " );
			scanf( "%d", &num );
			raiz = remover( raiz, num );
			printf( "arvore atual: " );
			imprimirOrdemCentral( raiz );
			printf( "\n" );
		}
	} while( op == 1 );

	return 0;
}
