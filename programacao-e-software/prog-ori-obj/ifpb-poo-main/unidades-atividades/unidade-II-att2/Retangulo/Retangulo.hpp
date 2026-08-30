#pragma once 
#include <iostream>
#include <string>


class Retangulo{
private:
    int altura, largura;
public:
    Retangulo(int a = 1, int l = 1);
    void setAltura(int a);
    void setLargura(int l);

    int getAltura() const;
    int getLargura() const;

    int getPerimetro();
    int getArea();

    void desenharRetangulo();


};