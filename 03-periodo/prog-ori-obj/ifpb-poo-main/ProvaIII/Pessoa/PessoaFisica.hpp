#ifndef PESSOAFISICA_HPP
#define PESSOAFISICA_HPP

#include "Pessoa.hpp"

class PessoaFisica : public Pessoa {
protected:
    string CPF;

public:
    PessoaFisica(const string& n, const string& cpf);

    void setCPF(const string& cpf);
    string getCPF() const;

    string quemSouEu() const override;
};

#endif
