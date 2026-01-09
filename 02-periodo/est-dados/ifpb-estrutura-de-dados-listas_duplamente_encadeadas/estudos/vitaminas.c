#include <stdio.h>

int main() {
    char str[] = "3 sucos de acerola";
    char result[50]; // Buffer para armazenar o resultado

    // Usa sscanf para ler a parte desejada diretamente
    sscanf(str, "%*d %[^\n]", result);

    // Exibe o resultado
    printf("Resultado: %s\n", result);

    return 0;
}
