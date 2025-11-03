#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool lemonadeChange(int *bills, int billsSize);

int main()
{
    int bilssSize = 5;
    int bills[] = {5, 5, 5, 10, 20};
    bool result;

    result = lemonadeChange(bills, bilssSize);

    printf("%d", result);

    return 0;
}

bool lemonadeChange(int *bills, int billsSize)
{

    int c5 = 0;
    int c10 = 0;

    for (int cont = 0; cont < billsSize; cont++)
    {
        if (bills[cont] == 5)
        {
            c5++;
        }
        if (bills[cont] == 10)
        {
            c10++;
        }
    }

    for (int i = 0; i < billsSize; i++)
    {
        if (bills[i] == 10)
        {
            c5--;
        }
        else if (bills[i] == 20)
        {
            c5--;
            c10--;
        }
    }

    if (c5 > 0 && c10 > 0)
    {
        return true;
    }
    else
        return false;
}
