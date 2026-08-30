#include <iostream> 
#include <string>

#include "Bruxo.hpp"

Bruxo::Bruxo(std::string nm , std::string cs , std::string fp): nome(nm), casa(cs), feitico_predileto(fp){}


//gets
std::string Bruxo::getNome() const{
    return nome;
}
std::string Bruxo::getCasa() const{
    return casa;
}
std::string Bruxo::getFeitico() const{
    return feitico_predileto;
}
std::string Bruxo::display() const{
    return "Bruxo: " + nome + "\n" + "Casa: " + casa + "\n" + "Feitiço Predileto: " + feitico_predileto + "\n";
}
std::string Bruxo::lancarFeitico() const{
    return "Lançando Feitiço " + feitico_predileto + "\n";
}

//sets 
void Bruxo::setNome(std::string nm){
    nome = nm;
}
void Bruxo::setCasa(std::string cs){
    if((cs != "Grifinória" ) && (cs != "Sonserina" ) && (cs != "Lufa-Lufa" ) && (cs != "Corvinal" ) ) casa = " ";
    else casa = cs;
}
void Bruxo::setFeitico(std::string fp){
    feitico_predileto = fp;
}
