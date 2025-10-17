#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int vetor[100];
    int cabeca;
    int final;
    int cnt;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue* obj = malloc(sizeof(MyQueue));
    obj->cabeca = 0;
    obj->final = 0;
    obj->cnt = 0;
    return obj;
}

void myQueuePush(MyQueue* obj, int x) {
    if(obj == NULL) return;
    
    obj->cnt++;
    obj->vetor[obj->final] = x;
    obj->final = (obj->final + 1)%100;
}

int myQueuePop(MyQueue* obj) {
    if(obj == NULL) return NULL;
    
    obj->cnt--;
    obj->cabeca = (obj->cabeca + 1)%100;
    return (obj->vetor[(obj->cabeca-1)%100]);
}

int myQueuePeek(MyQueue* obj) {
    if(obj == NULL) return NULL;
    
    return obj->vetor[obj->cabeca];
}

bool myQueueEmpty(MyQueue* obj) {
    if(obj == NULL) return false;
    
    return (obj->cnt?false:true);
}

void myQueueFree(MyQueue* obj) {
    if(obj == NULL) return;
    free(obj);
}