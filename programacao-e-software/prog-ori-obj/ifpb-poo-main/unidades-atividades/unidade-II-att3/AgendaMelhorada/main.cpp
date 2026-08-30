#include <iostream>
#include <string>
using std::cout, std::endl, std::string;

#include "Agenda.hpp"


int main () {
	Agenda A(10);

	A.armazenaPessoa("Abel", 22, 1.78);
	A.armazenaPessoa(Pessoa("Tiago", 20, 1.80));
	A.imprimePovo();

	int posicao = A.buscaPessoa("Tiago");
	if (posicao > 0)
    	A.imprimePessoa(posicao);

	A.removePessoa("Tiago");
	A.imprimePovo();
	
 	return 0;
}

