#ifndef GAME_HPP
#define GAME_HPP

// Includes essenciais para sprites, objetos de jogo, entrada e estruturas padrão
#include "../../ASCII_Engine/SpriteBuffer.hpp"  // Buffer para desenho na tela
#include "../../ASCII_Engine/SpriteView.hpp"    // Visualização do sprite com câmera
#include "../../ASCII_Engine/ObjetoDeJogo.hpp"  // Classe base para objetos do jogo
#include "../../ASCII_Engine/Sprite.hpp"        // Classe de sprite básico
#include "../classes/Hero.hpp"                   // Classe herói do jogo
#include "../classes/Moeda.hpp"                  // Classe moeda
#include "../classes/Inimigo.hpp"                // Classe inimigo
#include "../classes/Chest.hpp"                  // Classe baú
#include "../classes/Chave.hpp"                  // Classe chave
#include "../InputHandler/InputHandler.hpp"     // Gerenciador de entrada do teclado

#include <set>            // Para possíveis estruturas de conjunto
#include <cmath>          // Funções matemáticas
#include <algorithm>      // std::clamp para limitar valores
#include <iostream>       // Para input/output padrão
#include <unistd.h>       // usleep() para delays
#include <vector>         // Vetores dinâmicos

// Definição da classe principal do jogo
class Game {
private:
    // Constantes para tamanho da câmera (altura e largura da viewport)
    static constexpr int CAM_HEIGHT = 96;
    static constexpr int CAM_WIDTH = 320;

    // Sprites usados no jogo
    Sprite mapa;                // Mapa do jogo (background)
    Sprite coracao;             // Sprite do coração (vida)
    Sprite vida;                // Template para barra de vida
    Sprite barra_vida;          // Barra de vida preenchida
    Sprite bau_aberto;          // Sprite do baú aberto

    // Vetores de objetos do jogo
    std::vector<ObjetoDeJogo> colisoes;  // Objetos que causam colisão (obstáculos)
    std::vector<ObjetoDeJogo> moedas;    // Moedas para coletar

    // Objetos especiais do jogo
    Chave chave;                 // Chave para abrir o baú
    Chest bau;                   // Baú do tesouro
    Sprite sprite_menu;          // Sprite para a tela do menu

    // Controle da câmera e tela
    SpriteView camera;           // Visão da câmera que foca no herói
    SpriteBuffer screen;         // Buffer de desenho (tela)

    // Personagens principais
    Hero hero;                   // Herói controlado pelo jogador
    Inimigo inimigo;             // Inimigo do jogo

    // Gerenciador de entrada do teclado
    InputHandler input;

    // Variáveis de controle da posição da câmera
    int cameraLin, cameraCol;

    // Flags para controle do estado do jogo
    bool running;                // Jogo rodando?
    bool menu_running;           // Menu ativo?
    bool gameover_running;       // Tela de game over ativa?
    bool move_inimigo;           // Controle do movimento do inimigo

public:
    // Construtor e destrutor
    Game();
    ~Game();

    // Métodos para controlar o fluxo do jogo
    void menu();                     // Exibe e gerencia o menu inicial
    void init();                     // Inicializa o estado do jogo
    void update();                   // Atualiza o estado do jogo a cada frame
    void render();                   // Desenha o estado atual do jogo na tela
    void run();                      // Loop principal do jogo
    void resetGameObjects();         // Reseta Objetos do Jogo

    // Método chamado ao terminar o jogo (Game Over)
    void GameOver();
    
};

#endif // GAME_HPP
