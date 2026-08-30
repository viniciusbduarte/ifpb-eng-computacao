#include <stdio.h>

int main() {

    float a, b, c, d;
    float exame;
    float mediafinal;

    scanf("%f %f %f %f", &a, &b, &c, &d);

    float media = (a * 2 + b * 3 + c * 4 + d) / 10;

    printf("Media: %.1f\n", media);

    if (media >= 7.0) {
        printf("Aluno aprovado.\n");
    }
    else if (media < 5.0) {
        printf("Aluno reprovado.\n");
    }
    else {
        printf("Aluno em exame.\n");

        scanf("%f", &exame);
        printf("Nota do exame: %.1f\n", exame);

        mediafinal = (media + exame) / 2;

        if (mediafinal >= 5.0) {
            printf("Aluno aprovado.\n");
        }
        else {
            printf("Aluno reprovado.\n");
        }
        printf("Media final: %.1f\n", mediafinal);
    }

    return 0;
}
