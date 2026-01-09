#include <iostream>
#include <string>
#include "Data.hpp"


Data::Data(int d, int m, int a) {
    dia = (d < 1 || d > 31) ? 1 : d;
    mes = (m < 1 || m > 12) ? 1 : m;
    ano = (a < 1) ? 1 : a;
}



//sets
    void Data::setDia(int d){
        dia = ((d<1)&&(d>31)) ? 1 : d;
    }
    void Data::setMes(int m){
        mes = ((m<1)&&(m>12)) ? 1 : m;
    }
    void Data::setAno(int a){
        ano = (a<1) ? 1 : a;
    }

//gets
    int Data::getDia() const{
        return dia;
    }
    int Data::getMes() const{
        return mes;
    }
    int Data::getAno() const{
        return ano;
    }


    std::string Data::toString(){
        return "Data: " + std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(ano);
    }