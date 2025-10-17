#include <stdio.h>
#include <stdlib.h>

int *finalPrices(int *prices, int pricesSize, int *returnSize)
{
    int *resultado = (int *)malloc(sizeof(int) * pricesSize);
    *returnSize = pricesSize;
    for (int i = 0; i < pricesSize; i++)
    {
        resultado[i] = prices[i];
        for (int j = i+1; j < pricesSize; j++) // nt prices [] =  {10,1,1,6};
        {
            if (prices[i] >= prices[j] && j>=i)
            {
                resultado[i] = prices[i] - prices[j];

                break;
            }
            
        }
    }

    return resultado;
}

int main()
{
    int pricesSize = 4, returnSize;
    int prices[] = {10,1,1,6};

    int *result = (int *)malloc(sizeof(int)*pricesSize);

    result = finalPrices(prices, pricesSize, &returnSize);
    for (int i = 0; i < pricesSize; i++)
    {
        printf("%d ", result[i]);
    }
    return 0;
}