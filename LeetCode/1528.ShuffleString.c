#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *restoreString(char *s, int *indices, int indicesSize)
{
    char *resultado;
    resultado = malloc((indicesSize + 1) * sizeof(char));

    for (int i = 0; i < indicesSize; i++)
    {
        resultado[indices[i]] = s[i];
    }

    resultado[indicesSize] = '\0';

    return resultado;
}

int main()
{
    char *s = "codeleet";
    int indices[] = {4, 5, 6, 7, 0, 2, 1, 3};
    int indicesSize = 8;
    
    char *result;
    result = restoreString(s, indices, indicesSize);

    printf("%s\n", result);

    return 0;
}