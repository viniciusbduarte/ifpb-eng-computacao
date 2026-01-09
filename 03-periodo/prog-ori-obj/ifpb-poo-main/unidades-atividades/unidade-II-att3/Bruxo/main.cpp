#include <iostream> 
#include <string>
#include "Bruxo.hpp"


int main(){

    Varinha varin{};
    varin.setTipoMadeira("Madeira");
    varin.setNucleo("sla ome");
    varin.setComprimento(2);

    CapaBruxo capa(23, "Sonserina");


    Bruxo bruxo("Vinicius","Sonserina","sla oq sla oq", &varin, &capa );


    std::cout << bruxo.display();
    std::cout << bruxo.lancarFeitico();

    return 0;
}