#include "Pessoa.hpp"

Pessoa::Pessoa(const string& n) : nome(n) {}
void Pessoa::setNome(const string& n) { nome = n; }
string Pessoa::getNome() const { return nome; }
