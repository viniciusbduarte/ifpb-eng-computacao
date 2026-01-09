#include "Bruxo.hpp"

// Construtores
Bruxo::Bruxo(string nm, string cs, string fp, Varinha *v, CapaBruxo *c)
    : nome(nm), casa(cs), feitico_predileto(fp), varinha(v), capabruxo(c) {}

Bruxo::Bruxo(string nm, string cs, string fp)
    : nome(nm), casa(cs), feitico_predileto(fp), varinha(nullptr), capabruxo(nullptr) {}

// Gets
string Bruxo::getNome() const { return nome; }
string Bruxo::getCasa() const { return casa; }
string Bruxo::getFeitico() const { return feitico_predileto; }

// Sets
void Bruxo::setNome(string nm) { nome = nm; }
void Bruxo::setCasa(string cs) {
    if (cs != "Grifinória" && cs != "Sonserina" && cs != "Lufa-Lufa" && cs != "Corvinal")
        casa = "";
    else
        casa = cs;
}
void Bruxo::setFeitico(string fp) { feitico_predileto = fp; }

// Métodos
string Bruxo::display() const {
    string d = "Bruxo: " + nome + "\nCasa: " + casa + "\nFeitiço Predileto: " + feitico_predileto + "\n";
    if (varinha) d += varinha->display();
    if (capabruxo) d += capabruxo->display();
    return d;
}

string Bruxo::lancarFeitico() const {
    return "Lançando Feitiço " + feitico_predileto + "\n";
}
