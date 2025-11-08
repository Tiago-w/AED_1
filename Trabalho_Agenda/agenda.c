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
    while (getchar() != '\n');

    printf("\n\nDigite o nome: ");
    scanf("%[^\n]", ((char *)(*pbuffer + nometemp)));
    while (getchar() != '\n');

    printf("Digite a idade: ");
    scanf("%d", (int *)(*pbuffer + idadetemp));
    while (getchar() != '\n');

    printf("Digite o email: ");
    scanf("%[^\n]", ((char *)(*pbuffer + emailtemp)));
    while (getchar() != '\n');


    void *tamanhoNome = malloc(sizeof(int));
    void *tamanhoEmail = malloc(sizeof(int));
    *(int *)tamanhoNome = strlen((char *)(*pbuffer + nometemp)) + 1;  
    *(int *)tamanhoEmail = strlen((char *)(*pbuffer + emailtemp)) + 1;
    
    void *tamanhoTotal = malloc(sizeof(int));
    *(int *)tamanhoTotal = *(int *)tamanhoNome + sizeof(int) + *(int *)tamanhoEmail;


    void *offsetAtual = malloc(sizeof(int));
    *(int *)offsetAtual = 0;
    
    *(int *)(*pbuffer + contadorLaço) = 0;
    while (*(int *)(*pbuffer + contadorLaço) < *(int *)(*pbuffer + contadorPessoas))
    {
        void *pessoaAtual = *pbuffer + inicioPessoas + *(int *)offsetAtual;
        
        void *tamanhoNomeAtual = malloc(sizeof(int));
        *(int *)tamanhoNomeAtual = strlen((char *)pessoaAtual) + 1;
        
        void *emailAtual = pessoaAtual + *(int *)tamanhoNomeAtual + sizeof(int);
        
        if (strcmp((char *)emailAtual, (char *)(*pbuffer + emailtemp)) == 0)
        {
            printf("\n\nJa existe uma pessoa cadastrada com este email!\n");
            free(tamanhoNome);
            free(tamanhoEmail);
            free(tamanhoTotal);
            free(offsetAtual);
            free(tamanhoNomeAtual);
            return;
        }
        
        void *tamanhoEmailAtual = malloc(sizeof(int));
        *(int *)tamanhoEmailAtual = strlen((char *)emailAtual) + 1;
        
        *(int *)offsetAtual += *(int *)tamanhoNomeAtual + sizeof(int) + *(int *)tamanhoEmailAtual;
        
        free(tamanhoNomeAtual);
        free(tamanhoEmailAtual);
        
        (*(int *)(*pbuffer + contadorLaço))++;
    }

    void *tamanhoNovoBuffer = malloc(sizeof(int));
    *(int *)tamanhoNovoBuffer = inicioPessoas + *(int *)offsetAtual + *(int *)tamanhoTotal;
    
    *pbuffer = realloc(*pbuffer, *(int *)tamanhoNovoBuffer);

    if (!(*pbuffer))
    {
        printf("\n\nErro de memoria!\n");
        free(tamanhoNome);
        free(tamanhoEmail);
        free(tamanhoTotal);
        free(offsetAtual);
        free(tamanhoNovoBuffer);
        return;
    }

    void *novaPessoa = *pbuffer + inicioPessoas + *(int *)offsetAtual;

    strcpy((char *)novaPessoa, (char *)(*pbuffer + nometemp));
    *(int *)(novaPessoa + *(int *)tamanhoNome) = *(int *)(*pbuffer + idadetemp);
    strcpy((char *)(novaPessoa + *(int *)tamanhoNome + sizeof(int)), (char *)(*pbuffer + emailtemp));

    (*(int *)(*pbuffer + contadorPessoas))++;

    printf("\n\nPessoa adicionada!\n");
    
    free(tamanhoNome);
    free(tamanhoEmail);
    free(tamanhoTotal);
    free(offsetAtual);
    free(tamanhoNovoBuffer);
}
void listarPessoas(void *pbuffer)
{
    if (*(int *)(pbuffer + contadorPessoas) == 0)
    {
        printf("\n\nAgenda vazia!\n");
        return;
    }

    *(int *)(pbuffer + contadorLaço) = 0;

    void *offsetAtual = malloc(sizeof(int));
    *(int *)offsetAtual = 0;

    while (*(int *)(pbuffer + contadorLaço) < *(int *)(pbuffer + contadorPessoas))
    {
        void *pessoaAtual = pbuffer + inicioPessoas + *(int *)offsetAtual;

        void *tamanhoNomeAtual = malloc(sizeof(int));
        *(int *)tamanhoNomeAtual = strlen((char *)pessoaAtual) + 1;

        void *nomeAtual = pessoaAtual;
        void *idadeAtual = pessoaAtual + *(int *)tamanhoNomeAtual;
        void *emailAtual = pessoaAtual + *(int *)tamanhoNomeAtual + sizeof(int);

        printf("\n\nCadastro [%d]\n", *(int *)(pbuffer + contadorLaço) + 1);
        printf("Nome: %s\n", (char *)nomeAtual);
        printf("Idade: %d\n", *(int *)idadeAtual);
        printf("Email: %s\n", (char *)emailAtual);

        void *tamanhoEmailAtual = malloc(sizeof(int));
        *(int *)tamanhoEmailAtual = strlen((char *)emailAtual) + 1;

        *(int *)offsetAtual += *(int *)tamanhoNomeAtual + sizeof(int) + *(int *)tamanhoEmailAtual;

        free(tamanhoNomeAtual);
        free(tamanhoEmailAtual);

        (*(int *)(pbuffer + contadorLaço))++;
    }

    free(offsetAtual);
}

void buscarPessoa(void *pbuffer)
{
    if (*(int *)(pbuffer + contadorPessoas) == 0)
    {
        printf("\n\nAgenda vazia!\n");
        return;
    }

    while (getchar() != '\n');

    printf("\n\nDigite o email da pessoa: ");
    scanf("%[^\n]", ((char *)(pbuffer + emailtemp)));
    while (getchar() != '\n');

    void *offsetAtual = malloc(sizeof(int));
    *(int *)offsetAtual = 0;
    void *encontrado = malloc(sizeof(int));
    *(int *)encontrado = 0;
    
    *(int *)(pbuffer + contadorLaço) = 0;
    while (*(int *)(pbuffer + contadorLaço) < *(int *)(pbuffer + contadorPessoas))
    {
        void *pessoaAtual = pbuffer + inicioPessoas + *(int *)offsetAtual;

        void *tamanhoNomeAtual = malloc(sizeof(int));
        *(int *)tamanhoNomeAtual = strlen((char *)pessoaAtual) + 1;

        void *nomeAtual = pessoaAtual;
        void *idadeAtual = pessoaAtual + *(int *)tamanhoNomeAtual;
        void *emailAtual = pessoaAtual + *(int *)tamanhoNomeAtual + sizeof(int);

        if (strcmp((char *)emailAtual, (char *)(pbuffer + emailtemp)) == 0)
        {
            printf("\n\nPessoa encontrada!\n");
            printf("Nome: %s\n", (char *)nomeAtual);
            printf("Idade: %d\n", *(int *)idadeAtual);
            printf("Email: %s\n", (char *)emailAtual);
            *(int *)encontrado = 1;
            free(tamanhoNomeAtual);
            break;
        }

        void *tamanhoEmailAtual = malloc(sizeof(int));
        *(int *)tamanhoEmailAtual = strlen((char *)emailAtual) + 1;

        *(int *)offsetAtual += *(int *)tamanhoNomeAtual + sizeof(int) + *(int *)tamanhoEmailAtual;

        free(tamanhoNomeAtual);
        free(tamanhoEmailAtual);

        (*(int *)(pbuffer + contadorLaço))++;
    }

    if (*(int *)encontrado == 0)
    {
        printf("\n\nPessoa nao encontrada!\n");
    }

    free(offsetAtual);
    free(encontrado);
}

void removerPessoa(void **pbuffer)
{
    if (*(int *)(*pbuffer + contadorPessoas) == 0)
    {
        printf("\n\nAgenda vazia!\n");
        return;
    }

    while (getchar() != '\n');

    printf("\n\nDigite o email da pessoa a remover: ");
    scanf("%[^\n]", ((char *)(*pbuffer + emailtemp)));
    while (getchar() != '\n');

    *(int *)(*pbuffer + contadorLaço) = 0;
    void *offsetAtual = malloc(sizeof(int));
    *(int *)offsetAtual = 0;
    void *encontrado = malloc(sizeof(int));
    *(int *)encontrado = 0;
    void *tamanhoPessoaRemover = malloc(sizeof(int));

    while (*(int *)(*pbuffer + contadorLaço) < *(int *)(*pbuffer + contadorPessoas))
    {
        void *pessoaAtual = *pbuffer + inicioPessoas + *(int *)offsetAtual;

        void *tamanhoNomeAtual = malloc(sizeof(int));
        *(int *)tamanhoNomeAtual = strlen((char *)pessoaAtual) + 1;

        void *emailAtual = pessoaAtual + *(int *)tamanhoNomeAtual + sizeof(int);

        if (strcmp((char *)emailAtual, (char *)(*pbuffer + emailtemp)) == 0)
        {
            *(int *)encontrado = 1;

            void *tamanhoEmailAtual = malloc(sizeof(int));
            *(int *)tamanhoEmailAtual = strlen((char *)emailAtual) + 1;

            *(int *)tamanhoPessoaRemover = *(int *)tamanhoNomeAtual + sizeof(int) + *(int *)tamanhoEmailAtual;

            void *offsetProximo = malloc(sizeof(int));
            *(int *)offsetProximo = *(int *)offsetAtual + *(int *)tamanhoPessoaRemover;

            void *offsetFinal = malloc(sizeof(int));
            *(int *)offsetFinal = 0;

            void *contadorTemp = malloc(sizeof(int));
            *(int *)contadorTemp = *(int *)(*pbuffer + contadorLaço) + 1;

            while (*(int *)contadorTemp < *(int *)(*pbuffer + contadorPessoas))
            {
                void *pessoa = *pbuffer + inicioPessoas + *(int *)offsetProximo;
                void *tamNome = malloc(sizeof(int));
                *(int *)tamNome = strlen((char *)pessoa) + 1;
                void *tamEmail = malloc(sizeof(int));
                *(int *)tamEmail = strlen((char *)(pessoa + *(int *)tamNome + sizeof(int))) + 1;

                *(int *)offsetFinal += *(int *)tamNome + sizeof(int) + *(int *)tamEmail;
                *(int *)offsetProximo += *(int *)tamNome + sizeof(int) + *(int *)tamEmail;

                free(tamNome);
                free(tamEmail);
                (*(int *)contadorTemp)++;
            }

            if (*(int *)offsetFinal > 0)
            {
                void *origem = *pbuffer + inicioPessoas + *(int *)offsetAtual + *(int *)tamanhoPessoaRemover;
                void *destino = *pbuffer + inicioPessoas + *(int *)offsetAtual;
                memmove(destino, origem, *(int *)offsetFinal);
            }

            void *novoTamanho = malloc(sizeof(int));
            *(int *)novoTamanho = inicioPessoas + *(int *)offsetAtual + *(int *)offsetFinal;
            *pbuffer = realloc(*pbuffer, *(int *)novoTamanho);

            (*(int *)(*pbuffer + contadorPessoas))--;

            printf("\n\nPessoa removida com sucesso!\n");

            free(tamanhoEmailAtual);
            free(offsetProximo);
            free(offsetFinal);
            free(contadorTemp);
            free(novoTamanho);
            free(tamanhoNomeAtual);
            break;
        }

        void *tamanhoEmailAtual = malloc(sizeof(int));
        *(int *)tamanhoEmailAtual = strlen((char *)emailAtual) + 1;

        *(int *)offsetAtual += *(int *)tamanhoNomeAtual + sizeof(int) + *(int *)tamanhoEmailAtual;

        free(tamanhoNomeAtual);
        free(tamanhoEmailAtual);

        (*(int *)(*pbuffer + contadorLaço))++;
    }

    if (*(int *)encontrado == 0)
    {
        printf("\n\nPessoa nao encontrada!\n");
    }

    free(offsetAtual);
    free(encontrado);
    free(tamanhoPessoaRemover);
}