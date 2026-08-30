#include <iostream>

double media(double nota1, double nota2, double nota3);

int main(){
    // nome do aluno
    std::string nome_aluno;
    std::cout << "Digite o nome do aluno: ";
    std::getline(std::cin, nome_aluno);

    // notas
    double nota1{0}, nota2{0}, nota3{0};
    std::cout << "Digite as 3 notas do aluno " << nome_aluno << ": ";
    std::cin >> nota1 >> nota2 >> nota3;

    // média
    std::cout << "A aluno " << nome_aluno << " obteve média "
              << media(nota1, nota2, nota3) << std::endl;

    return 0;
}

// função da média
double media(double nota1, double nota2, double nota3){
    int peso_nota1{3}, peso_nota2{4}, peso_nota3{5};
    return ((nota1 * peso_nota1) + (nota2 * peso_nota2) + (nota3 * peso_nota3)) 
            / (peso_nota1 + peso_nota2 + peso_nota3);
}
