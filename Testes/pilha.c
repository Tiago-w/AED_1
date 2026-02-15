#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Tamanho máximo da pilha

typedef struct {
	int itens[MAX];
	int top;
} Pilha;

// 1. Inicializar (Começa com -1 para dizer que está vazia)
void initPilha( Pilha* p ) {
	p->top = -1;
}

// 2. Empilhar (Push) - Adiciona no topo
void push( Pilha* p, int valor ) {
	if( p->top == MAX - 1 ) {
		printf( "Erro: Pilha cheia!\n" );
		return;
	}
	p->top++;				  // Sobe o topo
	p->itens[p->top] = valor; // Guarda o valor
}

// 3. Desempilhar (Pop) - Remove do topo
int pop( Pilha* p ) {
	if( p->top == -1 ) {
		printf( "Erro: Pilha vazia!\n" );
		return -1;
	}
	int valor = p->itens[p->top]; // Pega o valor
	p->top--;					  // Desce o topo
	return valor;
}

// Main para teste

int main() {
	Pilha p;
	initPilha( &p );
	push( &p, 10 );
	push( &p, 20 );
	printf( "Removido: %d\n", pop( &p ) ); // Imprime 20
	return 0;
}
