#include <iostream> 
#include <string>
#pragma once

class ViraTempo{
private:
    int tempo;
    int incremento;
    int limite;
public:

    ViraTempo(int t);
    void virarTempo();
    void avancarTempo();
    void mostrarTempo();
};

