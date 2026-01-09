#include <stdio.h>

int main() {

    int voltas, placas;
    scanf("%d %d", &voltas, &placas);

    int total = voltas * placas;

    printf("%d %d %d %d %d %d %d %d %d\n",
           (int)((total * 0.1)+0.9), (int)((total * 0.2)+0.9), (int)((total * 0.3)+0.9), (int)((total * 0.4)+0.9),
           (int)((total * 0.5)+0.9), (int)((total * 0.6)+0.9), (int)((total * 0.7)+0.9), (int)((total * 0.8)+0.9), (int)((total * 0.9)+0.9));

    return 0;
}
