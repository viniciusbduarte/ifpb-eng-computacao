#pragma once
#include <string>

class Empregado{
private:
    std::string nome;
    std::string sobrenome;
    float salario;
public:
    Empregado(std::string nm = " ", std::string sbn = " ", float sal = 0.0);
    std::string getNome() const;
    void setNome(std::string nm);
    std::string getSobrenome() const;
    void setSobrenome(std::string sbn);
    float getSalario() const;
    void setSalario(float sal);
};