#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sNODE {
    char emocao[18];
    int freq;
    struct sNODE *ant;
    struct sNODE *prox;
};

struct sLISTA {
    struct sNODE *ini, *fim;
};

typedef struct sLISTA LISTA;

void inicializar(LISTA *lst);
void inserir(LISTA *lst, const char *emocao);
void imprimir(LISTA *lst);
void emocao_no_controle(LISTA *lst, const char *emocao);
void emocao_dominante(LISTA *lst);
//void emocao_submissiva(LISTA *lst);



int main() {
    LISTA lst1;

    inicializar(&lst1);

    inserir(&lst1, "felicidade");// inicializar tipo de emoção, freq inicial = 0;
      inserir(&lst1, "raiva");// inicializar tipo de emoção, freq inicial = 0;

    emocao_no_controle(&lst1, "felicidade"); //adicionar +1 na freq
    emocao_no_controle(&lst1, "raiva"); //adicionar +1 na freq
    
    emocao_dominante(&lst1);
   // emocao_submissiva(&lst1);

   

    imprimir(&lst1);


    return 0;
}

void inicializar(LISTA *lst) {
    lst->ini = lst->fim = NULL;
}

void inserir(LISTA *lst, const char *emocao) {
    struct sNODE *novo = (struct sNODE *)malloc(sizeof(struct sNODE));

    strcpy(novo->emocao, emocao);
    novo->freq = 0;
    novo->ant = NULL;
    novo->prox = NULL;

    if (!lst->ini) {
        lst->ini = lst->fim = novo;
    } else {
        lst->fim->prox = novo;
        lst->fim = novo;
    }
}

void emocao_no_controle(LISTA *lst, const char *emocao){
    struct sNODE *aux = lst->ini;

    while(aux){
            if (strcmp(aux->emocao, emocao ) == 0) {
                aux->freq++;
                
            }
            aux = aux->prox;
    }
}
void emocao_dominante(LISTA *lst) {
    struct sNODE *aux = lst->ini;
    struct sNODE *dominante = NULL;
    int maior_frequencia = 0;

    while (aux) {
        if (aux->freq > maior_frequencia) {
            maior_frequencia = aux->freq;
            dominante = aux;
        }
        aux = aux->prox;
    }

    if (dominante) {
        printf("Emoção dominante: %s com frequência %d\n", dominante->emocao, dominante->freq);
    } else {
        printf("Lista vazia ou erro na lista\n");
    }
}





void imprimir(LISTA *lst) {
    struct sNODE *aux = lst->ini;
    printf("[");
    while (aux) {
        printf(" %s %d", aux->emocao, aux->freq);
        aux = aux->prox;
    }
    printf(" ]\n");
}

