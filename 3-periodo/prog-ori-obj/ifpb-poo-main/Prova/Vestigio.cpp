#include <iostream>
#include "Vestigio.hpp"

void Vestigio::setNome(string nome) {
    this->nome = nome;
}

void Vestigio::setTipo(string tipo) {
    if (tipo == "Biológico" || tipo == "Físico" || tipo == "Digital") {
        this->tipo = tipo;
    } else {
        cout << "Esse tipo não existe!" << endl;
    }
}

string Vestigio::getNome() const {
    return nome;
}

string Vestigio::getTipo() const {
    return tipo;
}

bool Vestigio::getEvidencia() const {
    return evidencia;
}

string Vestigio::toString() const {
    string evidencia_str = evidencia ? "é evidência" : "não é evidência";
    return "Vestígio: " + nome + ", Tipo: " + tipo + ", " + evidencia_str;
}