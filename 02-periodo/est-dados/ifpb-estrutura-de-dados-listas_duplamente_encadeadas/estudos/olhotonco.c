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
#include <string.h>

//========================= CONSTANTES GLOBAIS =================================
#define TAM 30

//========================= VARIÁVEIS GLOBAIS ==================================
struct sNODE {
    char nome[TAM];
    int cargo, salario;
    struct sNODE *ant;
    struct sNODE *prox;
};

struct sLISTA {
    struct sNODE *ini, *fim;
};

typedef struct sLISTA LISTA;

//========================= PROTÓTIPOS DE FUNÇÕES ==============================
void inicializar(LISTA *lst);
void apagar(LISTA *lst);
void inserir_ord(LISTA *lst, const char *nome, const char *cargo, int salario_funcionario);
int cargo_int(const char *cargo);
void imprimir(LISTA *lst);

//========================= FUNÇÃO PRINCIPAL ===================================
int main() {
    LISTA empresa1;
    inicializar(&empresa1);

    inserir_ord(&empresa1, "fulanogerente", "gerente", 1000);
    inserir_ord(&empresa1, "fulanosupervisor", "supervisor", 900);
    inserir_ord(&empresa1, "fulanopeao", "peao", 800);

    imprimir(&empresa1);

    apagar(&empresa1);
    return 0;
}

//========================= IMPLEMENTAÇÃO DAS FUNÇÕES ==========================
void inicializar(LISTA *lst) {
    /*
     * Descrição:
     * Inicializa uma lista, atribuindo NULL para os ponteiros ini e fim.
     */
    lst->ini = lst->fim = NULL;
}

void apagar(LISTA *lst) {
    /*
     * Descrição:
     * Libera a memória ocupada pelos nós da lista e reinicializa seus ponteiros.
     */
    struct sNODE *aux = lst->ini, *temp;
    while (aux) {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }
    lst->ini = lst->fim = NULL;
}


void inserir_ord(LISTA *lst, const char *nome, const char *cargo, int salario_funcionario) {
    /*
     * Descrição:
     * Insere um dado do tipo int na lista de maneira sequencial( ordem de inserção ).
     */
  struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE));

  
    strcpy(novo->nome, nome);
    novo->cargo = cargo_int(cargo);
    novo->salario = salario_funcionario;
    novo->ant = novo->prox = NULL;

  if (!lst->ini)
	  lst->ini = lst->fim = novo;

  else{
	  lst->fim->prox = novo;
	  novo->ant = lst->fim;
	  lst->fim = novo;
  }
}







int cargo_int(const char *cargo) {
    /*
     * Descrição:
     * Converte o cargo de string para um valor numérico para ordenar.
     * Retorna:
     * - 1 para "gerente"
     * - 2 para "supervisor"
     * - 3 para "peao"
     */
    if (strcmp(cargo, "gerente") == 0) return 1;
    if (strcmp(cargo, "supervisor") == 0) return 2;
    if (strcmp(cargo, "peao") == 0) return 3;
    return 0;
}





void imprimir(LISTA *lst) {
    /*
     * Descrição:
     * Imprime todos os elementos da lista na tela.
     */
    struct sNODE *aux = lst->ini;
    printf("[\n");
    while (aux) {
        printf(" Nome: %s, Cargo: %d, Salário: %d\n", aux->nome, aux->cargo, aux->salario);
        aux = aux->prox;
    }
    printf("]\n");
}
