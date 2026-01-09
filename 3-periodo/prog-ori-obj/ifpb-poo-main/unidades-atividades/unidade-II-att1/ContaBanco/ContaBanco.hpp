#pragma once 
#include <iostream> 
#include <string>

class ContaBanco {
private:
    std::string nome;
    std::string numero_conta;
    double saldo;

public:
    ContaBanco(std::string nm, std::string num_conta, double sd = 0.0);

    void creditar(double deposito);
    void debitar(double retirar);
    double getSaldo() const;
    std::string getNome() const;
};
