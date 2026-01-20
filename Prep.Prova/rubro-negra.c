#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct No {
	int		   cor, info;
	struct No *esq, *dir, *pai;
} No;

int corNo( No* h ) {
	if( h == NULL ) {
		return BLACK;
	}
	return h->cor;
}

No* avo( No* n ) {
	if( n != NULL && n->pai != NULL )
		return n->pai->pai;
	return NULL;
}

No* tio( No* n ) {
	No* a = avo( n );
	if( a == NULL )
		return NULL;
	if( n->pai == a->esq )
		return a->dir;
	return a->esq;
}

void rotacionaEsquerda( No** raiz, No* n ) {
	No* d = n->dir;
	if( d == NULL )
		return;

	n->dir = d->esq;
	if( d->esq != NULL )
		d->esq->pai = n;

	d->pai = n->pai;

	if( n->pai == NULL ) {
		*raiz = d;
	} else if( n == n->pai->esq ) {
		n->pai->esq = d;
	} else {
		n->pai->dir = d;
	}

	d->esq = n;
	n->pai = d;
}

void rotacionaDireita( No** raiz, No* n ) {
	No* e = n->esq;
	if( e == NULL )
		return;

	n->esq = e->dir;
	if( e->dir != NULL )
		e->dir->pai = n;

	e->pai = n->pai;

	if( n->pai == NULL ) {
		*raiz = e;
	} else if( n == n->pai->esq ) {
		n->pai->esq = e;
	} else {
		n->pai->dir = e;
	}

	e->dir = n;
	n->pai = e;
}

No* novoNo( int info ) {
	No* n	= ( No* )calloc( 1, sizeof( No ) );
	n->info = info;
	n->cor	= RED;
	return n;
}

void inserirBST( No** raiz, No* n ) {
	if( *raiz == NULL ) {
		*raiz = n;
		return;
	}

	No* atual = *raiz;
	No* pai	  = NULL;

	while( atual != NULL ) {
		pai = atual;
		if( n->info < atual->info )
			atual = atual->esq;
		else
			atual = atual->dir;
	}

	n->pai = pai;
	if( n->info < pai->info )
		pai->esq = n;
	else
		pai->dir = n;
}

void inserirCaso1( No** raiz, No* n );
void inserirCaso2( No** raiz, No* n );
void inserirCaso3( No** raiz, No* n );
void inserirCaso4( No** raiz, No* n );
void inserirCaso5( No** raiz, No* n );

void inserirCaso1( No** raiz, No* n ) {
	if( n->pai == NULL ) {
		n->cor = BLACK;
		*raiz  = n;
	} else {
		inserirCaso2( raiz, n );
	}
}

void inserirCaso2( No** raiz, No* n ) {
	if( n->pai->cor == BLACK )
		return;
	inserirCaso3( raiz, n );
}

void inserirCaso3( No** raiz, No* n ) {
	No* t = tio( n );
	No* a;

	if( t != NULL && t->cor == RED ) {
		n->pai->cor = BLACK;
		t->cor		= BLACK;

		a	   = avo( n );
		a->cor = RED;

		inserirCaso1( raiz, a );
	} else {
		inserirCaso4( raiz, n );
	}
}

void inserirCaso4( No** raiz, No* n ) {
	No* a = avo( n );
	if( a == NULL )
		return;

	if( n == n->pai->dir && n->pai == a->esq ) {
		rotacionaEsquerda( raiz, n->pai );
		n = n->esq;
	} else if( n == n->pai->esq && n->pai == a->dir ) {
		rotacionaDireita( raiz, n->pai );
		n = n->dir;
	}

	inserirCaso5( raiz, n );
}

void inserirCaso5( No** raiz, No* n ) {
	No* a = avo( n );
	if( a == NULL )
		return;

	if( n == n->pai->esq && n->pai == a->esq ) {
		rotacionaDireita( raiz, a );
	} else {
		rotacionaEsquerda( raiz, a );
	}

	n->pai->cor = BLACK;
	a->cor		= RED;
}

void inserirRubroNegra( No** raiz, int info ) {
	No* n = novoNo( info );
	inserirBST( raiz, n );
	inserirCaso1( raiz, n );
}

static void imprimeInOrdem( No* r ) {
	if( r == NULL )
		return;
	imprimeInOrdem( r->esq );
	printf( "%d(%c) ", r->info, ( r->cor == RED ? 'R' : 'B' ) );
	imprimeInOrdem( r->dir );
}

static void liberaArvore( No* r ) {
	if( r == NULL )
		return;
	liberaArvore( r->esq );
	liberaArvore( r->dir );
	free( r );
}

int main( void ) {
	No* raiz = NULL;

	int valores[] = { 11, 2, 14, 1, 7, 13, 15, 5, 8 }; 
	int n		  = 9;

	for( int i = 0; i < n; i++ ) {
		inserirRubroNegra( &raiz, valores[i] );
	}

	printf( "In-ordem (ordenado): " );
	imprimeInOrdem( raiz );
	printf( "\n" );

	liberaArvore( raiz );
	return 0;
}
