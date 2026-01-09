#include <iostream> 
#include <string>

#include "Empregado.hpp"

Empregado::Empregado(std::string nm , std::string sbn , float sal): nome(nm), sobrenome(sbn), salario(sal){}



//gets
std::string Empregado::getNome() const{
    return nome;
}
std::string Empregado::getSobrenome() const{
    return sobrenome;
}
float Empregado::getSalario() const{
    return salario;
}

//sets 
void Empregado::setNome(std::string nm){
    nome = nm;
}
void Empregado::setSobrenome(std::string sbn){
    sobrenome = sbn;
}
void Empregado::setSalario(float sal){
    if(sal<0) sal = 0.0;
    salario = sal;
}
