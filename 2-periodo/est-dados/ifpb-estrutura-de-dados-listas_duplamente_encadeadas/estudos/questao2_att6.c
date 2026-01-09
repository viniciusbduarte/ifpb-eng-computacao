/*==============================================================================
 * Nome do Programa: Listas Duplamente Encadeadas 
 * Descrição       : Manipulando mais de uma lista Duplamente Encadeada 
 * Autor           : Vinicius Batista Duarte
 * Data de Criação : 14/12/24
 * Última Modificação: 14/12/24
 * Versão          : 1.0
 *==============================================================================
 */ 

//========================= BIBLIOTECAS =======================================
#include <stdio.h>
#include <stdlib.h>

//========================= CONSTANTES GLOBAIS ===============================


//========================= VARIÁVEIS GLOBAIS ===============================

struct sNODE{
  int dado;  
  struct sNODE *ant;
  struct sNODE *prox;
};

struct sLISTA{
  struct sNODE *ini, *fim;
};

typedef struct sLISTA LISTA;  

//========================= PROTÓTIPOS DE FUNÇÕES ============================

void inicializar(LISTA *lst);
void apagar(LISTA *lst);
void inserir(LISTA *lst, int dado);
void inserir_ord(LISTA *lst, int dado);
void remover(LISTA *lst, int dado);
struct sNODE *buscar(LISTA *lst, int dado);
//int obter(struct sNODE *node);
//int tamanho(LISTA *lst);
void imprimir(LISTA *lst);

//========================= FUNÇÃO PRINCIPAL ================================

int main(){
  LISTA lst1;
  LISTA lst2;
  inicializar(&lst1);
  inicializar(&lst2);

  inserir_ord(&lst1, 200);
  inserir_ord(&lst1, 200);
  inserir_ord(&lst1, 400);
  inserir_ord(&lst1, 100);
  inserir_ord(&lst1, 300);
  inserir_ord(&lst1, 100);

  inserir_ord(&lst2, 200);
  
  imprimir(&lst1);
  imprimir(&lst2);

  apagar(&lst1);

  imprimir(&lst1);


  return 0;
}

//========================= IMPLEMENTAÇÃO DAS FUNÇÕES ========================

void inicilizar(LISTA *lst){
  lst->ini = lst->fim = NULL;
}

/*------------------------------------------------------------------------------inserir------------------------------------------------------------------------------------------------*/

void inserir(LISTA *lst, int dado){
  struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE));

  
  novo->dado = dado;
  novo->ant = NULL;
  novo->prox = NULL;

  if (!lst->ini)
	  lst->ini = lst->fim = novo;

  else{
	  lst->fim->prox = novo;
	  novo->ant = lst->fim;
	  lst->fim = novo;
  }
}

/*------------------------------------------------------------------------------inserir_ord------------------------------------------------------------------------------------------------*/

void inserir_ord(LISTA *lst, int dado) {
    struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE));
    struct sNODE *aux;

    novo->dado = dado;
    novo->ant = NULL;
    novo->prox = NULL;

    // Caso 1: Lista vazia
    if (!lst->ini) {
        lst->ini = lst->fim = novo;
        return;
    }

    // Caso 2: Inserção no início
    if (dado < lst->ini->dado) {
        novo->prox = lst->ini;
        lst->ini->ant = novo;
        lst->ini = novo;
        return;
    }

    // Caso 3: Inserção no final
    if (dado >= lst->fim->dado) {
        novo->ant = lst->fim;
        lst->fim->prox = novo;
        lst->fim = novo;
        return;
    }

    // Caso 4: Inserção no meio
    aux = lst->ini;
    while (aux) {
        if (dado < aux->dado) {
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
            return;
        }
        aux = aux->prox;
    }
}



void imprimir(LISTA *lst){
  struct sNODE *aux = lst->ini;
  printf("[");
  while(aux){
      printf(" %d", aux->dado);
      aux = aux->ant;
  }
  printf(" ]\n");
}