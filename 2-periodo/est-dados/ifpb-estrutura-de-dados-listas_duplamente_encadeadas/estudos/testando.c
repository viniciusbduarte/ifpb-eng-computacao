#include <stdio.h>

int main(){

int opt; // variavel para armazena a opcao a ser escolhida no meni
char clientes[3][20] = {
    "Julio",
    "Robson",
    "Zezo"
};
int tamanho = 3; // tamanho da array de clientes
char novonome[10];


do{
    do{
        printf("*****Menu*****\n");
        printf("[1] Clientes\n");
        printf("[2] Cadastrar\n\n");
        printf("Digite sua opcao: ");
        scanf("%d", &opt);

    }while((opt<1)||(opt>2));

    switch(opt){

        case 1:
            printf("\n*****Clientes*****\n");
            for(int i=0; i<tamanho; i++)printf("%s\n", clientes[i]);printf("\n");
            break;

        case 2:
            printf("*****Modulo de Cadastramento*****\n\n");
            printf("Digite o nome do novo cliente: ");
            scanf("%10s", novonome);
            strcpy(clientes[tamanho], novonome);
            tamanho++;
            break;
                }

    }while(opt != 4);



return 0;

}
