#include <iostream>
using namespace std;

#include "Policial.hpp"

void Policial::setNome(string nome) {
    this->nome = nome;
}

void Policial::setCargo(string cargo) {
    if (cargo == "Delegado" || cargo == "Perito" || cargo == "Investigador" || cargo == "Escrivão") {
        this->cargo = cargo;
    } else {
        cout << "Esse cargo não existe!" << endl;
    }
}

string Policial::getNome() const {
    return nome;
}

string Policial::getCargo() const {
    return cargo;
}

string Policial::toString() const {
    return "Nome do Policial: " + nome + ", Cargo: " + cargo;
}
