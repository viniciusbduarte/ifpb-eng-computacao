#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int l[MAX], pos = 0;

void inserir(int elemento);
void inserir_ord(int elemento);
void inserir_ini(int elemnto);
int buscar(int elemento);
void remover(int elemento);

int obter(int indice);
int tamanho();
void imprimir();
void apagar();

int main(void) {
    inserir_ord(200);
    inserir_ord(400);
    inserir_ord(500);
    inserir_ord(100);
    inserir_ord(700);
    inserir_ord(800);

    imprimir(l);
  return 0;
}

//inserir elemento ao final da lista  ( se já houver um item igual, n adiciona )
void inserir(int elemento){
    if (pos < MAX){
        /*for(int i = 0; i < pos; i++) {
            if (l[i] == elemento){
                printf("Não foi possível inserir %d. Elemento já encontrado.\n",elemento);
                exit(0);
            }
        }*/
	    l[pos++] = elemento;
    }
    else {
	    printf("Não foi possível inserir %d. Lista cheia.\n",elemento);
        exit(0);
     }
}
//inserir elemento no inicio da lista ( se já houver um item igual, n adiciona )
void inserir_ini(int elemento){
    if (pos < MAX){
        pos++;
        for(int i=pos; i > 0; i--) {
            if(l[i] == elemento){
                printf("Não foi possível inserir %d. Elemento já encontrado.\n",elemento);
                exit(0);
            }
        for(int i=pos; i > 0; i--) {  
                l[i] = l[i-1];
        }
        }
        l[0] = elemento; 
    }
    else {
        printf("Não foi possível inserir %d. Lista cheia.\n",elemento); // caso a lista esteja cheia (pos >= MAX), exibe uma mensagem de erro
        exit(0);
        4
    }

}
//função modificada para remover todos os itens que sejam igual o elemento escolhido
void remover(int elemento){
    for(int i = pos; i >= 0; i-- ){ // percorre a lista até o item inicial
        if( l[i] == elemento){ //verifica todos os itens da lista e confere quais são iguais ao elemento escolhido
            for( int p = i; p < pos; p++){ // a partir da posição encontrada(i), 
              l[p] = l[p+1]; // substitui cada item pelo próximo( "cobrindo o item escolhido" ), fazendo isso para todos os elementos repetidos
            }
            pos--; // diminui a lista ignorando o ultimo elemento repetido 
        }
    }
}
  
int buscar(int elemento){
  for (int i = 0 ; i < pos ; i++){
	if (l[i] == elemento)
  	return i;
  }
  return -1;
}

void inserir_ord(int elemento){
  int i, p;
  if (pos < MAX) {
	for (i = 0 ; i < pos ; i++)
  	    if (l[i] >= elemento)
    	        break;
    
	for (p = pos ; p > i ; p--)
  	    l[p] = l[p-1];
    
	l[i] = elemento;

	pos ++;
  }
  else {
	printf("Não foi possível inserir %d. Lista cheia.\n",elemento);
  } 
}









int obter(int indice){
  if (indice < 0 || indice >= pos) {
	printf("Indice %d fora dos limites da Lista.\n", indice);
	exit(1);
  }
  return l[indice];
}

int tamanho(){
  return pos;
}

void imprimir(){
  for (int i = 0 ; i < pos ; i++)
	printf("%d ",l[i]);
  printf("\n");
}

void apagar(){
  pos = 0;
}