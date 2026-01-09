#include <iostream>
#include <string>
#include "Varinha.hpp"


int main(){
     
Varinha varinhaqualquer{};

varinhaqualquer.setTipoMadeira("Madeira");
varinhaqualquer.setNucleo("sla ome");
varinhaqualquer.setComprimento(2);

varinhaqualquer.display();



    return 0;
}