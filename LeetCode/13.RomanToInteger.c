#include <stdio.h>  
#include <string.h> 

int romanToInt(char * s) {
    int total = 0;
    int valor_anterior = 0;
    int tamanho = strlen(s);

    for (int i = tamanho - 1; i >= 0; i--) {
        int valor_atual;

        switch (s[i]) {
            case 'I': valor_atual = 1;    break;
            case 'V': valor_atual = 5;    break;
            case 'X': valor_atual = 10;   break;
            case 'L': valor_atual = 50;   break;
            case 'C': valor_atual = 100;  break;
            case 'D': valor_atual = 500;  break;
            case 'M': valor_atual = 1000; break;
            default:  valor_atual = 0;    break;
        }

        if (valor_atual < valor_anterior) {
            total -= valor_atual;
        } else {
            total += valor_atual;
        }
        
        valor_anterior = valor_atual;
    }
    
    return total;
}


int main() {
    
    char carac[] = "MCMXCIV";
    int num= romanToInt(carac);

    printf("%s -> %d\n", carac, num);

    return 0;
}