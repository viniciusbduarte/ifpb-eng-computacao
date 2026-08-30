#pragma once
#include <string>

class Bruxo{
private:
    std::string nome;
    std::string casa;
    std::string feitico_predileto;
    
public:
    Bruxo(std::string nm = " ", std::string cs = " ", std::string fp = " ");
    std::string getNome() const;
    void setNome(std::string nm);
    std::string getCasa() const;
    void setCasa(std::string cs);
    std::string getFeitico() const;
    void setFeitico(std::string fp);
    std::string display() const;
    std::string lancarFeitico() const;
};