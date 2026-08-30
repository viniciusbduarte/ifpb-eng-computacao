#ifndef MALA_HPP
#define MALA_HPP

#include <iostream>
#include <string>
using namespace std;

class Mala {
private:
    string identificador;
    string fabricante;
    double peso;

public:
    Mala();
    Mala(string id, string fab, double p);

    // Setters
    void setIdentificador(string id);
    void setFabricante(string fab);
    void setPeso(double p);

    // Getters
    string getIdentificador() const;
    string getFabricante() const;
    double getPeso() const;

    friend ostream& operator<<(ostream& os, const Mala& m);
};

#endif
