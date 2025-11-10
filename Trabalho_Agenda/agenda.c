#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define contadorPessoas 0
#define escolhaMenu (contadorPessoas + sizeof(int))
#define contadorLaço (escolhaMenu + sizeof(int))
#define idadetemp (contadorLaço + sizeof(int))
#define nometemp (idadetemp + sizeof(int))
#define emailtemp (nometemp + sizeof(char) * 30)
#define inicioPessoas (emailtemp + (sizeof(char) * 30))

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
    while (getchar() != '\n')
        ;

    printf("\n\nDigite o nome: ");
    scanf("%[^\n]", (char *)(*pbuffer + nometemp));
    while (getchar() != '\n')
        ;

    printf("Digite a idade: ");
    scanf("%d", (int *)(*pbuffer + idadetemp));
    while (getchar() != '\n')
        ;

    printf("Digite o email: ");
    scanf("%[^\n]", (char *)(*pbuffer + emailtemp));
    while (getchar() != '\n')
        ;

    void *novoPbuffer = realloc(*pbuffer,
                                inicioPessoas +
                                    strlen((char *)(*pbuffer + nometemp)) + 1 +
                                    sizeof(int) +
                                    strlen((char *)(*pbuffer + emailtemp)) + 1);
    if (!novoPbuffer)
    {
        printf("\n\n--ERRO DE MEMÓRIA--\n\n");
        return;
    }

    *pbuffer = novoPbuffer;

    char *destino = (char *)(*pbuffer + inicioPessoas);
    *(int *)(*pbuffer + contadorLaço) = 0;

    while (*(int *)(*pbuffer + contadorLaço) < *(int *)(*pbuffer + contadorPessoas))
    {
        destino = destino +
                  strlen(destino) + 1 +
                  sizeof(int) +
                  strlen(destino + strlen(destino) + 1 + sizeof(int)) + 1;

        (*(int *)(*pbuffer + contadorLaço))++;
    }

    strcpy(destino, (char *)(*pbuffer + nometemp));

    *((int *)(destino + strlen(destino) + 1)) = *(int *)(*pbuffer + idadetemp);

    strcpy(destino + strlen(destino) + 1 + sizeof(int),
           (char *)(*pbuffer + emailtemp));

    (*(int *)(*pbuffer + contadorPessoas))++;

    printf("\nPessoa adicionada!\n");
}

void listarPessoas(void *pbuffer)
{

    if (*(int *)(pbuffer + contadorPessoas) == 0)
    {
        printf("\n\nNenhuma pessoa cadastrada!\n");
        return;
    }

    *(int *)(pbuffer + contadorLaço) = 0;
    char *pessoaAtual = (char *)(pbuffer + inicioPessoas);

    while (*(int *)(pbuffer + contadorLaço) < *(int *)(pbuffer + contadorPessoas))
    {

        printf("\nCadastro[%d]", *(int *)(pbuffer + contadorLaço) + 1);
        printf("\nNome: %s\n", pessoaAtual);
        printf("Idade: %d\n", *(int *)(pessoaAtual + strlen(pessoaAtual) + 1));
        printf("Email: %s", pessoaAtual + strlen(pessoaAtual) + 1 + sizeof(int));

        pessoaAtual = pessoaAtual + strlen(pessoaAtual) + 1 + sizeof(int) + strlen(pessoaAtual + strlen(pessoaAtual) + 1 + sizeof(int)) + 1;

        (*(int *)(pbuffer + contadorLaço))++;
    }
}
void buscarPessoa(void *pbuffer)
{
    if (*(int *)(pbuffer + contadorPessoas) == 0)
    {
        printf("\nNenhuma pessoa cadastrada!\n");
        return;
    }

    while (getchar() != '\n');
    printf("\nDigite o email para buscar: ");
    scanf(" %[^\n]", (char *)(pbuffer + emailtemp));
    while (getchar() != '\n')
        ;

    *(int *)(pbuffer + contadorLaço) = 0;
    char *pessoaAtual = (char *)(pbuffer + inicioPessoas);

    while (*(int *)(pbuffer + contadorLaço) < *(int *)(pbuffer + contadorPessoas))
    {

        char *emailPessoa = pessoaAtual + strlen(pessoaAtual) + 1 + sizeof(int);

        if (strcmp(emailPessoa, (char *)(pbuffer + emailtemp)) == 0)
        {
            printf("\nPessoa encontrada!\n");
            printf("Nome: %s\n", pessoaAtual);
            printf("Idade: %d\n", *(int *)(pessoaAtual + strlen(pessoaAtual) + 1));
            printf("Email: %s\n", emailPessoa);
            return;
        }
        pessoaAtual = pessoaAtual + strlen(pessoaAtual) + 1 + sizeof(int) +
                      strlen(pessoaAtual + strlen(pessoaAtual) + 1 + sizeof(int)) + 1;

        (*(int *)(pbuffer + contadorLaço))++;
    }

    printf("\nPessoa nao encontrada!\n");
}
void removerPessoa(void **pbuffer){
    
}