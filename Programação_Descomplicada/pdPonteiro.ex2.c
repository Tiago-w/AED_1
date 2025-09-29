#include <stdio.h>
#include <stdlib.h>

int main(){

    int num1=5, num2=10;

    if(&num1>&num2){
        printf("endereço %p do numero %d maior que endereco %p do numero %d\n", &num1, num1, &num2, num2);
    }
    else{
        printf("endereço %p do numero %d maior que endereco %p do numero %d\n", &num2, num2, &num1, num1);

    }

    return 0;
}