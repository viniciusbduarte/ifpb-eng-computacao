#include "Pessoa.hpp"

// Construtor padrão
Pessoa::Pessoa() {}
Pessoa::Pessoa(string n, int i, float a) : nome(n), idade(i), altura(a){}

// Destrutor
Pessoa::~Pessoa() {}

// Métodos set
void Pessoa::setNome(string nome) {
    this->nome = nome;
}

void Pessoa::setIdade(int idade) {
    this->idade = idade;
}

void Pessoa::setAltura(float altura) {
    this->altura = altura;
}

// Métodos get
string Pessoa::getNome() const {
    return nome;
}

int Pessoa::getIdade() const {
    return idade;
}

float Pessoa::getAltura() const {
    return altura;
}


string Pessoa::display() const{
    return "Nome:" + getNome() + "\nIdade: " + to_string(getIdade()) + "\nAltura: " + to_string(getAltura());
}