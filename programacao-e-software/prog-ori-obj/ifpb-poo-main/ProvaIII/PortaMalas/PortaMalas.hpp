#ifndef PORTAMALAS_HPP
#define PORTAMALAS_HPP

#include "Mala.hpp"

class PortaMalas {
private:
    Mala malas[15];
    int quantidade;

public:
    PortaMalas();

    // Sobrecarga do operador << para adicionar uma Mala
    PortaMalas& operator<<(const Mala& m);

    // Sobrecarga do operador >> para remover uma Mala pelo identificador
    PortaMalas& operator>>(const string& id);

    // Sobrecarga do operador << para imprimir todas as Malas
    friend ostream& operator<<(ostream& os, const PortaMalas& pm);
};

#endif
