#include <stdio.h>
#include <string.h>

int main() {
    char primeiro_ah[1000], segundo_ah[1000];

    fgets(primeiro_ah, sizeof(primeiro_ah), stdin);
    fgets(segundo_ah, sizeof(segundo_ah), stdin);
    primeiro_ah[strcspn(primeiro_ah, "\n")] = 0;
    segundo_ah[strcspn(segundo_ah, "\n")] = 0;

    if (strlen(primeiro_ah) > strlen(segundo_ah)) {
        printf("go\n");
    } else {
        printf("no\n");
    }

    return 0;
}
