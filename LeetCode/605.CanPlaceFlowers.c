#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n);

int main()
{
    int flowerbed[] = {0, 0, 1, 0, 0};
    int flowerbedSize = 5;
    int n = 3;
    bool result;

    result = canPlaceFlowers(flowerbed, flowerbedSize, n);

    printf("%d", result);

    return 0;
}

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n)
{
    if (n == 0) {
        return true;
    }
    
    int count = 0; 
    
    if (flowerbedSize >= 1 && flowerbed[0] == 0)
    {
        if (flowerbedSize == 1 || flowerbed[1] == 0)
        {
            flowerbed[0] = 1;
            count++;
            
            if (count >= n) {
                return true;
            }
        }
    }



    for (int i = 1; i < flowerbedSize - 1; i++)
    {
        if (flowerbed[i - 1] == 0 && flowerbed[i] == 0 && flowerbed[i + 1] == 0)
        {
            flowerbed[i] = 1; 
            count++;
            
            if (count >= n) {
                return true;
            }
        }
    }


    
    
    if (flowerbedSize >= 2 && flowerbed[flowerbedSize - 1] == 0 && flowerbed[flowerbedSize - 2] == 0)
    {
        count++;
    }

    return count >= n;
}