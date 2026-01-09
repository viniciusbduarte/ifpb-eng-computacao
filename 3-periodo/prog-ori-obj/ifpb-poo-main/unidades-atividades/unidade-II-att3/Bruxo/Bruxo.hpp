#pragma once
#include <string>
#include "CapaBruxo.hpp"
#include "Varinha.hpp"
using namespace std;

class Bruxo {
private:
    string nome;
    string casa;
    string feitico_predileto;

    Varinha *varinha;       // agregação: recebidas externamente
    CapaBruxo *capabruxo;   // agregação: recebidas externamente

public:
    // Construtor com acessórios (agregação)
    Bruxo(string nm, string cs, string fp, Varinha *v, CapaBruxo *c);

    // Construtor sem acessórios
    Bruxo(string nm, string cs, string fp);

    string getNome() const;
    void setNome(string nm);

    string getCasa() const;
    void setCasa(string cs);

    string getFeitico() const;
    void setFeitico(string fp);

    string display() const;
    string lancarFeitico() const;
};
