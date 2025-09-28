#include <stdlib.h>
#include <stdio.h>

int main()
{

    int i, *numero;
    numero = (int *)calloc(sizeof(int), 6);

    for (i = 0; i < 6; i++)
    {
        numero[i] = i + 1;
    }

    int *temp;
    temp = (int *)realloc(numero, 10 * sizeof(int));

    numero = temp;

    for (i = 5; i < 10; i++){
        numero[i]=i+1;
    }

    for ( i = 0; i < 10; i++)
    {
        printf("vetor %d: %d\n", i, numero[i]);

    }
    
}