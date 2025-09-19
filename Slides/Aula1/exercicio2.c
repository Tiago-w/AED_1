#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int menu() {
     int c;

    do{
        printf("Digite uma das opcoes abaixo\n");
        printf("\t--MENU--\n");
        printf("1. Adicionar nome\n");
        printf("2. Remover nome\n");
        printf("3. Listar\n");
        printf("4. Sair\n");
        scanf("%d ", &c);
    }while(c<1 || c>4);

    return c;
}

void adicionarnome(char lista[][100], int *total) {
  
    printf("Digite o nome: ");
    fgets(lista[*total], 100, stdin);
    
    lista[*total][strcspn(lista[*total], "\n")] = 0;

    (*total)++;
    printf("Nome adicionado.\n");
}

void removernome(char lista[][100], int *total) {
    char nome_remover[100];
    int indice_encontrado = -1;

    printf("Digite o nome a ser removido: ");

    fgets(nome_remover, sizeof(nome_remover), stdin);
    nome_remover[strcspn(nome_remover, "\n")] = 0;

    for (int i = 0; i < *total; i++) {
        if (strcmp(lista[i], nome_remover) == 0) {
            indice_encontrado = i;
            break;
        }
    }

    if (indice_encontrado != -1) {
        for (int i = indice_encontrado; i < *total - 1; i++) {
            strcpy(lista[i], lista[i + 1]);
        }
        (*total)--;
        printf("Nome removido.\n");
    } else {
        printf("Nome nao encontrado.\n");
    }
}

void listarnomes(char lista[][100], int total) {
        
    printf("\nLista de Nomes\n");

        for (int i = 0; i < total; i++) {
            printf("%s\n", lista[i]);
        }
    }

int main() {
    char lista_de_nomes[50][100];
    int total_nomes = 0;
    int opcao;

    do {
        opcao = menu();
        switch (opcao) {
            case 1:
                adicionarnome(lista_de_nomes, &total_nomes);
                break;
            case 2:
                removernome(lista_de_nomes, &total_nomes);
                break;
            case 3:
                listarnomes(lista_de_nomes, total_nomes);
                break;
            case 4:

        }
    } while (opcao);

    return 0;
}