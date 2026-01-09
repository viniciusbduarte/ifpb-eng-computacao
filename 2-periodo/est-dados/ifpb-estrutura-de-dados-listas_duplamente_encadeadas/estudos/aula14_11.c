#include <stdio.h>

int fat(int n)
{

    return(n*fat(n-1));

}


int main(){



printf("%d", fat(5));





return 0;
}
