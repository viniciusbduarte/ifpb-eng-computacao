#include <iostream>
using std::cout, std::endl;
#include "Time.hpp"

int main() {
	Time t(16, 40);



	cout << "Objeto t: ";
	cout << t.toUniversal() << endl;

	Time outroTime;

	cout << "Objeto outroTime criado: ";
	cout << outroTime.toUniversal() << endl;

	outroTime = t;  // cada atributo de t é copiado para o respectivo atributo de outroTime

	cout << "Objeto outroTime após atribuição: ";
	cout << outroTime.toUniversal() << endl;

	outroTime.setTime(13, 58, 59);
    outroTime.tick();

	cout << "Objeto outroTime após setTime 13 0 0 e tick: ";
	cout << outroTime.toUniversal() << endl;

	cout << "Objeto t original: ";
	cout << t.toUniversal() << endl;

	return 0;
}
