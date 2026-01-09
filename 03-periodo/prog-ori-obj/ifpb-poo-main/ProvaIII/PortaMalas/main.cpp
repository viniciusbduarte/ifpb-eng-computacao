#include <iostream>
#include "PortaMalas.hpp"
using namespace std;

int main() {
    PortaMalas carro;

    Mala m1("001", "Marca Mala 1", 8.5);
    Mala m2("002", "Marca Mala 2", 7.2);
    Mala m3("003", "Marca Mala 3", 6.0);
    Mala m4("004", "Marca Mala 4", 5.5);
    Mala m5("005", "Marca Mala 5", 9.0);

    carro << m1 << m2 << m3 << m4 << m5;

    carro >> "003"; 

    cout << carro;

    return 0;
}
