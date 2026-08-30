#include <iostream>
#include <string>
#include "Retangulo.hpp"
using namespace std;

int main(){
    Retangulo ret{22,0};

    cout << "Altura: " << ret.getAltura() << "\nLargura: " << ret.getLargura() << endl;
    ret.desenharRetangulo();

    return 0;
}