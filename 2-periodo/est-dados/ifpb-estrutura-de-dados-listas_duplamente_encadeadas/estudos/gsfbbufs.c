#include <stdio.h>
#include <stdlib.h>

#define MAX 3

void inserir_ini(int elemento);
void imprimir(int l[MAX]);
int l[MAX], pos = 0;

int main() {
    inserir_ini(100);
    inserir_ini(200);
    inserir_ini(100);
    imprimir(l);

    return 0;
}

// Funções


void inserir_ini(int elemento) {
    if (pos >= MAX) {
        printf("Lista cheia!\n");
        exit(1);
    }
    for (int i = pos; i > 0; i--) l[i] = l[i - 1];
    for (int i = pos; i > 0; i--) {
        if (l[i] == elemento) {
            printf("Esse elemento jah existe!\n");
            exit(1);
    }}
        l[0] = elemento;
        pos++;
}





void imprimir(int l[MAX]) {
    for (int i = 0; i < pos; i++) {
        printf("Posicao %d tem o elemento %d\n", i, l[i]);
}}
