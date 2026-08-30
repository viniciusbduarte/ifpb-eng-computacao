#include "Funcionario.hpp"

Funcionario::Funcionario(const string& n, const string& cpf, const string& mat, double sal)
    : PessoaFisica(n, cpf), matricula(mat), salario(sal) {}

void Funcionario::setMatricula(const string& mat) { matricula = mat; }
string Funcionario::getMatricula() const { return matricula; }

void Funcionario::setSalario(double sal) { salario = sal; }
double Funcionario::getSalario() const { return salario; }

string Funcionario::quemSouEu() const { return "Funcionario"; }
