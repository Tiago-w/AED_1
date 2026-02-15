#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
	int itens[MAX];
	int front; // Onde sai (início)
	int rear;  // Onde entra (fim)
} Fila;

// 1. Inicializar
void initFila( Fila* f ) {
	f->front = 0;
	f->rear	 = 0;
}

// 2. Enfileirar (Enqueue) - Entra no fim
void enqueue( Fila* f, int valor ) {
	if( f->rear == MAX ) {
		printf( "Erro: Fila cheia!\n" );
		return;
	}
	f->itens[f->rear] = valor; // Coloca no final
	f->rear++;				   // Aumenta a fila
}

// 3. Desenfileirar (Dequeue) - Sai do início
int dequeue( Fila* f ) {
	if( f->front == f->rear ) {
		printf( "Erro: Fila vazia!\n" );
		return -1;
	}
	int valor = f->itens[f->front]; // Pega quem está na frente
	f->front++;						// A fila anda
	return valor;
}


int main() {
	Fila f;
	initFila(&f);
	enqueue(&f, 10);
	enqueue(&f, 20);
	printf("Atendido: %d\n", dequeue(&f)); // Imprime 10
	return 0;
}

/*
#include <stdio.h>
#include <stdbool.h>

void exemploFila() {
    // 1. Definição (Tamanho fixo para a prova)
    int fila[1000];
    int front = 0; // Aponta para o PRIMEIRO elemento (cabeça)
    int rear = 0;  // Aponta para a posição VAZIA depois do último (rabo)

    // --- COMO ENFILEIRAR (ENQUEUE) ---
    // Adicionar o número 10
    fila[rear] = 10; 
    rear++; 
    // ou simplesmente: fila[rear++] = 10;

    // Adicionar o número 20
    fila[rear++] = 20;

    // --- COMO DESENFILEIRAR (DEQUEUE) ---
    // Regra: Só pode tirar se front < rear (fila não vazia)
    if (front < rear) {
        int removido = fila[front];
        front++;
        printf("Saiu da fila: %d\n", removido); // Vai imprimir 10 (o primeiro que entrou)
    }

    // --- COMO VER O PRIMEIRO (PEEK/FRONT) ---
    if (front < rear) {
        int primeiro = fila[front];
        printf("Quem é o próximo da fila? %d\n", primeiro); // Vai ser 20
    }
}*/
