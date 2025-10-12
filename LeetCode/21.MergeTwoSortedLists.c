#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *crialista(void)
{
    struct ListNode *cabeca;
    cabeca = (struct ListNode *)malloc(sizeof(struct ListNode));
    cabeca->next = NULL;
    return cabeca;
}

void inserelist1(struct ListNode *list)
{
    struct ListNode *atual = list;
    for (int i = 1; i <= 5; i++)
    {
        struct ListNode *novo;
        novo = (struct ListNode *)malloc(sizeof(struct ListNode));
        novo->val = i;
        novo->next = NULL;
        atual->next = novo;
        atual = novo;
    }
}

void inserelist2(struct ListNode *list)
{
    struct ListNode *atual = list;

    for (int i = 5; i >= 1; i--)
    {
        struct ListNode *novo;
        novo = (struct ListNode *)malloc(sizeof(struct ListNode));
        novo->val = i;
        novo->next = NULL;

        atual->next = novo;
        atual = novo;
    }
}

void imprimeLista(struct ListNode *list)
{
    struct ListNode *atual;
    atual = list->next;
    while (atual != NULL)
    {
        printf("%d ", atual->val);
        atual = atual->next;
    }
    printf("\n");
}

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{

    struct ListNode *result = crialista();
    struct ListNode *atual = result;

    struct ListNode *p1 = list1->next;
    struct ListNode *p2 = list2->next;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->val <= p2->val)
        {
            atual->next = p1;
            p1 = p1->next;
        }
        else
        {
            atual->next = p2;
            p2 = p2->next;
        }
        atual = atual->next;
    }

    if (p1 != NULL)
    {
        atual->next = p1;
    }
    else
    {
        atual->next = p2;
    }
    return result;
}

int main()
{
    struct ListNode *list1;
    struct ListNode *list2;

    list1 = crialista();
    list2 = crialista();

    inserelist1(list1);
    inserelist2(list2);

    imprimeLista(list1);
    imprimeLista(list2);

    struct ListNode *resultado;
    resultado = (struct ListNode *)malloc(sizeof(struct ListNode));

    resultado = mergeTwoLists(list1, list2);

    imprimeLista(resultado);

    return 0;
}
