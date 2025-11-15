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

    void *pbuffer = malloc(inicioPessoas);
    if (!pbuffer)
    {
        printf("Erro de memoria!\n");
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
            removerPessoa(&pbuffer);
            break;
        case 3:
            buscarPessoa(pbuffer);
            break;
        case 4:
            listarPessoas(pbuffer);
            break;
        case 5:
            printf("\nSaindo da agenda.\n");
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
    printf("\n");

    printf("\033[0m===========================================\033[0m\n");
    printf("\033[0m|\033[0m             \033[36mAgenda em buffer\033[0m            \033[0m|\033[0m\n");
    printf("\033[0m|\033[0m                                         \033[0m|\033[0m\n");

    printf("\033[0m|\033[0m   \033[1;32m1\033[0m- Adicionar pessoa                   \033[0m|\033[0m\n");
    printf("\033[0m|\033[0m   \033[1;32m2\033[0m- Remover uma pessoa                 \033[0m|\033[0m\n");
    printf("\033[0m|\033[0m   \033[1;32m3\033[0m- Buscar uma pessoa                  \033[0m|\033[0m\n");
    printf("\033[0m|\033[0m   \033[1;32m4\033[0m- Listar todas as pessoas            \033[0m|\033[0m\n");
    printf("\033[0m|\033[0m   \033[1;31m5\033[0m- Sair da agenda                     \033[0m|\033[0m\n");

    printf("\033[0m|\033[0m                                         \033[0m|\033[0m\n");
    printf("\033[0m===========================================\033[0m\n");

    printf("\033[5;37mDigite sua escolha:\033[0m ");
}

void adicionarPessoa(void **pbuffer)
{
    while (getchar() != '\n')
        ;

    printf("\n\nDigite o nome: ");
    scanf(" %29[^\n]", (char *)(*pbuffer + nometemp));
    while (getchar() != '\n')
        ;

    printf("Digite a idade: ");
    scanf("%d", (int *)(*pbuffer + idadetemp));
    while (getchar() != '\n')
        ;

    printf("Digite o email: ");
    scanf(" %29[^\n]", (char *)(*pbuffer + emailtemp));
    while (getchar() != '\n')
        ;

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

    *(int *)(*pbuffer + escolhaMenu) = destino - (char *)(*pbuffer);

    void *novoPbuffer = realloc(*pbuffer,
                                ((char *)destino - (char *)(*pbuffer)) +
                                    strlen((char *)(*pbuffer + nometemp)) + 1 +
                                    sizeof(int) +
                                    strlen((char *)(*pbuffer + emailtemp)) + 1);

    if (!novoPbuffer)
    {
        printf("\n\n--ERRO DE MEMÓRIA--\n\n");
        return;
    }

    *pbuffer = novoPbuffer;

    destino = (char *)(*pbuffer) + *(int *)(*pbuffer + escolhaMenu);

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

    while (getchar() != '\n')
        ;
    printf("\nDigite o email para buscar: ");
    scanf(" %29[^\n]", (char *)(pbuffer + emailtemp));
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
void removerPessoa(void **pbuffer)
{
    if (*(int *)(*pbuffer + contadorPessoas) == 0)
    {
        printf("\nNenhuma pessoa na agenda para remover!\n");
        return;
    }

    while (getchar() != '\n');
    printf("\nDigite o email para remover: ");
    scanf(" %29[^\n]", (char *)(*pbuffer + emailtemp));
    while (getchar() != '\n');

    *(int *)(*pbuffer + contadorLaço) = 0;

    char *pessoa = (char *)(*pbuffer + inicioPessoas);

    while (*(int *)(*pbuffer + contadorLaço) < *(int *)(*pbuffer + contadorPessoas))
    {
        char *idade_ptr = pessoa + strlen(pessoa) + 1;
        char *email = idade_ptr + sizeof(int);

        if (strcmp(email, (char *)(*pbuffer + emailtemp)) == 0)
        {
            char *proxima = email + strlen(email) + 1;

            char *fim = (char *)(*pbuffer + inicioPessoas);

            *(int *)(*pbuffer + escolhaMenu) = 0;

            while (*(int *)(*pbuffer + escolhaMenu) < *(int *)(*pbuffer + contadorPessoas))
            {
                char *temp_idade = fim + strlen(fim) + 1;
                char *temp_email = temp_idade + sizeof(int);
                fim = temp_email + strlen(temp_email) + 1;

                (*(int *)(*pbuffer + escolhaMenu))++;
            }

            memmove(pessoa, proxima, fim - proxima);
            (*(int *)(*pbuffer + contadorPessoas))--;

            printf("\nPessoa removida!\n");
            return;
        }

        pessoa = email + strlen(email) + 1;
        
        (*(int *)(*pbuffer + contadorLaço))++;
    }
    printf("\nPessoa nao encontrada!\n");
}
