#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include "../../ASCII_Engine/input/Keyboard.hpp"
#include "../classes/Hero.hpp"
#include "../../ASCII_Engine/ObjetoDeJogo.hpp"
#include <algorithm>

class InputHandler {
private:
    bool noChao;
    float velocidadeX;
    float velY;

    const float acel = 0.5f;
    const float desacel = 0.2f;
    const float velMax = 5.0f;

    const float gravidade = 1.0f;
    const float forcaPulo = -10.0f;

public:
    InputHandler();

    char readKey() const;
    bool handleKey(char key, Hero& hero, const std::vector<ObjetoDeJogo>& colisoes);
};

#endif
