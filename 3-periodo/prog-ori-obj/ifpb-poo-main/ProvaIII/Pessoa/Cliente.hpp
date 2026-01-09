#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include "PessoaFisica.hpp"

class Cliente : public PessoaFisica {
private:
    string telefone;
    string endereco;

public:
    Cliente(const string& n, const string& cpf, const string& tel, const string& end);

    void setTelefone(const string& tel);
    string getTelefone() const;

    void setEndereco(const string& end);
    string getEndereco() const;

    string quemSouEu() const override;
};

#endif
