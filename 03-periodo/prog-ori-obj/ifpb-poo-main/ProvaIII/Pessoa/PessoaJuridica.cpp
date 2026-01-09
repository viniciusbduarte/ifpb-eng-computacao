#include "PessoaJuridica.hpp"

PessoaJuridica::PessoaJuridica(const string& nomeFantasia, const string& razao, const string& cnpj)
    : Pessoa(nomeFantasia), razaoSocial(razao), CNPJ(cnpj) {}

void PessoaJuridica::setCNPJ(const string& cnpj) { CNPJ = cnpj; }
string PessoaJuridica::getCNPJ() const { return CNPJ; }

void PessoaJuridica::setRazaoSocial(const string& razao) { razaoSocial = razao; }
string PessoaJuridica::getRazaoSocial() const { return razaoSocial; }

string PessoaJuridica::quemSouEu() const { return "PessoaJuridica"; }
