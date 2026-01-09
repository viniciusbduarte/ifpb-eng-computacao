#include <iostream>
#include "Caso.hpp"

void Caso::setIdentificacao(string identificacao) {
    this->identificacao = identificacao;
}

void Caso::setData(string data) {
    this->data = data;
}

void Caso::setDelegado(const Policial& delegado_policial) {
    this->delegado = delegado_policial;
}

void Caso::inserirPeritos(const Policial& policial) {
    if (peritos.size() < maximo_peritos)
        peritos.push_back(policial);
    else
        cout << "Já há peritos suficientes!" << endl;
}

void Caso::inserirSuspeitos(const Suspeito& suspeito) {
    if (suspeitos.size() < maximo_suspeitos)
        suspeitos.push_back(suspeito);
    else
        cout << "Já há suspeitos suficientes!" << endl;
}

void Caso::inserirVestigios(const Vestigio& vestigio) {
    if (vestigios.size() < maximo_vestigios)
        vestigios.push_back(vestigio);
    else
        cout << "Já há vestígios suficientes!" << endl;
}

string Caso::toString() {
    string output = "Identificação: " + identificacao + "\n";
    output += "Data: " + data + "\n";
    output += "Delegado: " + delegado.getNome() + "\n";

    output += "\nPeritos:\n";
    for (const auto& p : peritos)
        output += "- " + p.getNome() + "\n";

    output += "\nSuspeitos:\n";
    for (const auto& s : suspeitos)
        output += "- " + s.toString() + "\n";

    output += "\nVestígios:\n";
    for (const auto& v : vestigios)
        output += "- " + v.toString() + "\n";

    return output;
}