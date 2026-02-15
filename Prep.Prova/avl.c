#include <stdio.h>
#include <stdlib.h>


//avl

typedef struct No {
	long	   valor;
	struct No* esq;
	struct No* dir;
} No;

int Altura( No* raiz ) {
	int iEsq, iDir;
	if( raiz == NULL ) {
		return 0;
	}
	iEsq = Altura( raiz->esq );
	iDir = Altura( raiz->dir );
	if( iEsq > iDir ) {
		return iEsq + 1;
	} else {
		return iDir + 1;
	}
}

int FB( No* raiz ) {
	if( raiz == NULL ) {
		return 0;
	}
	return Altura( raiz->esq ) - Altura( raiz->dir );
}

void rotaçãoEsquerda( No** raiz ) {
	No* aux;
	aux			   = ( *raiz )->dir;
	( *raiz )->dir = aux->esq;
	aux->esq	   = ( *raiz );
	( *raiz )	   = aux;
}

void rotaçãoDireita( No** raiz ) { // 15
	No* aux;
	aux			   = ( *raiz )->esq; // aux recebe 10
	( *raiz )->esq = aux->dir;		 // filho esq de 15 recebe direita de 10 = null
	aux->dir	   = ( *raiz );		 // direta do 10 recebe 15
	( *raiz )	   = aux;			 // raiz recebe nó 10
}

int balançaEsquerda( No** raiz ) {
	int fbe = FB( ( *raiz )->esq );
	if( fbe > 0 ) {
		rotaçãoDireita( raiz );
		return 1;
	} else if( fbe < 0 ) {
		rotaçãoEsquerda( &( ( *raiz )->esq ) );
		rotaçãoDireita( raiz );
		return 1;
	}
	return 0;
}

int balançaDireita( No** raiz ) {
	int fbd = FB( ( *raiz )->dir );
	if( fbd < 0 ) {
		rotaçãoEsquerda( raiz );
		return 1;
	} else if( fbd > 0 ) {
		rotaçãoDireita( &( ( *raiz )->dir ) );
		rotaçãoEsquerda( raiz );
		return 1;
	}
	return 0;
}

int balanceamento( No** raiz ) {
	int fb = FB( *raiz );
	if( fb > 1 )
		return balançaEsquerda( raiz );
	else if( fb < -1 )
		return balançaDireita( raiz );
	else
		return 0;
}

int Insere( No** raiz, long valor ) {
	if( *raiz == NULL ) {
		*raiz			 = ( No* )malloc( sizeof( No ) );
		( *raiz )->valor = valor;
		( *raiz )->esq	 = NULL;
		( *raiz )->dir	 = NULL;
		return 1;
	} else if( ( *raiz )->valor > valor ) {
		if( Insere( &( ( *raiz )->esq ), valor ) ) {
			if( balanceamento( raiz ) )
				return 0;
			else
				return 1;
		}
	} else if( ( *raiz )->valor < valor ) {
		if( Insere( &( ( *raiz )->dir ), valor ) ) {
			if( balanceamento( raiz ) )
				return 0;
			else
				return 1;
		} else
			return 0;
	} else
		return 0;
}

int EhArvoreAvl( No* raiz ) {
	int fb;
	if( raiz == NULL )
		return 1;
	if( !EhArvoreAvl( raiz->esq ) )
		return 0;
	if( !EhArvoreAvl( raiz->dir ) )
		return 0;
	fb = FB( raiz );
	if( ( fb > 1 ) || ( fb < -1 ) )
		return 0;
	else
		return 1;
}

void EmOrdem( No* raiz ) {
	if( raiz != NULL ) {
		EmOrdem( raiz->esq );
		printf( "%ld ", raiz->valor );
		EmOrdem( raiz->dir );
	}
}

int main() {
	No* raiz = NULL;

	int valores[] = { 10, 20, 15 };
	int n		  = 3;

	for( int i = 0; i < n; i++ ) {
		printf( "%d ", valores[i] );
		Insere( &raiz, valores[i] );
	}

	printf( "\n" );
	EmOrdem( raiz );
	printf( "\n" );

	if( EhArvoreAvl( raiz ) )
		printf( "e avl\n" );
	else
		printf( "n e avl\n" );

	printf( "altura: %d\n", Altura( raiz ) );
	printf( "FB: %d\n", FB( raiz ) );

	return 0;
}
