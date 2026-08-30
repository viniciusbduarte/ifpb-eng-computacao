#include "Carro.hpp"
#include <string> // necessário para std::string

Carro::Carro(std::string marca, std::string modelo, int ano)
    : marca(marca), modelo(modelo), ano(ano) {}

std::string Carro::getMarca() const {
    return marca;
}

void Carro::setMarca(std::string marca) {
    this->marca = marca;
}

std::string Carro::getModelo() const {
    return modelo;
}

void Carro::setModelo(std::string modelo) {
    this->modelo = modelo;
}


int Carro::getAno() const{
	return ano;
}

void Carro::setAno(int ano){
	this->ano = ano;
}


std::string Carro::toString() const{
	return "Marca:" + marca + ", Modelo:" + modelo + ", Ano:" + std::to_string(ano);
}