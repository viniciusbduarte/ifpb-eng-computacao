#include "InputHandler.hpp"

InputHandler::InputHandler()
    : noChao(true), velocidadeX(0.0f), velY(0.0f)
{
    Keyboard::setMode(Keyboard::NONBLOCKING);
}

char InputHandler::readKey() const {
    return Keyboard::read();
}

bool InputHandler::handleKey(char key, Hero& hero, const std::vector<ObjetoDeJogo>& colisoes) {
    if (key == 'q') {
        return false; // encerra o jogo
    }

    // Movimento horizontal
    if (key == 'a') velocidadeX -= acel;
    else if (key == 'd') velocidadeX += acel;
    else if (noChao) {
        if (velocidadeX > 0) {
            velocidadeX -= desacel;
            if (velocidadeX < 0) velocidadeX = 0;
        } else if (velocidadeX < 0) {
            velocidadeX += desacel;
            if (velocidadeX > 0) velocidadeX = 0;
        }
    }

    velocidadeX = std::clamp(velocidadeX, -velMax, velMax);

    // Pulo
    if (key == 'w' && noChao) {
        velY = forcaPulo;
        noChao = false;
    }

    // Gravidade
    velY += gravidade;
    velY = std::clamp(velY, -15.0f, 15.0f);

    // Movimento horizontal pixel a pixel
    if (velocidadeX < 0) {
        for (int i = 0; i < (int)std::abs(velocidadeX); ++i) {
            hero.moveLeft(1);
            for (auto& c : colisoes) {
                if (hero.colideCom(c)) {
                    hero.moveRight(1);
                    break;
                }        }}
    } else if (velocidadeX > 0) {
        for (int i = 0; i < (int)velocidadeX; ++i) {
            hero.moveRight(1);
            for (auto& c : colisoes) {
                if (hero.colideCom(c)) {
                    hero.moveLeft(1);
                    break;
                }        }
            // colisão lateral se precisar
        }
    }

    // Movimento vertical pixel a pixel
    if (velY < 0) {
        for (int i = 0; i < (int)std::abs(velY); ++i) {
            hero.moveUp(1);
            for (auto& c : colisoes) {
                if (hero.colideCom(c)) {
                    hero.moveDown(1);
                    velY = 0;
                    break;
                }
            }
        }
    } else if (velY > 0) {
        for (int i = 0; i < (int)velY; ++i) {
            hero.moveDown(1);
            bool tocouChao = false;
            for (auto& c : colisoes) {
                if (hero.colideCom(c)) {
                    hero.moveUp(1);
                    velY = 0;
                    noChao = true;
                    tocouChao = true;
                    break;
                }
            }
            if (!tocouChao) noChao = false;
        }
    }

    return true;
}