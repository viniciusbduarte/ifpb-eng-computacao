#include <iostream>
#include <string>
#include "ContaBanco.hpp"

double saldoValido(double saldo);  

ContaBanco::ContaBanco(std::string nm, std::string num_conta, double sd)
    : nome(nm), numero_conta(num_conta), saldo(saldoValido(sd)) {}

void ContaBanco::creditar(double deposito){
    if(deposito < 0) std::cout << "Valor de depósito incorreto!" << std::endl;
    else saldo += deposito;
}

void ContaBanco::debitar(double retirar){
    if(retirar > saldo) std::cout << "Saldo Insuficiente!" << std::endl;
    else saldo -= retirar;
}

double ContaBanco::getSaldo() const{
    return saldo;
}

std::string ContaBanco::getNome() const{
    return nome;
}

double saldoValido(double saldo){
    return (saldo < 0) ? 0.0 : saldo;
}
