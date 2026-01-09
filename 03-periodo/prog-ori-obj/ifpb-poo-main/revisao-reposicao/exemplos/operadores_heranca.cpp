#include <iostream>
#include <string>

// Classe base
class Animal {
public:
    void falar() {
        std::cout << "Animal falando..." << std::endl;
    }
};

// Classe derivada que herda de Animal
class Cachorro : public Animal {
private:
    std::string nome;

public:
    Cachorro(std::string n) : nome(n) {}

    void falar() {
        std::cout << "Au au! Eu sou " << nome << std::endl;
    }

    // Sobrecarga do operador ==
    bool operator==(const Cachorro& outro) const {
        return this->nome == outro.nome;
    }
};

int main() {
    Cachorro c1("Rex");
    Cachorro c2("Rex");
    Cachorro c3("Max");

    c1.falar();  // Au au! Eu sou Rex
    c3.falar();  // Au au! Eu sou Max

    if (c1 == c2)
        std::cout << "c1 e c2 são iguais!" << std::endl;
    else
        std::cout << "c1 e c2 são diferentes!" << std::endl;

    if (c1 == c3)
        std::cout << "c1 e c3 são iguais!" << std::endl;
    else
        std::cout << "c1 e c3 são diferentes!" << std::endl;

    return 0;
}
