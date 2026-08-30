#pragma once
#include <iostream>
#include <string>


class Data{
private:
    int dia, mes, ano;
public:
    Data(int d, int m ,int a);

//sets
    void setDia(int d);
    void setMes(int m);
    void setAno(int a);
//gets
    int getDia() const;
    int getMes() const;
    int getAno() const;

    std::string toString();
};
