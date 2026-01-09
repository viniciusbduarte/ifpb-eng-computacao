#include "PessoaFisica.hpp"

PessoaFisica::PessoaFisica(const string& n, const string& cpf) : Pessoa(n), CPF(cpf) {}

void PessoaFisica::setCPF(const string& cpf) { CPF = cpf; }
string PessoaFisica::getCPF() const { return CPF; }

string PessoaFisica::quemSouEu() const { return "PessoaFisica"; }
