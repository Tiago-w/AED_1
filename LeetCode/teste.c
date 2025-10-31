#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n);

int main()
{
    int flowerbed[] = {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    int flowerbedSize = 13;
    int n = 4;
    bool result;

    result = canPlaceFlowers(flowerbed, flowerbedSize, n);

    printf("%d", result);

    return 0;
}

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n)
{

    for (int i = 1; i < flowerbedSize - 1; i++)
    {

        if (flowerbed[i - 1] == 0 && flowerbed[i + 1] == 0 && flowerbed[i - 1] == flowerbed[i + 1] && flowerbed[i] == 0)
        {
            flowerbed[i] = 1;
            n--;
        }
    }

    if ((flowerbed[0] == 0 && flowerbed[1] == 0) || ((flowerbed[flowerbedSize - 2] == 0 && flowerbed[flowerbedSize - 1] == 0)))
    {
        n--;
    }
    if ((flowerbed[0] == 0 && flowerbed[1] == 0) && ((flowerbed[flowerbedSize - 2] == 0 && flowerbed[flowerbedSize - 1] == 0)))
    {
        n--;
    }

    if (n == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}