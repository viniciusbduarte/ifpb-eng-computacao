#include <iostream> 
#include <string>
#include "Empregado.hpp"


int main(){
    Empregado func1;
    Empregado func2;

    func1.setNome("Vinicius ");
    func1.setSobrenome("Duarte");
    func1.setSalario(1500.0);

    func2.setNome("Fulano ");
    func2.setSobrenome("de tals");
    func2.setSalario(2000.0);

    std::cout << "Nome: " << func1.getNome() << func1.getSobrenome() <<  std::endl;
    std::cout << "Salario: " << func1.getSalario() << std::endl;

    std::cout << "Nome: " << func2.getNome() << func2.getSobrenome() << std::endl;
    std::cout << "Salario: " << func2.getSalario() << std::endl;

    func1.setSalario(func1.getSalario() * 1.10);
    func2.setSalario(func2.getSalario() * 1.10);


    std::cout << "Nome: " << func1.getNome() << func1.getSobrenome() <<  std::endl;
    std::cout << "Salario: " << func1.getSalario() << std::endl;

    std::cout << "Nome: " << func2.getNome() << func2.getSobrenome() << std::endl;
    std::cout << "Salario: " << func2.getSalario() << std::endl;



    return 0;
}