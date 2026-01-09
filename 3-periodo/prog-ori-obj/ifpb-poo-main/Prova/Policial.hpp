#pragma once
#include <string>
using namespace std;

class Policial {
private:
    string nome;
    string cargo;

public:
    Policial() = default;
    Policial(string nome, string cargo) {
        this->nome = nome;
        setCargo(cargo);
    }

    void setNome(string nome);
    void setCargo(string cargo);

    string getNome() const;
    string getCargo() const;

    string toString() const;
};