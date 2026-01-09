#include "Mala.hpp"

// Construtores
Mala::Mala() : identificador(""), fabricante(""), peso(0) {}
Mala::Mala(string id, string fab, double p) : identificador(id), fabricante(fab), peso(p) {}

// Setters
void Mala::setIdentificador(string id) { identificador = id; }
void Mala::setFabricante(string fab) { fabricante = fab; }
void Mala::setPeso(double p) { peso = p; }

// Getters
string Mala::getIdentificador() const { return identificador; }
string Mala::getFabricante() const { return fabricante; }
double Mala::getPeso() const { return peso; }

// Sobrecarga do operador << para imprimir
ostream& operator<<(ostream& os, const Mala& m) {
    os << "Mala [ID: " << m.identificador
       << ", Fabricante: " << m.fabricante
       << ", Peso: " << m.peso << "kg]";
    return os;
}
