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

#define nomeT (contadorLaço + sizeof(int))
#define idadeT (nomeT + (sizeof(char) * 50))
#define emailT (idadeT + sizeof(int))

#define pessoa (emailT + (sizeof(char) * 50))

void exibirMenu(void);
void adicionarPessoa(void **pbuffer);
// void removerPessoa();
// void buscarPessoa();
// void listarPessoas();

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

    int *escolha = (int *)(pbuffer + escolhaMenu);

    do
    {

        exibirMenu();
        scanf("%d", escolha);

        switch (*escolha)
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
            // listarPessoas();
            break;
        case 5:
            printf("saindo but\n");
            break;
        default:
            printf("opcao invalida\n");
            break;
        }

    } while (*escolha != 5);

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

    printf("digita o nome but:\n");
    scanf(" %[^\n]", (char *)(*pbuffer + nomeT));
    while (getchar() != '\n')
        ;

    printf("digita a idade but:\n");
    scanf("%d", (int *)(*pbuffer + idadeT));
    while (getchar() != '\n')
        ;

    printf("digita o email but:\n");
    scanf(" %[^\n]", (char *)(*pbuffer + emailT));
    while (getchar() != '\n')
        ;

    void *pbufferT = realloc(*pbuffer, pessoa + ((*(int *)(*pbuffer + contadorPessoas) + 1) * gavetaPessoa));

    if (!pbufferT)
    {
        printf("erro de memoria\n");
        return;
    }

    *pbuffer = pbufferT;
    memcpy(
        (char *)(*pbuffer + pessoa) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa),
        (char *)(*pbuffer + nomeT),
        sizeof(char)*nomeT);

    memcpy(
        (char *)(*pbuffer + pessoa) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa) + nome,
        (int *)(*pbuffer + idadeT),
        sizeof(int));

    memcpy(
        (char *)(*pbuffer + pessoa) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa) + nome + idade,
        (char *)(*pbuffer + emailT),
        sizeof(char)*emailT);

    (*(int *)(*pbuffer + contadorPessoas))++;

    printf("deu\n");
}
