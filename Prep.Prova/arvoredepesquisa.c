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

int main() {

	struct no* raiz = NULL;
	int		   num;

    printf("Digite a raiz ( numero ): ");
	scanf( "%d", &num );
	raiz = inserir( raiz, num );
    printf("Digite o restante dos numeros ( digite 0 para sair ): \n");
	do {
        
		scanf( "%d", &num );
		if( num == 0 ) {
			break;
		}
		inserir( raiz, num );
	} while( num != 0 );

	printf( "Numeros da arvore em ordem crescente:\n" );
	imprimirOrdemCentral( raiz );
	printf( "\n" );

	return 0;
}
