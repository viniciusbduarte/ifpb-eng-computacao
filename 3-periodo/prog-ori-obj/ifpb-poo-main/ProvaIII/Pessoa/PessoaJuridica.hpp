#ifndef PESSOAJURIDICA_HPP
#define PESSOAJURIDICA_HPP

#include "Pessoa.hpp"

class PessoaJuridica : public Pessoa {
private:
    string CNPJ;
    string razaoSocial;

public:
    PessoaJuridica(const string& nomeFantasia, const string& razao, const string& cnpj);

    void setCNPJ(const string& cnpj);
    string getCNPJ() const;

    void setRazaoSocial(const string& razao);
    string getRazaoSocial() const;

    string quemSouEu() const override;
};

#endif
