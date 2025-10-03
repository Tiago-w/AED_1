#include <stdio.h>
#include <stdlib.h>

#define numSize 5

int *runningSum(int *nums, int numsSize, int *returnSize)
{
    int *vetor;
    vetor = (int *)malloc(sizeof(int) * numsSize);

    vetor[0]=nums[0];

    for (int i = 1; i < numSize; i++)
    {
        vetor[i] = vetor[i - 1] + nums[i];
    }
    *returnSize = numsSize;
    
    return vetor;
}

int main()
{
    int nums[numSize] = {1, 2, 3, 4, 5};
    int returnSize;
    int numsSize=numSize;

    int *resultado = runningSum(nums, numsSize, &returnSize);

    printf("[");
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", resultado[i]);
    }
    printf("]");

    free(resultado);
}
