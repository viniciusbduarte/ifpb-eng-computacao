#include <iostream> 
#include <string>
#include "Bruxo.hpp"


int main(){
    Bruxo bruxo;

    bruxo.setNome("Vinicius");
    bruxo.setCasa("Sonserina");
    bruxo.setFeitico("sla oq sla oq");


    std::cout << bruxo.display();
    std::cout << bruxo.lancarFeitico();

    return 0;
}