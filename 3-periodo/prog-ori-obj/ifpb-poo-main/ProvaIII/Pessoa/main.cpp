#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PessoaFisica.hpp"
#include "PessoaJuridica.hpp"
#include "Funcionario.hpp"
#include "Cliente.hpp"
using namespace std;

int main() {
    srand(time(0));

    Pessoa* pessoas[10];

    for (int i = 0; i < 10; i++) {
        int tipo = rand() % 4;
        switch (tipo) {
            case 0:
                pessoas[i] = new PessoaFisica("NomePF" + to_string(i), "CPF" + to_string(i));
                break;
            case 1:
                pessoas[i] = new PessoaJuridica("NomeFantasia" + to_string(i), "Razao" + to_string(i), "CNPJ" + to_string(i));
                break;
            case 2:
                pessoas[i] = new Funcionario("NomeFunc" + to_string(i), "CPF" + to_string(i), "MAT" + to_string(i), 3000 + i*100);
                break;
            case 3:
                pessoas[i] = new Cliente("NomeCli" + to_string(i), "CPF" + to_string(i), "Telefone" + to_string(i), "Endereco" + to_string(i));
                break;
        }
    }

    for (int i = 0; i < 10; i++) {
        cout << "Pessoa[" << i << "] é: " << pessoas[i]->quemSouEu() << endl;
    }

    for (int i = 0; i < 10; i++) {
        delete pessoas[i];
    }

    return 0;
}
