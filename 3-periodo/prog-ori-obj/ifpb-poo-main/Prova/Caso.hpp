#pragma once
#include <string>
#include <vector>
#include "Policial.hpp"
#include "Suspeito.hpp"
#include "Vestigio.hpp"
using namespace std;

class Caso {
private:
    string identificacao;
    string data;
    Policial delegado;
    vector<Policial> peritos;
    vector<Suspeito> suspeitos;
    vector<Vestigio> vestigios;
    const int maximo_peritos = 5;
    const int maximo_suspeitos = 10;
    const int maximo_vestigios = 20;

public:
    Caso(string identificacao, string data, const Policial& delegado)
        : identificacao(identificacao), data(data), delegado(delegado) {}

    void setIdentificacao(string identificacao);
    void setData(string data);
    void setDelegado(const Policial& delegado_policial);

    void inserirPeritos(const Policial& policial);
    void inserirSuspeitos(const Suspeito& suspeito);
    void inserirVestigios(const Vestigio& vestigio);

    string toString();
};