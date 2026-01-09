#pragma once
#include <iostream>
#include <string>
using namespace std;


class CapaBruxo {
private:
    float tamanho;
    string casa;
    string cor;
public: 
    CapaBruxo(float t, string c) : tamanho(t) {
        setCasa(c);
    };

    //sets
    void setTamanho(float tamanho);
    void setCasa(string casa);

    //gets 
    inline float getTamanho() const{
        return tamanho;
    }
    inline string getCor() const{
        return cor;
    }
    inline string getCasa() const{
        return casa;
    }

    //exibição 
    string display() const;

};