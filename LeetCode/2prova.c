#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dados{
    float custo;
    float prioridade;

    struct dados *prox;
};

typedef struct dados celula;

celula *cria_lista(void){

    celula *cabeça;
    cabeça=(celula*)malloc(sizeof(celula));
    if(cabeça==NULL){
        printf("\nerro de memoria");
        return 0;
    }

    cabeça->prox=NULL;

    return cabeça;
}
void ler_arq(celula *cabeça){
    
    FILE *t = fopen("entrada.txt", "r");
    
    if(!t){
        printf("\narquivo nao encontrado");
        return;
    }

    float prioridade;
    float custo;
    
        while(fscanf(t, "%f %f",&prioridade, &custo)==2){
            celula *nova;
            nova=(celula*)malloc(sizeof(celula));
            if(nova==NULL){
                printf("\nerro de memoria");
                return;
            }

            nova->custo=custo;
            nova->prioridade=prioridade;
            nova->prox=NULL;

            celula *anterior=cabeça;
            celula *atual=cabeça->prox;

           while(atual != NULL && ((nova->custo > atual->custo) || 
                                    (nova->custo == atual->custo &&    
                                       nova->prioridade > atual->prioridade))) {
                    

                    anterior=atual;
                    atual=atual->prox;
            }
                 
                anterior->prox=nova;
                nova->prox=atual;
    }
    
        fclose(t);

}
void salvar_arq(celula *cabeça){

    FILE *t = fopen("saida.txt", "w");

    celula *cel;
    cel=cabeça->prox;

    while(cel){
        fprintf(t, "%.2f %.2f\n", cel->prioridade, cel->custo);
        cel=cel->prox;
    }

    fclose(t);


}

int main(){
    
    celula *começo;
    começo=cria_lista();
    
    ler_arq(começo);
    salvar_arq(começo);

}