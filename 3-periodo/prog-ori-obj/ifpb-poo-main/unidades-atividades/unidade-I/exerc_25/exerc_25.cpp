#include <iostream>

int main() {
    int paradas{1};
    double km{0}, litros{0};
    double totaldelitros{0}, totalkm{0};

    while (true) {
        std::cout << "\nParada " << paradas << std::endl;

        std::cout << "Digite a quilometragem rodada desde o último abastecimento (-1 para encerrar): ";
        std::cin >> km;

        if (km == -1) break;

        if (km <= -1) {
            std::cout << "Quantidade de Km inválida!" << std::endl;
            continue;   
        }

        std::cout << "Digite a quantidade de litros abastecidos: ";
        std::cin >> litros;

        if (litros <= 0) {
            std::cout << "Quantidade de litros inválida!" << std::endl;
            continue;   
        }

        double consumo = km / litros;
        totaldelitros += litros;
        totalkm += km;

        std::cout << "Consumo atual: " << consumo << " Km/L" << std::endl;
        std::cout << "Total de litros: " << totaldelitros << " L" << std::endl;
        std::cout << "Total rodado: " << totalkm << " Km" << std::endl;

        paradas++;
    }

    std::cout << "\nEncerrando programa..." << std::endl;
    return 0;
}
