#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *longestCommonPrefix(char **strs, int strsSize)
{

    char *prefixo;
    prefixo=(char*)malloc(sizeof(char));

    prefixo[0] = '\0';
    int t = 0;

    for (int j = 0; strs[0][j] != '\0'; j++)
    {
        char char_atual = strs[0][j];

        for (int i = 1; i < strsSize; i++)
        {
            if (strs[i][j] == '\0' || strs[i][j] != char_atual)
            {
                return prefixo;
            }
        }

        t++;

        char *temp = realloc(prefixo, t + 1);
       
        prefixo = temp;

        prefixo[t - 1] = char_atual;
        prefixo[t] = '\0';
    }

    return prefixo;
}

int main()
{
    int strsSize = 3;
    char *strs[] = {"carro", "carga", "carregado"};
    char *resultado;

    resultado = longestCommonPrefix(strs, strsSize);
    printf("%s", resultado);

    return 0;
}