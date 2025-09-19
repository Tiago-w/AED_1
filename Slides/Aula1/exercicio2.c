#include <stdio.h>

int menu(int){
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
void adicionarnome(void){
    
    char nomes[300];

    printf("Digite o nome: ");
    scanf("%s", nomes);
    
}
int main(){
    int opcao;
    opcao=menu;

    switch (opcao)
    {
    case 1:
        adicionarnome();
        break;
    case 2:
        removernome();
        break;
    case 3:
        listarnomes();
        break;
    case 4:
        exit(0);
    }

    return 0;
}