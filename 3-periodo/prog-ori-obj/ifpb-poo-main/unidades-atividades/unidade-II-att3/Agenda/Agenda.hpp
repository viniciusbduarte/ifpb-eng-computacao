#include <iostream>
#include <string>
#include "Pessoa.hpp"

class Agenda{

private:
   Pessoa pessoas[10];
   int numPessoas; 

public:
   Agenda(int tPessoas);

   void armazenaPessoa(const string &nome, int idade, float altura);
   void armazenaPessoa(const Pessoa &p);

   void removePessoa(const string &nome);


   int buscaPessoa(const string &nome) const; // informa em que posição da agenda está a pessoa
   void imprimePovo() const; // imprime todos os dados de todas as pessoas da agenda
   void imprimePessoa(int i) const; // imprime os dados da pessoa que está na posição 'i' da agenda

}; 