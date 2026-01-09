#pragma once
#include <iostream>
#include <string>

class Cupom {
private:
    std::string id;
    std::string descricao;
    int quantidade;
    float preco;

public:
    Cupom(std::string id, std::string desc, int qtd, float prc);

    // sets
    void setId(std::string id);
    void setDescricao(std::string desc);
    void setQuantidade(int qtd);
    void setPreco(float prc);

    // gets
    std::string getId() const;
    std::string getDescricao() const;
    int getQuantidade() const;
    float getPreco() const;

    // Método para calcular o valor total
    float calculaCupom() const;
};
