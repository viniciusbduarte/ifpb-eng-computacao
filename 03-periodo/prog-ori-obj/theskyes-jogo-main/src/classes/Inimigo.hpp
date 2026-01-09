#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include "../../ASCII_Engine/ObjetoDeJogo.hpp"

class Inimigo : public ObjetoDeJogo {
private:
    int hp{40};
    bool alive{true};
public:
    using ObjetoDeJogo::ObjetoDeJogo; // herda o construtor

    inline bool isAlive(){
        return alive;
    
    }


};

#endif
