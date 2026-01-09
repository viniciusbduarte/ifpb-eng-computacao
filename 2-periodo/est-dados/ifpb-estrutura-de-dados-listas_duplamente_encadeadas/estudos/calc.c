#include <stdio.h>
#include <stdlib.h>

int main() {
    int R, L, J;
    char calc[25];
    int resultado = 0;

    for (int i = 0; i < 3; i++) {
        fgets(calc, sizeof(calc), stdin);
        sscanf(calc, "%d+%d=%d\n", &R, &L, &J);  // Usa %d para ler números inteiros
        sscanf(calc, "%c+%c=%c\n", &r, &l, &j);  // Usa %d para ler números inteiros


        if (r == 'R') {  // Se o lado esquerdo é a incógnita
            resultado = J - L;
            printf("%d\n", resultado);
        } else if (l == 'L') {  // Se o lado direito da soma é a incógnita
            resultado = J - R;
            printf("%d\n", resultado);
        } else if (j == 'J') {  // Se o resultado é a incógnita
            resultado = R + L;
            printf("%d\n", resultado);
        }

        resultado = 0;
    }

    return 0;
}
