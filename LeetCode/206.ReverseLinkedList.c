#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *iniciaLista(void)
{
    struct ListNode *head;
    head = (struct ListNode *)malloc(sizeof(struct ListNode));

    head->next = NULL;
    return head;
}

void criaLista(struct ListNode *head)
{
    struct ListNode *anterior;
    anterior = head;

    for (int i = 1; i <= 10; i++)
    {
        struct ListNode *novoNo;
        novoNo = (struct ListNode *)malloc(sizeof(struct ListNode));

        novoNo->val = i;
        novoNo->next = NULL;

        anterior->next = novoNo;
        anterior = novoNo;
    }
}

void imprimeLista(struct ListNode *atual)
{
    struct ListNode *p;

    for (p = atual->next; p != NULL; p = p->next)
    {
        printf("%d ", p->val);
    }
}

struct ListNode *reverseList(struct ListNode *head)
{

    struct ListNode *anterior = NULL;
    struct ListNode *atual = head;
    struct ListNode *proximo = NULL;

    while (atual != NULL)
    {
        proximo = atual->next;
        atual->next = anterior;
        anterior = atual;
        atual = proximo;
    }

    return anterior;
}

int main()
{
    struct ListNode *head;
    struct ListNode *atual;

    head = iniciaLista();

    criaLista(head);

    atual = reverseList(head);

    imprimeLista(atual);

    return 0;
}