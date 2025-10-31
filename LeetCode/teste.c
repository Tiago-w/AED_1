#include <stdbool.h>
#include <stddef.h> // Para usar size_t ou definir o tamanho

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n)
{
    if (n == 0)
    {
        return true;
    }

    if (flowerbedSize == 1)
    {
        if (flowerbed[0] == 0 && n <= 1)
        {
            return true;
        }
        return false;
    }

    for (int i = 0; i < flowerbedSize; i++)
    {
        if (flowerbed[i] == 0)
        {
            bool prev_ok = (i == 0) || (flowerbed[i - 1] == 0);

            bool next_ok = (i == flowerbedSize - 1) || (flowerbed[i + 1] == 0);

            if (prev_ok && next_ok)
            {
                flowerbed[i] = 1;
                n--;

                if (n == 0)
                {
                    return true;
                }
            }
        }
    }

    return n <= 0;
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
    if((flowerbed[0] == 0 && flowerbed[1] == 0) && ((flowerbed[flowerbedSize - 2] == 0 && flowerbed[flowerbedSize - 1] == 0)))
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