#ifndef PESSOA_HPP
#define PESSOA_HPP

#include <string>
using namespace std;

class Pessoa {
protected:
    string nome;

public:
    Pessoa(const string& n);
    void setNome(const string& n);
    string getNome() const;

    virtual string quemSouEu() const = 0; 
    virtual ~Pessoa() {}
};

#endif
