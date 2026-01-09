#include <iostream>
#include <string>
#include "Mala.hpp"

void Mala::guardarLivro(const Livro& livro){
    if( Livros.size() < capacidade_mala) Livros.push_back(livro);
    else cout << "A mala está cheia!" << endl;
}

void Mala::display() const{
    cout << "Livros na mala:" << endl;
    for(const auto& livro : Livros) livro.display();
}

Mala::Mala(int capacidade): capacidade_mala(capacidade){}