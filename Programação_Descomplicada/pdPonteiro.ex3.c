#include <stdio.h>
#include <stdlib.h>

int main(){

    int n1, n2;

    printf("digite a ariavel de n1: ");
    scanf("%d", &n1);
    printf("digite a ariavel de n2: ");
    scanf("%d", &n2);

    if(&n1>&n2){
        printf("endereço de %d maior que de %d\n%p > %p", n1, n2, &n1, &n2);
    } else {
        printf("endereço de %d maior que de %d\n%p > %p", n2, n1, &n2, &n1);
      }

      return 0;
      
}