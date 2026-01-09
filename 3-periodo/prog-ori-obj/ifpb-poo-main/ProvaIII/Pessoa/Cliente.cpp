#include "Cliente.hpp"

Cliente::Cliente(const string& n, const string& cpf, const string& tel, const string& end)
    : PessoaFisica(n, cpf), telefone(tel), endereco(end) {}

void Cliente::setTelefone(const string& tel) { telefone = tel; }
string Cliente::getTelefone() const { return telefone; }

void Cliente::setEndereco(const string& end) { endereco = end; }
string Cliente::getEndereco() const { return endereco; }

string Cliente::quemSouEu() const { return "Cliente"; }
