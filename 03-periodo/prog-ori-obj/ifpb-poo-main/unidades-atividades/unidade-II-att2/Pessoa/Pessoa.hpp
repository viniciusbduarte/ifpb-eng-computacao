#pragma once 
#include <iostream>
#include <string>
using namespace std;

class Pessoa {
private:
    string nome;
    string CPF;
    bool CPFvalido;

public:
    // Construtor com argumentos default
    Pessoa(string n, string c = "00000000000", bool v = false);

    //gets
    string getNome();
    bool getCPFvalido();
    string getCPF();
    
    //sets
    void setCPF(string c);
    void setNome(string n);
    void setCPFvalido(bool v);

    // Método para exibir o nome e CPF
    void apresentar();
};
