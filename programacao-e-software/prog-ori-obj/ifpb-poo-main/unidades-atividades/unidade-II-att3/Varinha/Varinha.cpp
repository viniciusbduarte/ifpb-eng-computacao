#include "Varinha.hpp"

Varinha::Varinha() {}

Varinha::Varinha(string t, string n, float c) : tipo_madeira(t), nucleo(n), comprimento(c) {}

void Varinha::setTipoMadeira(string tipo_madeira) {
    this->tipo_madeira = tipo_madeira;
}

void Varinha::setNucleo(string nucleo) {
    this->nucleo = nucleo;
}

void Varinha::setComprimento(float comprimento) {
    this->comprimento = comprimento;
}

string Varinha::getTipoMadeira() const {
    return tipo_madeira;
}

string Varinha::getNucleo() const {
    return nucleo;
}

float Varinha::getComprimento() const {
    return comprimento;
}

void Varinha::display() {
    cout << "Atributos da Varinha:" << endl
         << "Tipo de madeira: " << getTipoMadeira() << endl
         << "Núcleo: " << getNucleo() << endl
         << "Comprimento: " << getComprimento() << endl;
}
