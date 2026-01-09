#ifndef FUNCIONARIO_HPP
#define FUNCIONARIO_HPP

#include "PessoaFisica.hpp"

class Funcionario : public PessoaFisica {
private:
    string matricula;
    double salario;

public:
    Funcionario(const string& n, const string& cpf, const string& mat, double sal);

    void setMatricula(const string& mat);
    string getMatricula() const;

    void setSalario(double sal);
    double getSalario() const;

    string quemSouEu() const override;
};

#endif
