#include <stdio.h>

int main() {
    int numero = 10;
    int *ponteiro;

    ponteiro = &numero;

    printf("Ponteiro antes %p\n", ponteiro);
    printf("Valor de 'numero' antes de alterar pelo ponteiro: %d\n", numero);
    *ponteiro = (int*)&ponteiro;
    printf("Valor de 'numero' depois de alterar pelo ponteiro: %d\n", numero);
    printf("Ponteiro depois %p\n", ponteiro);





    return 0;
}

