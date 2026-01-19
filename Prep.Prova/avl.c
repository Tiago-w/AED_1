#include <stdio.h>
#include <stdlib.h>

typedef struct No {
	long	   valor;
	struct No* pEsq;
	struct No* pDir;
} TNo;

int Altura( TNo* pRaiz ) {
	int iEsq, iDir;
	if( pRaiz == NULL ) {
		return 0;
	}
	iEsq = Altura( pRaiz->pEsq );
	iDir = Altura( pRaiz->pDir );
	if( iEsq > iDir ) {
		return iEsq + 1;
	} else {
		return iDir + 1;
	}
}

int FB( TNo* pRaiz ) {
	if( pRaiz == NULL ) {
		return 0;
	}
	return Altura( pRaiz->pEsq ) - Altura( pRaiz->pDir );
}

void RSE( TNo** ppRaiz ) {
	TNo* pAux;
	pAux			  = ( *ppRaiz )->pDir;
	( *ppRaiz )->pDir = pAux->pEsq;
	pAux->pEsq		  = ( *ppRaiz );
	( *ppRaiz )		  = pAux;
}

void RSD( TNo** ppRaiz ) { // 15
	TNo* pAux;
	pAux			  = ( *ppRaiz )->pEsq; // aux recebe 10
	( *ppRaiz )->pEsq = pAux->pDir;		   // filho esq de 15 recebe direita de 10 = null
	pAux->pDir		  = ( *ppRaiz );	   // direta do 10 recebe 15
	( *ppRaiz )		  = pAux;			   // raiz recebe nó 10
}

int BalancaEsquerda( TNo** ppRaiz ) {
	int fbe = FB( ( *ppRaiz )->pEsq );
	if( fbe > 0 ) {
		RSD( ppRaiz );
		return 1;
	} else if( fbe < 0 ) {
		RSE( &( ( *ppRaiz )->pEsq ) );
		RSD( ppRaiz );
		return 1;
	}
	return 0;
}

int BalancaDireita( TNo** ppRaiz ) {
	int fbd = FB( ( *ppRaiz )->pDir );
	if( fbd < 0 ) {
		RSE( ppRaiz );
		return 1;
	} else if( fbd > 0 ) {
		RSD( &( ( *ppRaiz )->pDir ) );
		RSE( ppRaiz );
		return 1;
	}
	return 0;
}

int Balanceamento( TNo** ppRaiz ) {
	int fb = FB( *ppRaiz );
	if( fb > 1 )
		return BalancaEsquerda( ppRaiz );
	else if( fb < -1 )
		return BalancaDireita( ppRaiz );
	else
		return 0;
}

int Insere( TNo** ppRaiz, long valor ) {
	if( *ppRaiz == NULL ) {
		*ppRaiz			   = ( TNo* )malloc( sizeof( TNo ) );
		( *ppRaiz )->valor = valor;
		( *ppRaiz )->pEsq  = NULL;
		( *ppRaiz )->pDir  = NULL;
		return 1;
	} else if( ( *ppRaiz )->valor > valor ) {
		if( Insere( &( ( *ppRaiz )->pEsq ), valor ) ) {
			if( Balanceamento( ppRaiz ) )
				return 0;
			else
				return 1;
		}
	} else if( ( *ppRaiz )->valor < valor ) {
		if( Insere( &( ( *ppRaiz )->pDir ), valor ) ) {
			if( Balanceamento( ppRaiz ) )
				return 0;
			else
				return 1;
		} else
			return 0;
	} else
		return 0;
}

int EhArvoreAvl( TNo* pRaiz ) {
	int fb;
	if( pRaiz == NULL )
		return 1;
	if( !EhArvoreAvl( pRaiz->pEsq ) )
		return 0;
	if( !EhArvoreAvl( pRaiz->pDir ) )
		return 0;
	fb = FB( pRaiz );
	if( ( fb > 1 ) || ( fb < -1 ) )
		return 0;
	else
		return 1;
}

void EmOrdem( TNo* pRaiz ) {
	if( pRaiz != NULL ) {
		EmOrdem( pRaiz->pEsq );
		printf( "%ld ", pRaiz->valor );
		EmOrdem( pRaiz->pDir );
	}
}

int main() {
	TNo* raiz = NULL;

	int valores[] = { 10, 20, 30, 40, 50, 25 };
	int n		  = 6;

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
