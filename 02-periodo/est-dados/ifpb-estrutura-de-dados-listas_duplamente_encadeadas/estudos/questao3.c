#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sNODE {
    char emocao[18];
    struct sNODE *prox;
};

struct sLISTA {
    struct sNODE *ini, *fim;
};

typedef struct sLISTA LISTA;

void inicializar(LISTA *lst);
void inserir(LISTA *lst, const char *emocao);
void imprimir(LISTA *lst);

void preencher_lst3(LISTA *lst1, LISTA *lst2, LISTA *lst3);

int main() {
    LISTA lst1, lst2, lst3;

    inicializar(&lst1);
    inicializar(&lst2);
    inicializar(&lst3);

    inserir(&lst1, "felicidade");
    inserir(&lst2, "raiva");

    preencher_lst3(&lst1, &lst2, &lst3);

    imprimir(&lst1);
    imprimir(&lst2);
    imprimir(&lst3);



    return 0;
}

void inicializar(LISTA *lst) {
    lst->ini = lst->fim = NULL;
}

void inserir(LISTA *lst, const char *emocao) {
    struct sNODE *novo = (struct sNODE *)malloc(sizeof(struct sNODE));

    strcpy(novo->emocao, emocao);
    novo->prox = NULL;

    if (!lst->ini) {
        lst->ini = lst->fim = novo;
    } else {
        lst->fim->prox = novo;
        lst->fim = novo;
    }
}

void preencher_lst3(LISTA *lst1, LISTA *lst2, LISTA *lst3) {
    struct sNODE *aux1 = lst1->ini;
    struct sNODE *aux2 = lst2->ini;

    while (aux1) {
        if (strlen(aux1->emocao) >= strlen(aux2->emocao)) {
            inserir(lst3, aux1->emocao);
            aux1 = aux1->prox;
            aux2 = aux2->prox;
        } else {
            inserir(lst3, aux2->emocao);
            aux1 = aux1->prox;
            aux2 = aux2->prox;
        }
    }
}

void imprimir(LISTA *lst) {
    struct sNODE *aux = lst->ini;
    printf("[");
    while (aux) {
        printf(" %s", aux->emocao);
        aux = aux->prox;
    }
    printf(" ]\n");
}



int emocao_no_controle(LISTA *emocoes, const char *emocao) {
    if (strcmp(cargo, "gerente") == 0) return gerentes;
    if (strcmp(cargo, "supervisor") == 0) return supervisores;
    if (strcmp(cargo, "peao") == 0) return peoes;  
    return NULL;
}
