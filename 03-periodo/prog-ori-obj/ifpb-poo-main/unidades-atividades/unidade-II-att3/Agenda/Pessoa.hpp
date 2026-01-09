#include <iostream>
#include <string>
using namespace std;

class Pessoa{
private:
    string nome;
    int idade;
    float altura;
public:
    Pessoa();
    Pessoa(string n, int i, float a);
    ~Pessoa();

    void setNome(string nome);
    void setIdade(int idade);
    void setAltura(float altura);

    string getNome() const;
    int getIdade() const;
    float getAltura() const;

    string display() const;

};

    
