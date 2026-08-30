#include "Bruxo.hpp"

Bruxo::Bruxo(string nome, string casa) : nome(nome) {
    setCasa(casa);
}

void Bruxo::setNome(string nome) {
    this->nome = nome;
}

void Bruxo::setCasa(string casa) {
    if (casa == "Grifinória" || casa == "Sonserina" || casa == "Corvinal" || casa == "Lufa-Lufa")
        this->casa = casa;
    else
        this->casa = "Indefinida";
}

string Bruxo::getNome() const {
    return nome;
}

string Bruxo::getCasa() const {
    return casa;
}

void Bruxo::pegarMala(Mala* m) {
    mala = m;
}

void Bruxo::soltarMala() {
    mala = nullptr;
}

void Bruxo::empunharVarinha(Varinha* v) {
    varinha = v;
}

void Bruxo::soltarVarinha() {
    varinha = nullptr;
}

void Bruxo::setFeitico(string f) {
    feitiço = f;
}

void Bruxo::lancarFeitico() const {
    if (varinha)
        cout << nome << " lançou o feitiço: " << feitiço << " com sua varinha de " 
             << varinha->getMadeira() << " (" << varinha->getComprimento() << " cm)" << endl;
    else
        cout << nome << " tentou lançar um feitiço, mas não empunha uma varinha!" << endl;
}

void Bruxo::display() const {
    cout << "===== Dados do Bruxo =====" << endl;
    cout << "Nome: " << nome << endl;
    cout << "Casa: " << casa << endl;
    if (varinha)
        cout << "Varinha: " << varinha->getMadeira() << ", " << varinha->getComprimento() << " cm" << endl;
    else
        cout << "Varinha: Nenhuma empunhada" << endl;

    if (mala)
        cout << "Mala: Carregando mala" << endl;
    else
        cout << "Mala: Nenhuma" << endl;

    cout << "==========================" << endl;
}
