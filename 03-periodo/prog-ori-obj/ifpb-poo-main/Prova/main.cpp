#include <iostream>
using namespace std;
#include "Policial.hpp"
#include "Suspeito.hpp"
#include "Vestigio.hpp"
#include "Caso.hpp"

int main() {
    Policial Delegado1("Joao da Silva", "Delegado");
    Suspeito Suspeito1("Cleytin do Lava Jato", true);
    Vestigio vestigio1("Evidencia1", "Biológico", true);

    Caso caso1("Nome do Caso", "01/02/25", Delegado1);
    caso1.inserirSuspeitos(Suspeito1);
    caso1.inserirVestigios(vestigio1);

    cout << caso1.toString();

    return 0;
}