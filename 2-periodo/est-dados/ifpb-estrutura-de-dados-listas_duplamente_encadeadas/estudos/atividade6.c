/*==============================================================================
 * Nome do Programa: Listas Duplamente Encadeadas 
 * Descrição       : Manipulando mais de uma lista Duplamente Encadeada 
 * Autor           : Vinicius Batista Duarte
 * Data de Criação : 14/12/24
 * Última Modificação: 14/12/24
 * Versão          : 1.0
 *==============================================================================
 */ 

//========================= BIBLIOTECAS ========================================
#include <stdio.h>
#include <stdlib.h>

//========================= CONSTANTES GLOBAIS =================================

//========================= VARIÁVEIS GLOBAIS ==================================

struct sNODE{
  int dado;  
  struct sNODE *ant;
  struct sNODE *prox;
};

struct sLISTA{
  struct sNODE *ini, *fim;
};

typedef struct sLISTA LISTA;  


//========================= PROTÓTIPOS DE FUNÇÕES ==============================

void inicializar(LISTA *lst);
void apagar(LISTA *lst);
void inserir(LISTA *lst, int dado);
void inserir_ord(LISTA *lst, int dado);
void remover(LISTA *lst, int dado);
struct sNODE *buscar(LISTA *lst, int dado);
int obter(struct sNODE *node);
int tamanho(LISTA *lst);
void imprimir(LISTA *lst);


//========================= FUNÇÃO PRINCIPAL ===================================


int main(){

  return 0;
}



//========================= IMPLEMENTAÇÃO DAS FUNÇÕES ==========================


void inicializar(LISTA *lst){
    /*
     * Descrição:
     * Inicializando uma lista. Ex: lst1 , lst2 , lst3... 
     */
  lst->ini = lst->fim = NULL;
}

void apagar(LISTA *lst){
    /*
     * Descrição:
     * Liber o espaço de todos os elementos da lista e reinicializa a lista aterrando ini e fim. 
     */
  struct sNODE *aux = lst->ini, *ant;
 
  while (aux){
	ant = aux;
	aux = aux->prox;
	free(ant);
  }
  lst->ini = lst->fim = NULL; 
}

void inserir(LISTA *lst, int dado){
    /*
     * Descrição:
     * Insere um dado do tipo int na lista de maneira sequencial( ordem de inserção ).
     */
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

void inserir_ord(LISTA *lst, int dado) {
    /*
     * Descrição:
     * Inserir de maneira ordenada. Ex: [ 12 , 25 , 28 , 40 ].
     */
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
      aux = aux->prox;
  }
  printf(" ]\n");
}

void remover(LISTA *lst, int dado) {
    struct sNODE *aux = lst->ini;
       /*
     * Descrição:
     * Remove o nó escolhido, caso tenha.
     */

    while (aux) {
         if (aux->dado == dado) {
            // Caso 1: Remover o único nó da lista
            if (aux == lst->ini && aux == lst->fim) {
                lst->ini = lst->fim = NULL;
            }
            // Caso 2: Remover o primeiro nó
            else if (aux == lst->ini) {
                lst->ini = aux->prox;
                lst->ini->ant = NULL;
            }
            // Caso 3: Remover o último nó
            else if (aux == lst->fim) {
                lst->fim = aux->ant;
                lst->fim->prox = NULL;
            }
            // Caso 4: Remover um nó no meio
            else {
                aux->ant->prox = aux->prox;
                aux->prox->ant = aux->ant;
            }

            // Liberar o nó
            struct sNODE *temp = aux;
            aux = aux->prox;  // Avançar antes de liberar
            free(temp);
        } else {
            // Continuar para o próximo nó
            aux = aux->prox;
        }
    }
}

struct sNODE *buscar(LISTA *lst, int dado){
    /*
     * Descrição:
     * Retorna o nó com o dado desejado. ( Pode ser utilizado em void remover() para encontrar o nó desejado )
     */
  struct sNODE *aux = lst->ini;

  while (aux){
	if (dado == aux->dado)
      	return aux;
	aux = aux->prox;
  }

  return NULL;

}

int obter(struct sNODE *node){
    /*
     * Descrição:
     * Recebe um ponteiro para um nó e retorna seu dado. ( o nó recebido vem da função buscar)
     */
  if (!node){
	printf("Erro ao obter dado. Ponteiro invalido.");
	exit(0);
  }
 
  return node->dado;
}

int tamanho(LISTA *lst){
    /*
     * Descrição:
     * Retorna a quantidade de itens na lista. 
     */
  struct sNODE *aux = lst->ini;
  int tam = 0;
 
  while (aux){
	tam++;
	aux = aux->prox;
  }
 
  return tam;
}