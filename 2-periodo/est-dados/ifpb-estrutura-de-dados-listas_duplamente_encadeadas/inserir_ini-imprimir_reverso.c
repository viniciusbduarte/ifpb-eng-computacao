/*==============================================================================
 * Nome do Programa: Listas Duplamente Encadeadas ( funções inserir_ini e imprimir_reverso )
 * Descrição       : Funções para inserir elemento no inicio da lista e para imprimir de trás pra frente
 * Autor           : Vinicius Batista Duarte
 * Data de Criação : 14/12/24
 * Última Modificação: 16/12/24
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

struct sNODE *ini = NULL, *fim = NULL;


//========================= PROTÓTIPOS DE FUNÇÕES ==============================

void inserir(int dado);
void inserir_ini(int dado);
void remover(int dado);
struct sNODE *buscar(int dado);
int obter(struct sNODE *node);
int tamanho();
void imprimir();
void apagar();


//========================= FUNÇÃO PRINCIPAL ===================================

int main(){
  return 0;
}

//========================= IMPLEMENTAÇÃO DAS FUNÇÕES ==========================

void inserir_ini(int dado){
    /*
     * Descrição:
     * Inserir no inicio da lista.
     */
  struct sNODE *novo = (struct sNODE*) malloc(sizeof(struct sNODE));
  novo->dado = dado;
  novo->ant = NULL;
  novo->prox = NULL;

  if (!ini)
	  ini = fim = novo; //verifico se a lista está vazia, se sim, defino o novo nó como início e fim
  else{               //a principio a mesma lógica usada para inserir ao final 
	  ini->ant = novo;   // entretanto, com a lista possuindo algum nó, ant vai ser desconectado do terra sendo conectado ao novo nó 
	  novo->prox = ini; //nesse novo nó prox deve apontar para o nó existente 
	  ini = novo; //logo, o novo nó implementado passará a ser o novo início 
  } 
    //mas n para por aí, anteriormente o nó inicial tinha o ant aterrado. dessa forma, devemos fazer o mesmo com o novo nó:
    ini->ant = NULL;
}

void imprimir_reverso(){ 
    /*
     * Descrição:
     * Imprimir a lista ao contrário. 
     */
  struct sNODE *aux = fim; // criamos um ponteiro aux para o último nó 
 
  printf("[ ");
 
  while (aux){        // enquanto aux for diferente de NULL
	  printf("%d ", aux->dado);  // imprimir o dado por onde aux está passando, quase como um print sendo tirado em cada nó 
	  aux = aux->ant; // fazemos aux percorrer para o nó anterior, em vez do prox como na função void imprimir(); 
  }
  printf("]\n");
}


