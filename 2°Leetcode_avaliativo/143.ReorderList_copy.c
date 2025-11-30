// 143.ReorderList

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
	int				 val;
	struct ListNode* next;
};

void			 reorderList( struct ListNode* head );
struct ListNode* criaLista( int valor );
void			 imprimirLista( struct ListNode* cabeca );
void			 liberaLista( struct ListNode* head );

int main() {
	struct ListNode* no;
	no						   = criaLista( 1 );
	no->next				   = criaLista( 2 );
	no->next->next			   = criaLista( 3 );
	no->next->next->next	   = criaLista( 4 );
	no->next->next->next->next = criaLista( 5 );

	reorderList( no );
	imprimirLista( no );

	liberaLista( no );
}

void reorderList( struct ListNode* head ) {
	if( head == NULL || head->next == NULL )
		return;

	int				 tamanho = 0;
	struct ListNode* temp	 = head;

	while( temp != NULL ) {
		tamanho++;
		temp = temp->next;
	}

	struct ListNode** vet = malloc( tamanho * sizeof( struct ListNode* ) );

	temp = head;
	for( int i = 0; i < tamanho; i++ ) {
		vet[i] = temp;
		temp   = temp->next;
	}

	int i = 0, j = tamanho - 1;

	while( i < j ) {
		vet[i]->next = vet[j];
		i++;

		if( i == j )
			break;

		vet[j]->next = vet[i];
		j--;
	}

	vet[i]->next = NULL;

	free( vet );
}

struct ListNode* criaLista( int valor ) {
	struct ListNode* novoNo;
	novoNo		 = ( struct ListNode* )malloc( sizeof( struct ListNode ) );
	novoNo->val	 = valor;
	novoNo->next = NULL;
	return novoNo;
}

void imprimirLista( struct ListNode* cabeca ) {
	struct ListNode* temp = cabeca;
	printf( "[ " );
	while( temp != NULL ) {
		printf( "%d", temp->val );
		if( temp->next != NULL ) {
			printf( " -> " );
		}
		temp = temp->next;
	}
	printf( " ]\n" );
}
void liberaLista( struct ListNode* head ) {
	struct ListNode* temp;
	while( head != NULL ) {
		temp = head;
		head = head->next;
		free( temp );
	}
}