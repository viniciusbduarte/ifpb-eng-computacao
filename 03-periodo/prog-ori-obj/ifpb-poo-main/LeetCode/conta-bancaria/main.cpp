#include <iostream>

using namespace std;

class ContaBancaria {
private: 
    int numeroConta;
    float saldo, taxa;

public:
    // Construtor com inicialização de saldo e taxa
    ContaBancaria(int c) : numeroConta(c), saldo(0.0), taxa(0.0) { }

    void deposito(float valorDeposito) {
        saldo = saldo + valorDeposito;
    }

    void saque(float valorSaque) {
        saldo = saldo - valorSaque;
    }

    void exibirSaldo() {
        cout << "Saldo: R$ " << saldo << endl;
    }
};

int main() {
    ContaBancaria usuario(1);

    usuario.deposito(20);
    usuario.exibirSaldo();  // Adiciona a chamada para exibir o saldo

    return 0;
}
