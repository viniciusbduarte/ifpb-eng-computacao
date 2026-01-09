#pragma once 
#include <iostream>
#include <string>
using namespace std;

class Pessoa {
private:
    string nome;
    string CPF;
    bool CPFvalido = false;
public:
    Pessoa(string n, string c);

    //gets
    string getNome();
    string getCPF();
    
    //sets
    void setCPF(string c);
    void setNome(string n);

    // Método para exibir o nome e CPF
    void apresentar();
};
