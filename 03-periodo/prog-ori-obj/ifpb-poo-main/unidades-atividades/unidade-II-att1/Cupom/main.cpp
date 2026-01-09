#include <iostream>
#include <string>
#include "Cupom.hpp"

int main() {
    Cupom cupom("001", "Mouse gamer", 2, 150.54f);

    std::cout << "ID: " << cupom.getId() << std::endl;
    std::cout << "Descrição: " << cupom.getDescricao() << std::endl;
    std::cout << "Quantidade: " << cupom.getQuantidade() << std::endl;
    std::cout << "Preço Unitário: R$" << cupom.getPreco() << std::endl;
    std::cout << "Valor Total: R$" << cupom.calculaCupom() << std::endl;

    return 0;
}
