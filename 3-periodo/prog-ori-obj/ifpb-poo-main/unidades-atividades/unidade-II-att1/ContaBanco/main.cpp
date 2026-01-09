#include <iostream>
#include <string>
#include "ContaBanco.hpp"

int main(){
    ContaBanco usuario1{"Vinicius", "0000000-0"};
    ContaBanco usuario2{"Fulano de tals", "0000000-0"};

    usuario1.creditar(200.35);
    usuario2.creditar(4300.50);


    std::cout << "Saldo de " << usuario1.getNome() << " é de R$ " << usuario1.getSaldo() << std::endl;
    std::cout << "Saldo de " << usuario2.getNome() << " é de R$ " << usuario2.getSaldo() << std::endl;

    usuario1.debitar(140);
    usuario2.debitar(1500);


    std::cout << "Saldo de " << usuario1.getNome() << " é de R$ " << usuario1.getSaldo() << std::endl;
    std::cout << "Saldo de " << usuario2.getNome() << " é de R$ " << usuario2.getSaldo() << std::endl;


    return 0;
}