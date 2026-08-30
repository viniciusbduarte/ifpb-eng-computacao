#include <stdio.h>
#include <stdlib.h>

struct sNODE {
    int dado;
    struct sNODE *prox;
};

struct sNODE *ini = NULL, *fim = NULL;
void inserir(int dado);

int main(void) {

    inserir(10);
    inserir(20);
    inserir(30);

    struct sNODE *atual = ini;

    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->prox;
    }
    printf("NULL\n");

    return 0;
}

void inserir(int dado) {
    struct sNODE *novo;
    novo = malloc(sizeof(struct sNODE));

    novo->dado = dado;
                                                                                                                                                                                                                                                                                                                                   

    if (ini == NULL) { // Lista vazia
        ini = novo;
        fim = novo;
    } else {
        fim->prox = novo;
        fim = novo;
    }
}



void buscar( ){

if ( ini != NULL ){


}
}

