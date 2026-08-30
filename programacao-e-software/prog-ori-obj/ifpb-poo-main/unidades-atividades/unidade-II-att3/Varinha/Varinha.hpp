#pragma once
#include <iostream>
#include <string>
using namespace std;

class Varinha {
private:
    string tipo_madeira;
    string nucleo;
    float comprimento;

public:
    Varinha();
    Varinha(string t, string n, float c);

    void setTipoMadeira(string tipo_madeira);
    void setNucleo(string nucleo);
    void setComprimento(float comprimento);

    string getTipoMadeira() const;
    string getNucleo() const;
    float getComprimento() const;

    void display();
};
