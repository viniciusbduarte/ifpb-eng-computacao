#pragma once
#include <string>
#include <iostream>
#include "Mala.hpp"
#include "Varinha.hpp"
using namespace std;

class Bruxo {
private:
    string nome;
    string casa;
    string feitiço;
    Mala* mala = nullptr;
    Varinha* varinha = nullptr;

public:
    Bruxo(string nome = "", string casa = "");
    void setNome(string nome);
    void setCasa(string casa);
    string getNome() const;
    string getCasa() const;
    
    void pegarMala(Mala* m);
    void soltarMala();
    void empunharVarinha(Varinha* v);
    void soltarVarinha();
    
    void setFeitico(string f);
    void lancarFeitico() const;

    void display() const;
};
