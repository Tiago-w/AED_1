#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode* middleNode(struct ListNode* head){
    int contador = 0;
    struct ListNode* atual = head;
    while(atual != NULL){
        contador++;
        atual=atual->next;
    }
    atual = head;
    for(int i=0; i<contador/2; i++){
        atual=atual->next;
    }
    return atual;
}


int main(){

    struct ListNode node5 = {5, &node5};
    struct ListNode node4 = {4, &node5};
    struct ListNode node3 = {3, &node4};
    struct ListNode node2 = {2, &node3};
    struct ListNode head = {1, &node2};

    struct ListNode* meio = middleNode(&head);

    printf("%d", meio->val);
    
}