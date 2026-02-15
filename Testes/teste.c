#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    struct ListNode* current = head;
    int len = 1;
    while (current->next != NULL) {
        current = current->next;
        len++;
    }

    k = k % len;
    if (k == 0) return head;

    current->next = head;

    int steps = len - k;
    while (steps > 0) {
        current = current->next;
        steps--;
    }

    struct ListNode* newHead = current->next;
    current->next = NULL;

    return newHead;
}


// Função para criar um novo nó
struct ListNode* criarNo(int valor) {
    struct ListNode* novoNo = (struct ListNode*)malloc(sizeof(struct ListNode));
    novoNo->val = valor;
    novoNo->next = NULL;
    return novoNo;
}

// Função para exibir a lista no terminal
void imprimirLista(struct ListNode* cabeca) {
    struct ListNode* temp = cabeca;
    printf("[ ");
    while (temp != NULL) {
        printf("%d", temp->val);
        if (temp->next != NULL) printf(" -> ");
        temp = temp->next;
    }
    printf(" ]\n");
}

int main() {
    // 1. Criando a lista manualmente: 1 -> 2 -> 3 -> 4 -> 5
    struct ListNode* cabeca = criarNo(1);
    cabeca->next = criarNo(2);
    cabeca->next->next = criarNo(3);
    cabeca->next->next->next = criarNo(4);
    cabeca->next->next->next->next = criarNo(5);

    printf("Lista Original:\n");
    imprimirLista(cabeca);

    int k = 2;
    printf("\nRotacionando %d vezes para a direita...\n", k);

    // 2. Chamando a função do LeetCode
    cabeca = rotateRight(cabeca, k);

    printf("Resultado Final:\n");
    imprimirLista(cabeca);

    // Limpeza de memória (opcional para scripts rápidos, mas boa prática)
    struct ListNode* temp;
    while (cabeca != NULL) {
        temp = cabeca;
        cabeca = cabeca->next;
        free(temp);
    }

    return 0;
}