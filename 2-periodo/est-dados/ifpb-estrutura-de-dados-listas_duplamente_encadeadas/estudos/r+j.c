#include <stdio.h>
#include <string.h>

int main() {
    char calc[25];
    char R, L, J;
    int result = 0;

    for (int i = 0; i < 3; i++) {

        fgets(calc, sizeof(calc), stdin);

        if (calc[strlen(calc) - 1] == '\n') {
            calc[strlen(calc) - 1] = '\0';
        }

        sscanf(calc, "%c+%c=%c", &R, &L, &J);

        int valR = R - '0';
        int valL = L - '0';
        int valJ = J - '0';

        if (R == 'R') {
            result = valJ - valL;
        } else if (L == 'L') {
            result = valJ - valR;
        } else if (J == 'J') {
            result = valR + valL;
        }

        printf("%d\n", result);
    }

    return 0;
}
