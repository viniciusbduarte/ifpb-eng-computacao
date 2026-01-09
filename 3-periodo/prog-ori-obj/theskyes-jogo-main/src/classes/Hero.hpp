#ifndef HERO_HPP
#define HERO_HPP

#include "../../ASCII_Engine/ObjetoDeJogo.hpp"

class Hero : public ObjetoDeJogo {
private:
    int hp{100};
    int lifes{3};
    bool alive{true};
    bool chave{false};
public:
    using ObjetoDeJogo::ObjetoDeJogo; // herda o construtor

    inline bool isAlive(){
        return alive;
    
    }

    inline void dead(){
        lifes--;
        hp = 100;
        
        if (lifes == 0) alive = false;

    }

    inline void damage(){
        hp -= 20;
        
        if (hp <= 0){
            dead();
        }
    }

    inline int getLifes(){
        return lifes;
    }

    inline int getHP(){
        return hp;
    }


    inline void pegouChave(){
        chave = true;
    }

    inline bool isKey(){
        return chave;
    }

};

#endif
