#include <iostream>
#include "Carro.hpp"

int main() {
    Carro possante{"Renault", "Duster", 2025};
	std::cout << possante.toString() << std::endl;
    /*std::cout << "Marca: " << possante.getMarca() << "\n";
    std::cout << "Modelo: " << possante.getModelo() << "\n";
	std::cout << "Ano: " << possante.getAno() << "\n";*/

    return 0;
}


