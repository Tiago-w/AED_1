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

#define tamanhoNome (emailT + sizeof(char) * 50)
#define tamanhoEmail (tamanhoNome + sizeof(int))

#define pessoa (tamanhoEmail + sizeof(int))

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
            // listarPessoas();
            break;
        case 5:
            printf("saindo but\n");
            break;
        default:
            printf("opcao invalida\n");
            break;
        }

    } while (*(int *)(pbuffer + escolhaMenu) != 5);

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
    while (getchar() != '\n');

    printf("digita a idade but:\n");
    scanf("%d", (int *)(*pbuffer + idadeT));
    while (getchar() != '\n');

    printf("digita o email but:\n");
    scanf(" %[^\n]", (char *)(*pbuffer + emailT));
    while (getchar() != '\n');

    *(int *)(*pbuffer + tamanhoNome) = strlen((char *)(*pbuffer + nomeT) + 1);
    *(int *)(*pbuffer + tamanhoEmail) = strlen((char *)(*pbuffer + emailT) + 1);

    *(int *)(*pbuffer + contadorLaço) = 0;
    *(int *)(*pbuffer + escolhaMenu) = 0;

    while (*(int *)(*pbuffer + escolhaMenu) < *(int *)(*pbuffer + contadorPessoas))
    {
        //posição atual + tamanho do nome
        *(int *)(*pbuffer + contadorLaço) = *(int *)(*pbuffer + contadorLaço) +
                                                     strlen((char *)(*pbuffer + pessoa) + 
                                                                *(int *)(*pbuffer + contadorLaço)) + 1;

        //pula idade
        *(int *)(*pbuffer + contadorLaço) = *(int *)(*pbuffer + contadorLaço) + sizeof(int);

        //pega posição atual + tamanho do email
        *(int *)(*pbuffer + contadorLaço) = *(int *)(*pbuffer + contadorLaço) +
                                                    strlen((char *)(*pbuffer + pessoa) +        
                                                             *(int *)(*pbuffer + contadorLaço)) + 1;

        (*(int *)(*pbuffer + escolhaMenu))++;
    }

    void *pbufferT = realloc(*pbuffer, pessoa + *(int *)(*pbuffer + contadorLaço) +
                                                      *(int *)(*pbuffer + tamanhoNome) +
                                                                       sizeof(int) +
                                                                             *(int *)(*pbuffer + tamanhoEmail));

    if (!pbufferT)
    {
        printf("erro de memoria\n");
        return;
    }

    *pbuffer = pbufferT;

    // copia nome
    memcpy((char *)(*pbuffer + pessoa) + *(int *)(*pbuffer + contadorLaço),
           (char *)(*pbuffer + nomeT),
           *(int *)(*pbuffer + tamanhoNome ));

    *(int *)(*pbuffer + contadorLaço) = *(int *)(*pbuffer + contadorLaço) + *(int *)(*pbuffer + tamanhoNome);

    // copia idade
    memcpy((char *)(*pbuffer + pessoa) + *(int *)(*pbuffer + contadorLaço),
           (int *)(*pbuffer + idadeT),
           sizeof(int));

    *(int *)(*pbuffer + contadorLaço) = *(int *)(*pbuffer + contadorLaço) + sizeof(int);

    // copia email
    memcpy((char *)(*pbuffer + pessoa) + *(int *)(*pbuffer + contadorLaço),
           (char *)(*pbuffer + emailT),
           *(int *)(*pbuffer + tamanhoEmail));

    (*(int *)(*pbuffer + contadorPessoas))++;

    printf("deu\n");
}

/*void *pbufferT = realloc(*pbuffer, pessoa + ((*(int *)(*pbuffer + contadorPessoas) + 1) * gavetaPessoa));

if (!pbufferT)
{
    printf("erro de memoria\n");
    return;
}

*pbuffer = pbufferT;
memcpy(
    (char *)(*pbuffer + pessoa) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa),
    (char *)(*pbuffer + nomeT),
    nome);

memcpy(
    (char *)(*pbuffer + pessoa) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa) + nome,
    (int*)(*pbuffer+idadeT),
    idade);

memcpy(
    (char *)(*pbuffer + pessoa) + (*(int *)(*pbuffer + contadorPessoas) * gavetaPessoa) + nome + idade,
    (char *)(*pbuffer + email),
    email);

(*(int *)(*pbuffer + contadorPessoas))++;

printf("deu\n");
}*/
