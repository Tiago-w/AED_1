#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nome 50
#define idade sizeof(int)
#define email 50
#define gavetaPessoa (nome * sizeof(char) + idade + email * sizeof(char))

// estrutura pbuffer (pessoa é onde começa os dados a serem inseridos)
#define contadorPessoas 0
#define escolhaMenu (contadorPessoas + sizeof(int))
#define contadorLaço (escolhaMenu + sizeof(int))
#define pessoa (contadorLaço + sizeof(int))

void exibirMenu(void);
void adicionarPessoa(void **pbuffer);
void listarPessoas(void *pbuffer);
// void removerPessoa();
// void buscarPessoa();

int main()
{

    void *pbuffer = malloc(pessoa);
    if (!pbuffer)
    {
        printf("erro de memoria\n");
        return 1;
    }

    *(int *)(pbuffer + contadorPessoas) = 0;
    *(int *)(pbuffer + escolhaMenu) = 0;

    do
    {

        exibirMenu();
        scanf("%d", (int *)(pbuffer + escolhaMenu));

        switch (*(int *)(pbuffer + escolhaMenu))
        {
        case 1:
            adicionarPessoa(&pbuffer);
            break;
        case 2:
            // removerPessoa();
            break;
        case 3:
            // buscarPessoa();
            break;
        case 4:
            listarPessoas(pbuffer);
            break;
        case 5:
            printf("saindo but\n");
            break;
        default:
            printf("opcao invalida\n");
            break;
        }

    } while ((*(int *)(pbuffer + escolhaMenu)) != 5);

    free(pbuffer);
    return 0;
}

void exibirMenu()
{

    printf("\n Agenda em Buffer \n");
    printf("1- Adicionar Pessoa\n");
    printf("2- Remover Pessoa\n");
    printf("3- Buscar Pessoa\n");
    printf("4- Listar todos\n");
    printf("5- Sair\n");
}
void adicionarPessoa(void **pbuffer)
{

    void *tempbuffer = realloc(*pbuffer, pessoa + (*(int *)(*pbuffer + contadorPessoas) + 1) * (gavetaPessoa));

    if (!tempbuffer)
    {
        printf("erro de memoria\n");
        return;
    }

    *pbuffer = tempbuffer;

    char *destino = (char *)(*pbuffer + pessoa) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa);

    printf("digita o nome but:\n");
    scanf(" %[^\n]", destino);
    while (getchar() != '\n')
        ;

    printf("digita a idade but:\n");
    scanf("%d", (int *)(destino + nome));
    while (getchar() != '\n')
        ;

    printf("digita o email but:\n");
    scanf(" %[^\n]", destino + nome + idade);
    while (getchar() != '\n')
        ;

    (*(int *)(*pbuffer + contadorPessoas))++;

    printf("deu but\n");
}
void listarPessoas(void *pbuffer)
{

    if (*(int *)(pbuffer + contadorPessoas) == 0)
    {
        printf("ngm aqui but\n");
        return;
    }

    *(int *)(pbuffer + contadorLaço) = 0;

    void *cont = (int *)(pbuffer + contadorLaço);

    for (*(int *)(pbuffer + contadorLaço) = 0; *(int *)cont < *(int *)(pbuffer + contadorPessoas); (*(int *)(pbuffer + contadorLaço))++)
    {

        char *registroatual = (char *)(pbuffer + pessoa) + (*(int *)(pbuffer + contadorLaço) * gavetaPessoa);
       
        printf("\n%d\n", *(int *)(pbuffer + contadorLaço) + 1);
        printf("nome: %s\n", registroatual);
        printf("idade: %d\n", *(int *)(registroatual + nome));
        printf("email: %s\n", registroatual + nome + idade);
    }
}
