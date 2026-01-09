#include <stdio.h>
#include <string.h>

int main() {
    char jon_aaah[1000];
    char medico_aah[1000];

    fgets(jon_aaah, sizeof(jon_aaah), stdin);
    fgets(medico_aah, sizeof(medico_aah), stdin);

    if (strlen(jon_aaah) >= strlen(medico_aah)) {
        printf("go\n");
    } else {
        printf("no\n");
    }

    return 0;
}
