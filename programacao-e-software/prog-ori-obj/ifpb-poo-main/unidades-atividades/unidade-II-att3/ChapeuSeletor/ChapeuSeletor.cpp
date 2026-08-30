#include "ChapeuSeletor.hpp"
#include <iostream>
#include <random>
using namespace std;

ChapeuSeletor::ChapeuSeletor(){};
ChapeuSeletor::~ChapeuSeletor(){};

void ChapeuSeletor::recepcionar() {
    cout << "Não há nada escondido em "
         << "sua cabeça que o Chapéu Seletor não consiga ver, "
         << "por isso é só me porem na cabeça que vou dizer "
         << "em que casa de Hogwarts deverão ficar" << endl;
}

void ChapeuSeletor::sortearcasa() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 4);

    int numero = dist(gen);

    switch (numero) {
        case 1:
            cout << "Grifinória" << endl;
            break;
        case 2:
            cout << "Lufa-Lufa" << endl;
            break;
        case 3:
            cout << "Sonserina" << endl;
            break;
        case 4:
            cout << "Corvinal" << endl;
            break;
        default:
            cout << "Erro no sorteio!" << endl;
            break;
    }
}
