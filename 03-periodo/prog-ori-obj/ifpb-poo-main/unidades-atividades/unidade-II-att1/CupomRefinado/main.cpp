#include <iostream>
#include "Cupom.hpp"

int main() {
    Cupom cupom;

    cupom.addItem(Item("001", "Mouse gamer", 2, 150.0f));
    cupom.addItem(Item("002", "Teclado mecânico", 1, 250.0f));
    cupom.addItem(Item("003", "Headset", 3, 100.0f));

    std::cout << "\nItens do cupom:\n";
    cupom.imprimirNota();

    std::cout << "\nTotal: R$" << cupom.calcularCupom() << std::endl;

    return 0;
}
