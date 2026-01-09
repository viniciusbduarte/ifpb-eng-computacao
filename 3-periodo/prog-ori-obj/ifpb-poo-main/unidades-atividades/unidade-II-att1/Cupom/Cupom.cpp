#include <iostream>
#include <string>
#include "Cupom.hpp"

// Construtor
Cupom::Cupom(std::string id, std::string desc, int qtd, float prc)
    : id(id), descricao(desc), quantidade(qtd > 0 ? qtd : 0), preco(prc > 0 ? prc : 0.0f) {}

// sets
void Cupom::setId(std::string id) {
    this->id = id;
}
void Cupom::setDescricao(std::string desc) {
    descricao = desc;
}
void Cupom::setQuantidade(int qtd) {
    quantidade = (qtd > 0) ? qtd : 0;
}
void Cupom::setPreco(float prc) {
    preco = (prc > 0) ? prc : 0.0f;
}

// gets
std::string Cupom::getId() const {
    return id;
}
std::string Cupom::getDescricao() const {
    return descricao;
}
int Cupom::getQuantidade() const {
    return quantidade;
}
float Cupom::getPreco() const {
    return preco;
}

// Calcula valor total
float Cupom::calculaCupom() const {
    return quantidade * preco;
}