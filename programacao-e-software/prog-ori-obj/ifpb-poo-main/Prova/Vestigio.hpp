#pragma once
#include <string>
using namespace std;

class Vestigio {
private:
    string nome;
    string tipo;
    bool evidencia;

public:
    Vestigio() = default;
    Vestigio(string nome, string tipo, bool evidencia) {
        this->nome = nome;
        setTipo(tipo);
        this->evidencia = evidencia;
    }

    void setNome(string nome);
    void setTipo(string tipo);

    string getNome() const;
    string getTipo() const;
    bool getEvidencia() const;

    string toString() const;
};