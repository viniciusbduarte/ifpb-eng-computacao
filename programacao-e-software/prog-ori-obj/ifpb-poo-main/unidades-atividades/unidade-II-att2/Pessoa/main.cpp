#include <iostream>
#include <string>
#include "Pessoa.hpp"

using namespace std;

int main() {
    Pessoa p1("Vinicius", "12345678901", true);
    p1.apresentar();

    Pessoa p2("Kalilca");  // CPF default e CPFvalido como false
    p2.apresentar();

    return 0;
}
