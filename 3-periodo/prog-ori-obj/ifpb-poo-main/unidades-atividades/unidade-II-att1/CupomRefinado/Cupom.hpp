#pragma once
#include <string>
#include <vector>

struct Item {
    std::string id;
    std::string descricao;
    int quantidade;
    float preco;

    Item(std::string i, std::string d, int q, float p)
        : id(i), descricao(d), quantidade(q > 0 ? q : 0), preco(p > 0 ? p : 0.0f) {}
};

class Cupom {
private:
    std::vector<Item> itens; // vector itens do tipo item

public:
    void addItem(const Item& item);
    float calcularCupom() const;
    void imprimirNota() const;
};
