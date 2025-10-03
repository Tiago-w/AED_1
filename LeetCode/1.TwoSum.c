#include <stdio.h>
#include <stdlib.h>

#define numSize 5

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                int *vetor;
                vetor = (int *)malloc(sizeof(int)*2);
                vetor[0] = i;
                vetor[1] = j;

                *returnSize = 2;

                return vetor;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

int main()
{
    int returnSize;
    int target = 6;
    int nums[numSize] = {1, 5, 9, 4, 7};

    int *resultado = twoSum(nums, numSize, target, &returnSize);

    if (resultado != NULL)
    {
        printf("[%d, %d]\n", resultado[0], resultado[1]);
        free(resultado);
    }

    return 0;
}