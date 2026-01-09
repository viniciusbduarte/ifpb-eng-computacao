#include <stdio.h>
#include <string.h>

int main() {
    int quantidade_alimentos;
    char alimento[100];
    int calorias;

    while (1) {
        scanf("%d", &quantidade_alimentos);

        if (quantidade_alimentos == 0) {
            break;
        }

        calorias = 0;

        for (int i = 0; i < quantidade_alimentos; i++) {
            int quantidade;
            char tipo_alimento[50];

            scanf("%d %[^\n]", &quantidade, tipo_alimento);

            if (strcmp(tipo_alimento, "suco de laranja") == 0) {
                calorias += quantidade * 120;
            } else if (strcmp(tipo_alimento, "morango fresco") == 0) {
                calorias += quantidade * 85;
            } else if (strcmp(tipo_alimento, "mamao") == 0) {
                calorias += quantidade * 85;
            } else if (strcmp(tipo_alimento, "goiaba vermelha") == 0) {
                calorias += quantidade * 70;
            } else if (strcmp(tipo_alimento, "manga") == 0) {
                calorias += quantidade * 56;
            } else if (strcmp(tipo_alimento, "laranja") == 0) {
                calorias += quantidade * 50;
            } else if (strcmp(tipo_alimento, "brocolis") == 0) {
                calorias += quantidade * 34;
            }
        }

        if (calorias >= 110 && calorias <= 130) {
            printf("%d mg\n", calorias);
        } else if (calorias > 130) {
            printf("Menos %d mg\n", calorias - 130);
        } else if (calorias < 110) {
            printf("Mais %d mg\n", 110 - calorias);
        }
    }

    return 0;
}
