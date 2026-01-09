#include "PortaMalas.hpp"
#include <iostream>
using namespace std;

PortaMalas::PortaMalas() : quantidade(0) {}

PortaMalas& PortaMalas::operator<<(const Mala& m) {
    if (quantidade < 15) {
        malas[quantidade++] = m;
    } else {
        cout << "Porta-malas cheio! Não é possível adicionar a mala.\n";
    }
    return *this;
}

PortaMalas& PortaMalas::operator>>(const string& id) {
    for (int i = 0; i < quantidade; i++) {
        if (malas[i].getIdentificador() == id) {
            for (int j = i; j < quantidade - 1; j++) {
                malas[j] = malas[j + 1];
            }
            quantidade--;
            break;
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const PortaMalas& pm) {
    if (pm.quantidade == 0) {
        os << "Porta-malas vazio.\n";
    } else {
        os << "Malas no porta-malas:\n";
        for (int i = 0; i < pm.quantidade; i++) {
            os << "  " << pm.malas[i] << endl;
        }
    }
    return os;
}
