#include <iostream>
#include <string>
#include <vector>
#include "Livro.hpp"
using namespace std;

void Livro::setLivro(string titulo, string autor){
    this->titulo = titulo;
    this->autor = autor;
}

void Livro::display() const{
    cout << "Livro: " << titulo << "," << autor << endl;
}