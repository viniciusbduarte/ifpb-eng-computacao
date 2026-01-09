#include <stdio.h>

int main() {

    float A, B, C;

    scanf("%f %f %f", &A, &B, &C);

    if (B > A) {
        float D = A;
        A = B;
        B = D;
    }
    if (C > A) {
        float D = A;
        A = C;
        C = D;
    }
    if (A >= B + C) {
        printf("NAO FORMA TRIANGULO\n");
    } else {
        if (A * A == (B * B + C * C)) {
            printf("TRIANGULO RETANGULO\n");
        }
        else if (A * A > (B * B + C * C)) {
            printf("TRIANGULO OBTUSANGULO\n");
        }
        else {
            printf("TRIANGULO ACUTANGULO\n");
        }
        if (A == B && B == C) {
            printf("TRIANGULO EQUILATERO\n");
        }
        else if ((A == B && A != C) || (A == C && A != B) || (B == C && B != A)) {
            printf("TRIANGULO ISOSCELES\n");
        }
    }

    return 0;
}
