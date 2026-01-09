#pragma once
#include <string>
using namespace std;

class Suspeito {
private:
    string nome;
    bool indiciado_ou_nao;

public:
    Suspeito() = default;
    Suspeito(string nome, bool indiciado) {
        this->nome = nome;
        this->indiciado_ou_nao = indiciado;
    }

    void setNome(string nome);
    void setIndiciadoOuNao(bool indiciado_ou_nao);

    string getNome() const;
    bool getIndiciadoOuNao() const;

    string toString() const;
};
