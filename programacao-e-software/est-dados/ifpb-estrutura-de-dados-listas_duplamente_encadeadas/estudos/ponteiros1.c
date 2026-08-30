#include <stdio.h>

// Função para trocar os valores
void troca(int *ptra, int *ptrb) {
    int aux = *ptra;  // Salva o valor de 'a' no auxiliar
    *ptra = *ptrb;       // Atribui o valor de 'b' para 'a'
    *ptrb = aux;      // Atribui o valor salvo para 'b'
}

int main() {
    int a = 42;
    int b = 10;

    // Chama a função passando os endereços de 'a' e 'b'
    troca(&a, &b);

    printf("a igual a %d e b igual a %d", a, b);

    return 0;
}
