#include "Pessoa.hpp"
#include <string>
#include <iostream>

Pessoa::Pessoa(string n, string c){
    setNome(n);
    setCPF(c);
 }

string Pessoa::getNome()  {
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

    if (CPF.size() != 11) {
        CPFvalido = false;
        return;
    }

    // verifica se todos os dígitos são iguais
    bool todosIguais = true;
    for (int i = 1; i < 11; i++) {
        if (CPF[i] != CPF[0]) {
            todosIguais = false;
            break;
        }
    }
    if (todosIguais) {
        CPFvalido = false;
        return;
    }

    // primeira validação
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (CPF[i] - '0') * (10 - i);
    }
    int resto1 = (soma * 10) % 11;
    if (resto1 == 10) resto1 = 0;

    // segunda validação
    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (CPF[i] - '0') * (11 - i);
    }
    int resto2 = (soma * 10) % 11;
    if (resto2 == 10) resto2 = 0;

    // verificação final
    CPFvalido = (resto1 == (CPF[9] - '0') && resto2 == (CPF[10] - '0'));
}


void Pessoa::apresentar() {
    cout << "Nome: " << nome << endl;
    cout << "CPF: " << CPF << " (" << (CPFvalido ? "Válido" : "Inválido") << ")" << endl;
}
