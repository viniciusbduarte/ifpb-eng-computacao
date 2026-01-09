#include <iostream>
#include "Suspeito.hpp"

void Suspeito::setNome(string nome) {
    this->nome = nome;
}

void Suspeito::setIndiciadoOuNao(bool indiciado_ou_nao) {
    this->indiciado_ou_nao = indiciado_ou_nao;
}

string Suspeito::getNome() const {
    return nome;
}

bool Suspeito::getIndiciadoOuNao() const {
    return indiciado_ou_nao;
}

string Suspeito::toString() const {
    string situacao = indiciado_ou_nao ? "Indiciado" : "Não Indiciado";
    return "Nome do Suspeito: " + nome + ", Situação: " + situacao;
}
