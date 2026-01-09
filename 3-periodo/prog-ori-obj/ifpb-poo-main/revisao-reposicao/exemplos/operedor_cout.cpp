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

    bool operator==(const Cachorro& outro) const {
        return this->nome == outro.nome;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cachorro& c);
};

std::ostream& operator<<(std::ostream& os, const Cachorro& c) {
    os << "Cachorro: " << c.nome;
    return os;
}

int main() {
    Cachorro c1("Rex");
    Cachorro c2("Max");

    std::cout << c1 << std::endl;  
    std::cout << c2 << std::endl;  

    return 0;
}
