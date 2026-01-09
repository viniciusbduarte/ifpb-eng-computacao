#include "CapaBruxo.hpp"

void CapaBruxo::setTamanho(float tamanho){
    this->tamanho = tamanho;
}
void CapaBruxo::setCasa(string casa) {
    if (casa == "Grifinória" || casa == "Lufa-Lufa" || casa == "Sonserina" || casa == "Corvinal") {
        this->casa = casa;
        cor = (casa == "Grifinória") ? "Vermelho" :
              (casa == "Lufa-Lufa") ? "Amarelo" :
              (casa == "Sonserina") ? "Verde" : "Azul";
    } else {
        cout << "Essa casa não existe" << endl;
        exit(1);
    }
}
void CapaBruxo::display(){
    cout << "Esses sãos os atributos da capa:" << endl
         << "Tamanho: " << getTamanho() << endl 
         << "Casa: " << getCasa() << endl 
         << "Cor: " << getCor() << endl; 
}


