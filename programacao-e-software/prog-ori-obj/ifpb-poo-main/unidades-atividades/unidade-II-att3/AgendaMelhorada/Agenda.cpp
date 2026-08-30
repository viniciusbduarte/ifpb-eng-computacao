#include "Agenda.hpp"
#include <iostream>
using namespace std;

Agenda::Agenda(int capacidadeInicial) {
    tPessoas = capacidadeInicial;
    numPessoas = 0;
    pessoas = new Pessoa[tPessoas]; // aloca dinamicamente
}

Agenda::~Agenda() {
    delete[] pessoas;
}

string linha = "---------------------------------------------";
string inicioagenda = "-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-";

void Agenda::armazenaPessoa(const string &nome, int idade, float altura) {
    if (numPessoas < tPessoas) {
        pessoas[numPessoas++] = Pessoa(nome, idade, altura);
    } else {
        cout << "Agenda cheia!" << endl;
    }
}

void Agenda::armazenaPessoa(const Pessoa &p) {
    if (numPessoas < tPessoas) {
        pessoas[numPessoas++] = p;
    } else {
        cout << "Agenda cheia!" << endl;
    }
}

void Agenda::removePessoa(const string &nome) {
    for (int i = 0; i < numPessoas; ++i) {
        if (pessoas[i].getNome() == nome) {
            pessoas[i] = pessoas[numPessoas - 1];
            --numPessoas;
            cout << "Pessoa removida.\n";
            return;
        }
    }
    cout << "Pessoa não encontrada.\n";
}

int Agenda::buscaPessoa(const string &nome) const {
    for (int i = 0; i < numPessoas; ++i) {
        if (pessoas[i].getNome() == nome) {
            return i;
        }
    }
    return -1; // Não encontrou
}

void Agenda::imprimePovo() const {
    cout << inicioagenda << endl;
    cout << "Agenda:\n";
    for (int i = 0; i < numPessoas; ++i) {
        cout << linha << endl;
        cout << pessoas[i].display() << endl;
    }
    cout << inicioagenda << endl;
}

void Agenda::imprimePessoa(int i) const {
    if (i >= 0 && i < numPessoas) {
        cout << pessoas[i].display() << endl;
        cout << linha << endl;
    } else {
        cout << "Índice inválido!\n";
    }
}
