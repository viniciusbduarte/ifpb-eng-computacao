#include <stdio.h>

int main() {
    int T;

    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        int PA, PB;
        double G1, G2;
        int anos = 0;

        scanf("%d %d %lf %lf", &PA, &PB, &G1, &G2);

        G1 = G1 / 100.0;
        G2 = G2 / 100.0;

        while (PA <= PB) {
            PA += (int)(PA * G1);
            PB += (int)(PB * G2);
            anos++;

            if (anos > 100) {
                printf("Mais de 1 seculo.\n");
                break;
            }
        }

        if (anos <= 100) {
            printf("%d anos.\n", anos);
        }
    }

    return 0;
}
