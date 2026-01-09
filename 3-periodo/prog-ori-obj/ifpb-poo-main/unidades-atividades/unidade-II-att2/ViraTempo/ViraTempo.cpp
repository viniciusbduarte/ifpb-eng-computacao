#include <iostream> 
#include <string>
#include "ViraTempo.hpp"

using namespace std;


ViraTempo::ViraTempo(int t): tempo(0), incremento(1), limite(t) {}


void ViraTempo::virarTempo(){
    incremento = incremento * (-1);
}


void ViraTempo::avancarTempo(){    
    if ((tempo == 0 && incremento < 0) || (tempo == limite && limite != 0 && incremento > 0)) {
        virarTempo();
    }
    tempo = tempo + incremento;
}




void ViraTempo::mostrarTempo(){
    cout << "Tempo: " << tempo << endl;
}