#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================================================
// PARTE 1: A FERRAMENTA (NOSSA PILHA)
// Estrutura de dados básica que usaremos para construir a Fila.
// ==========================================================
typedef struct {
    int *dados;
    int topo;
    int capacidade;
} MinhaPilha;

// Funções auxiliares para a Pilha
MinhaPilha* pilhaCria(int capacidade) {
    MinhaPilha* p = (MinhaPilha*) malloc(sizeof(MinhaPilha));
    p->dados = (int*) malloc(sizeof(int) * capacidade);
    p->topo = -1;
    p->capacidade = capacidade;
    return p;
}
bool pilhaVazia(MinhaPilha* p) { return p->topo == -1; }
void pilhaEmpilha(MinhaPilha* p, int valor) { p->topo++; p->dados[p->topo] = valor; }
int pilhaDesempilha(MinhaPilha* p) { int val = p->dados[p->topo]; p->topo--; return val; }
int pilhaEspia(MinhaPilha* p) { return p->dados[p->topo]; }
void pilhaLibera(MinhaPilha* p) { free(p->dados); free(p); }

// ==========================================================
// PARTE 2: A SOLUÇÃO (LEETCODE 232 - NOSSA FILA)
// Nomes das funções adaptados para o padrão do LeetCode.
// ==========================================================
typedef struct {
    MinhaPilha *pilhaEntrada;
    MinhaPilha *pilhaSaida;
} MyQueue; // O LeetCode espera o nome "MyQueue"

// Cria e inicializa a fila e suas duas pilhas internas.
MyQueue* myQueueCreate() {
    MyQueue* f = (MyQueue*) malloc(sizeof(MyQueue));
    // As restrições do problema garantem que 100 é uma capacidade segura.
    f->pilhaEntrada = pilhaCria(100);
    f->pilhaSaida = pilhaCria(100);
    return f;
}

// Adiciona um elemento à fila.
void myQueuePush(MyQueue* obj, int x) {
    // Novos elementos sempre entram pela pilha de entrada.
    pilhaEmpilha(obj->pilhaEntrada, x);
}

// Função auxiliar para mover os elementos quando necessário.
void _transferir(MyQueue* obj) {
    // Só move se a pilha de saída estiver vazia.
    if (pilhaVazia(obj->pilhaSaida)) {
        // Move todos os elementos da entrada para a saída, invertendo a ordem.
        while (!pilhaVazia(obj->pilhaEntrada)) {
            pilhaEmpilha(obj->pilhaSaida, pilhaDesempilha(obj->pilhaEntrada));
        }
    }
}

// Remove o primeiro elemento da fila e o retorna.
int myQueuePop(MyQueue* obj) {
    // Garante que o elemento mais antigo esteja no topo da pilha de saída.
    _transferir(obj);
    // Remove o elemento da pilha de saída.
    return pilhaDesempilha(obj->pilhaSaida);
}

// Retorna o primeiro elemento da fila sem removê-lo.
int myQueuePeek(MyQueue* obj) {
    // Garante que o elemento mais antigo esteja no topo da pilha de saída.
    _transferir(obj);
    // Apenas espia o elemento da pilha de saída.
    return pilhaEspia(obj->pilhaSaida);
}

// Verifica se a fila está vazia.
bool myQueueEmpty(MyQueue* obj) {
    // A fila só está vazia se AMBAS as pilhas estiverem vazias.
    return pilhaVazia(obj->pilhaEntrada) && pilhaVazia(obj->pilhaSaida);
}

// Libera toda a memória alocada.
void myQueueFree(MyQueue* obj) {
    pilhaLibera(obj->pilhaEntrada);
    pilhaLibera(obj->pilhaSaida);
    free(obj);
}