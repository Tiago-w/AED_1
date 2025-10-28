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
#define temp (contadorLaço + sizeof(int))
#define inicioPessoas (temp + (sizeof(char) * 50))

void exibirMenu(void);
void adicionarPessoa(void **pbuffer);
void listarPessoas(void *pbuffer);
void buscarPessoa(void *pbuffer);
void removerPessoa(void **pbuffer);

int main()
{

    void *pbuffer = malloc(inicioPessoas); // endereço de pbuffer que aponta pra qualquer tipo
    if (!pbuffer)
    {
        printf("Erro de memoria!\n");
        return 1;
    }

    *(int *)(pbuffer + contadorPessoas) = 0; // soma os endereços de memória
    *(int *)(pbuffer + escolhaMenu) = 0;     // faz o cast pra (int*) e trata o endereço calculado como um inteiro
                                             // o * na frente faz escrever o valor
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
            removerPessoa(&pbuffer);
            break;
        case 3:
            buscarPessoa(pbuffer);
            break;
        case 4:
            listarPessoas(pbuffer);
            break;
        case 5:
            printf("Saindo da agenda.\n");
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }

    } while ((*(int *)(pbuffer + escolhaMenu)) != 5);

    free(pbuffer);
    return 0;
}

void exibirMenu()
{
    printf("\033[1;36m\n");
    printf("==========================================\n");
    printf("\033[1;33m"); 
    printf("         AGENDA EM BUFFER\n");
    printf("\033[1;36m"); 
    printf("==========================================\n");
    printf("\033[0m\n"); 
    printf("\033[1;32m1\033[0m - Adicionar Pessoa\n");
    printf("\033[1;32m2\033[0m - Remover Pessoa\n");
    printf("\033[1;32m3\033[0m - Buscar Pessoa\n");
    printf("\033[1;32m4\033[0m - Listar todos\n");
    printf("\033[1;31m5\033[0m - Sair\n\n");
    printf("\033[1;33m\033[5mDigite sua escolha: \033[0m");
}
void adicionarPessoa(void **pbuffer)
{

    void *tempbuffer = realloc(*pbuffer, inicioPessoas + (*(int *)(*pbuffer + contadorPessoas) + 1) * (gavetaPessoa));

    if (!tempbuffer)
    {
        printf("Erro de memoria!\n");
        return;
    }

    *pbuffer = tempbuffer;

    char *destino = (char *)(*pbuffer + inicioPessoas) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa);

    printf("\n\nDigite o nome para adicionar: ");
    scanf(" %[^\n]", destino);
    while (getchar() != '\n')
        ;

    printf("Digite a idade: ");
    scanf("%d", (int *)(destino + nome));
    while (getchar() != '\n')
        ;

    printf("Digite o email: ");
    scanf(" %[^\n]", destino + nome + idade);
    while (getchar() != '\n')
        ;

    int *contadorP = (int *)(*pbuffer + contadorPessoas);
    int *contadorFor = (int *)(*pbuffer + contadorLaço);

    for (*contadorFor = 0; *contadorFor < *contadorP; (*contadorFor)++)
    {
        char *nomeAtual = (char *)(*pbuffer + inicioPessoas) + (*contadorFor * gavetaPessoa);
        if (strcmp(nomeAtual + nome + idade, destino + nome + idade) == 0 && *contadorP > 0)
        {
            printf("\nEssa pessoa ja esta cadastrada de acordo com o email fornecido.\n");
            return;
        }
    }

    (*(int *)(*pbuffer + contadorPessoas))++;

    printf("\nAicionado!\n");
}
void listarPessoas(void *pbuffer)
{
    int *cp = (int *)(pbuffer + contadorPessoas);

    if (*cp == 0)
    {
        printf("\nNao existe registros na agenda.\n");
        return;
    }
    int *i = (int *)(pbuffer + contadorLaço);

    for (*i = 0; *i < *cp; (*i)++)
    {

        char *registroatual = (char *)(pbuffer + inicioPessoas) + (*i * gavetaPessoa);

        printf("\nCadastro %d:\n\n", *i + 1);
        printf("Nome: %s\n", registroatual);
        printf("Idade: %d\n", *(int *)(registroatual + nome));
        printf("Email: %s\n", registroatual + nome + idade);
    }
}

void buscarPessoa(void *pbuffer)
{
    int *cp = (int *)(pbuffer + contadorPessoas);
    int *c = (int *)(pbuffer + contadorLaço);
    *c = 0;

    char *emailT = (char *)(pbuffer + temp);

    printf("\nDigite o email para buscar uma pessoa: \n");
    scanf(" %[^\n]", emailT);
    while (getchar() != '\n')
        ;

    for (*c = 0; *c < *cp; (*c)++)
    {

        char *registroAtual = (char *)(pbuffer + inicioPessoas) + ((*c) * gavetaPessoa);

        if (strcmp(registroAtual + nome + idade, emailT) == 0)
        {
            printf("\nCadastro encontrado!\n\nNome: %s\n", registroAtual);
            printf("Idade: %d\n", *(int *)(registroAtual + nome));
            printf("Email: %s", registroAtual + nome + idade);
            return;
        }
    }
    printf("\nCadastro nao encontrado.\n");

    return;
}

void removerPessoa(void **pbuffer)
{

    int *cp = (int *)(*pbuffer + contadorPessoas);
    int *c = (int *)(*pbuffer + contadorLaço);
    *c = 0;

    char *emailT = (char *)(*pbuffer + temp);
    int *contT = (int *)(*pbuffer + escolhaMenu);

    printf("\nDigite o email para remover uma pessoa do registro: \n");
    scanf(" %[^\n]", emailT);
    while (getchar() != '\n')
        ;

    for (*c = 0; *c < *cp; (*c)++)
    {
        char *registroAtual = (char *)(*pbuffer + inicioPessoas) + ((*c) * gavetaPessoa);
        if (strcmp(registroAtual + nome + idade, emailT) == 0)
        {
            for (*contT = *c; *contT < *cp - 1; (*contT)++)
            {
                char *regAtual = (char *)(*pbuffer + inicioPessoas) + ((*contT) * gavetaPessoa);
                memcpy(regAtual, regAtual + gavetaPessoa, gavetaPessoa);
            }
            printf("\nRegistro removido pelo email!\n");
            (*cp)--;
            return;
        }
    }
    printf("\nNenhum registro encontrado para remover.\n");
    return;
}
