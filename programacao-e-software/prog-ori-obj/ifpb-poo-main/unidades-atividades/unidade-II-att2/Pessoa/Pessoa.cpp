#include "Pessoa.hpp"
#include <string>
#include <iostream>

Pessoa::Pessoa(string n, string c, bool v) : nome(n), CPF(c), CPFvalido(v) { }

string Pessoa::getNome() {
    return nome;
}

void Pessoa::setNome(string n) {
    nome = n;
}

string Pessoa::getCPF() {
    return CPF;
}

void Pessoa::setCPF(string c) {
    CPF = c;
}

bool Pessoa::getCPFvalido() {
    return CPFvalido;
}

void Pessoa::setCPFvalido(bool v) {
    CPFvalido = v;
}

void Pessoa::apresentar() {
    cout << "Nome: " << nome << endl;
    cout << "CPF: " << CPF << " (" << (CPFvalido ? "Válido" : "Inválido") << ")" << endl;
}
