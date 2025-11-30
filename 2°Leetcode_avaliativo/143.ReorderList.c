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

int main() {
	struct ListNode* no;
	no						   = criaLista( 1 );
	no->next				   = criaLista( 2 );
	no->next->next			   = criaLista( 3 );
	no->next->next->next	   = criaLista( 4 );
	no->next->next->next->next = criaLista( 5 );

	reorderList( no );
	imprimirLista( no );
}

void reorderList( struct ListNode* head ) {

	struct ListNode* temp	   = head;
	int				 valorTemp = 0, i = 0;

	while( temp != NULL ) {
		if( i % 2 != 0 ) {
			int t	  = 0;
			while( temp->next != NULL ) {
				valorTemp = temp->val;
				t++;
			}
			temp->val = valorTemp - t;
			t++;
		}
		temp = temp->next;
		i++;
	}
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