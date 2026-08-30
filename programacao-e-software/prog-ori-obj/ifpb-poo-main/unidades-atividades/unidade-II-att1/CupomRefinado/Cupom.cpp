#include "Cupom.hpp"
#include <iostream>

void Cupom::addItem(const Item& item) {
    itens.push_back(item);
}

float Cupom::calcularCupom() const {
    float total = 0.0f;
    for (const auto& item : itens) {
        total += item.quantidade * item.preco;
    }
    return total;
}

void Cupom::imprimirNota() const {
    for (const auto& item : itens) {
        std::cout << "ID: " << item.id
                  << ", Descrição: " << item.descricao
                  << ", Quantidade: " << item.quantidade
                  << ", Preço: R$" << item.preco
                  << ", Subtotal: R$" << item.quantidade * item.preco << std::endl;
    }
}
