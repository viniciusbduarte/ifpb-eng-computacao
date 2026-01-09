#include <iostream>


//função para desenhar padrão 
void desenhar_padrao(int espaco_padrao[], int asterisco_padrao[], int tamanho){
    for (int i = 0; i < tamanho; i++) {
        for (int k = 0; k<espaco_padrao[i]; k++){
            std::cout << " ";
        }
        for (int k = 0; k<asterisco_padrao[i]; k++){
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    
    int asterisco_padrao1[] = {1, 2, 3, 4, 5};
    int espaco_padrao1[] = {0, 0, 0, 0, 0};

    int asterisco_padrao2[] = {5, 4, 3, 2, 1 };
    int espaco_padrao2[] = {0, 1, 2, 3, 4};
       
    int asterisco_padrao3[] = {1, 3, 5, 3, 1};
    int espaco_padrao3[] = {2, 1, 0, 1, 2};
    
    int asterisco_padrao4[] = {1, 3, 5, 7};
    int espaco_padrao4[] = {3, 2, 1, 0};
    

    desenhar_padrao(espaco_padrao1, asterisco_padrao1, 5);
    desenhar_padrao(espaco_padrao2, asterisco_padrao2, 5);
    desenhar_padrao(espaco_padrao3, asterisco_padrao3, 5);
    desenhar_padrao(espaco_padrao4, asterisco_padrao4, 4);

    return 0;
}




