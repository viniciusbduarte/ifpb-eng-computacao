#pragma once
#include <string>

class Carro {
private:
    std::string marca;
    std::string modelo;
	int ano;

public:
    Carro(std::string marca, std::string modelo, int ano);
    std::string getMarca() const;
    void setMarca(std::string marca);
    std::string getModelo() const;
    void setModelo(std::string modelo);
	int getAno() const;
    void setAno(int ano);
	std::string toString() const;
};
