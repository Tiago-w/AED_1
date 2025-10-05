#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* crialista(void) {
    struct ListNode* cabeca;
    cabeca = (struct ListNode*)malloc(sizeof(struct ListNode));
    cabeca->next = NULL;  
    return cabeca;
}

void inserelist1(struct ListNode* list) {
    struct ListNode* atual = list;
    for (int i = 1; i <= 5; i++) {
        struct ListNode* novo;
        novo = (struct ListNode*)malloc(sizeof(struct ListNode));
        novo->val = i;
        novo->next = NULL;
        atual->next = novo;
        atual = novo;
    }
}

void inserelist2(struct ListNode* list) {
    struct ListNode* atual = list;

    for (int i = 5; i >= 1; i--) {
        struct ListNode* novo;
        novo = (struct ListNode*)malloc(sizeof(struct ListNode));
        novo->val = i;
        novo->next = NULL;

        atual->next = novo;
        atual = novo;
    }
}

void imprimeLista(struct ListNode* list) {
    struct ListNode* atual;
    atual = list->next; 
    while (atual != NULL) {
        printf("%d ", atual->val);
        atual = atual->next;
    }
    
}

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2) {
    return NULL;
}

int main() {
    struct ListNode* list1;
    struct ListNode* list2;

    list1 = crialista();
    list2 = crialista();

    inserelist1(list1);
    inserelist2(list2);

    imprimeLista(list1);
    imprimeLista(list2);

    return 0;
}
