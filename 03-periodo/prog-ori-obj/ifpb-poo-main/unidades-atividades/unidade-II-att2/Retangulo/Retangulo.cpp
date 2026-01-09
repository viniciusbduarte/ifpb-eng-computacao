#include <iostream>
#include <string>
#include "Retangulo.hpp"
using namespace std;

//construtor 
Retangulo::Retangulo(int a, int l): altura(a), largura(l){
    altura = (a < 1 || a > 20) ? 1 : a;
    largura = (l < 1 || l > 20) ? 1 : l;
};

//sets
void Retangulo::setAltura(int a){
    altura = (a < 1 || a > 20) ? 1 : a;
}
void Retangulo::setLargura(int l){
    largura = (l < 1 || l > 20) ? 1 : l;
}

//gets
int Retangulo::getAltura() const{
    return altura;
}
int Retangulo::getLargura() const{
    return largura;
}

int Retangulo::getPerimetro(){
    return (largura * 2) + (altura * 2);
}
int Retangulo::getArea(){
    return largura * altura;
}




void Retangulo::desenharRetangulo() {
    // topo
    cout << "+";
    for (int i = 0; i < largura; i++) cout << "-";
    cout << "+\n";

    // meio
    for (int i = 0; i < altura; i++) {
        cout << "|";
        for (int j = 0; j < largura; j++) cout << " ";
        cout << "|\n";
    }

    // base
    cout << "+";
    for (int i = 0; i < largura; i++) cout << "-";
    cout << "+\n";
}

