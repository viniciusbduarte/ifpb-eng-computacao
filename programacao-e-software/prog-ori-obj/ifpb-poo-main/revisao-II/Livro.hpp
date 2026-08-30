#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Livro{
private:
    string titulo, autor;

public: 
    Livro(string titulo, string autor){
    setLivro(titulo, autor);
}
    //settters 
    void setLivro(string titulo, string autor);

    void display() const;

};