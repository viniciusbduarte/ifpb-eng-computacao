#include "Varinha.hpp"

Varinha::Varinha(string madeira, float comprimento)
    : madeira(madeira), comprimento(comprimento) {}

string Varinha::getMadeira() const {
    return madeira;
}

float Varinha::getComprimento() const {
    return comprimento;
}
