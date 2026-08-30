#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Livro.hpp"

class Mala{
private:
    vector<Livro> Livros;
    int capacidade_mala;
public:
    Mala(int capacidade);
    void guardarLivro(const Livro& livro);
    void display() const;

};