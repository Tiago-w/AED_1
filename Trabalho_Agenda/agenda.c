#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nome 50
#define idade sizeof(int)
#define email 50
#define gavetaPessoa (nome * sizeof(char) + idade + email * sizeof(char))

#define contadorPessoas 0
#define escolhaMenu (contadorPessoas + sizeof(int))
#define contadorLaço (escolhaMenu + sizeof(int))
#define pessoa (contadorLaço + sizeof(int))
#define temp (pessoa + (sizeof(char) * 50))

void exibirMenu(void);
void adicionarPessoa(void **pbuffer);
void listarPessoas(void *pbuffer);
void buscarPessoa(void *pbuffer);

int main()
{

    void *pbuffer = malloc(temp);
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
            buscarPessoa(pbuffer);
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

    void *tempbuffer = realloc(*pbuffer, temp + (*(int *)(*pbuffer + contadorPessoas) + 1) * (gavetaPessoa));

    if (!tempbuffer)
    {
        printf("erro de memoria\n");
        return;
    }

    *pbuffer = tempbuffer;

    char *destino = (char *)(*pbuffer + temp) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa);

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
    int *contadorP = (int *)(*pbuffer + contadorPessoas);
    int *contadorFor = (int *)(*pbuffer + contadorLaço);
  
        for (*contadorFor = 0; *contadorFor < *contadorP; (*contadorFor)++)
        {
            char *nomeAtual = (char *)(*pbuffer + temp) + (*contadorFor * gavetaPessoa);
            if (strcmp(nomeAtual + nome + idade, destino + nome + idade) == 0 && *contadorP>0)
            {
                printf("Essa pessoa já esta cadastrada de acordo com o email.\n");
                return;
            }
        }
    

    (*(int *)(*pbuffer + contadorPessoas))++;

    printf("deu but\n");
}
void listarPessoas(void *pbuffer)
{
    int *cp = (int *)(pbuffer + contadorPessoas);

    if (*cp == 0)
    {
        printf("ngm aqui but\n");
        return;
    }
    int *i = (int *)(pbuffer + contadorLaço);

    for (*i = 0; *i < *cp; (*i)++)
    {

        char *registroatual = (char *)(pbuffer + temp) + (*i * gavetaPessoa);

        printf("\n%d\n", *i + 1);
        printf("nome: %s\n", registroatual);
        printf("idade: %d\n", *(int *)(registroatual + nome));
        printf("email: %s\n", registroatual + nome + idade);
    }
}

void buscarPessoa(void *pbuffer)
{
    int *cp = (int *)(pbuffer + contadorPessoas);
    int *c = (int *)(pbuffer + contadorLaço);
    *c = 0;

    char *emailT = (char *)(pbuffer + pessoa);

    printf("Digite o email para buscar uma pessoa: \n");
    scanf(" %[^\n]", emailT);
    while (getchar() != '\n')
        ;

    for (*c = 0; *c < *cp; (*c)++)
    {

        char *registroAtual = (char *)(pbuffer + temp) + ((*c) * gavetaPessoa);

        if (strcmp(registroAtual + nome + idade, emailT) == 0)
        {
            printf("cadastro encontrado\nnome no sistema: ");
            printf("%s\n", registroAtual);
            return;
        }
    }
    printf("\ncadastro nao encontrado\n");

    return;
}
