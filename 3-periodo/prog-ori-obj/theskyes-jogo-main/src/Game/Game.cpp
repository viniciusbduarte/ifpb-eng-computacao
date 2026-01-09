#include "Game.hpp"

// Construtor da classe Game, inicializa todos os objetos do jogo
Game::Game()
    : mapa("src/assets/bg.txt"),                                   // Mapa do jogo
      coracao("src/assets/coracao.txt", COR::VERMELHA),            // Sprite do coração para HUD de vida
      bau_aberto("src/assets/bau_aberto.txt", COR::AMARELA),       // Sprite do baú aberto
      vida("src/assets/vida_template.txt", COR::CINZA),            // Template da barra de vida
      barra_vida("src/assets/barra_vida.txt", COR::VERMELHA),      // Barra de vida preenchida
      camera(mapa, 0, 0, CAM_HEIGHT, CAM_WIDTH),                   // Câmera que acompanha o herói
      hero("Hero", SpriteAnimado("src/assets/hero2.txt", 14), 100, 20),  // Herói principal
      chave("Chave", SpriteAnimado("src/assets/chave.txt", 14, COR::AMARELA), 27, 305), // Chave para o baú
      bau("Baú", Sprite("src/assets/bau_fechado.txt"), 110, 630),  // Baú fechado
      inimigo("Inimigo", SpriteAnimado("src/assets/inimigo.txt", 16), 114, 200), // Inimigo do jogo
      screen(CAM_WIDTH, CAM_HEIGHT, ' '),                          // Tela onde tudo é desenhado
      sprite_menu("src/assets/menu.txt"),                          // Menu inicial
      input()                                                      // Gerenciador de input do teclado
{
    // Inicializa variáveis de controle do jogo
    cameraLin = 0;
    cameraCol = 0;
    running = false;
    menu_running = false;
    gameover_running = false;
    move_inimigo = false;

    // Inicializa vetor de moedas no jogo com suas posições e sprites
    moedas.clear();
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 77, 70);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 77, 385);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 47, 500);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 112, 150);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 112, 600);

    // Inicializa objetos de colisão do mapa para restringir movimento
    colisoes.clear();
    colisoes.emplace_back("Colisao do mapa", Sprite("src/assets/colide_piso1.txt"), 125, 4);
    colisoes.emplace_back("Colisao do mapa", Sprite("src/assets/colide_piso2.txt"), 125, 576);
    colisoes.emplace_back("Colisao do mapa", Sprite("src/assets/bloco2.txt"), 90, 50);
    colisoes.emplace_back("Colisao do mapa", Sprite("src/assets/bloco1.txt"), 60, 200);
    colisoes.emplace_back("Colisao do mapa", Sprite("src/assets/bloco1.txt"), 40, 300);
    colisoes.emplace_back("Colisao do mapa", Sprite("src/assets/bloco1.txt"), 60, 490);
    colisoes.emplace_back("Colisao do mapa", Sprite("src/assets/bloco2.txt"), 90, 376);
}

// Destrutor da classe Game
Game::~Game() {
}

// Inicializa o jogo, limpando a tela e posicionando a câmera no início
void Game::init() {
    system("clear");
    camera.moveTo(cameraLin, cameraCol);
} 

// Função para reinicializar todos os objetos do jogo após GameOver ou reinício
void Game::resetGameObjects() {
    // Cria novo herói com vida cheia
    hero = Hero("Hero", SpriteAnimado("src/assets/hero2.txt", 14), 100, 20);

    // Recria a chave no seu local inicial e ativa
    chave = Chave("Chave", SpriteAnimado("src/assets/chave.txt", 14, COR::AMARELA), 27, 305);

    // Recria baú fechado na posição inicial
    bau = Chest("Baú", Sprite("src/assets/bau_fechado.txt"), 110, 630);

    // Recria inimigo na posição inicial
    inimigo = Inimigo("Inimigo", SpriteAnimado("src/assets/inimigo.txt", 16), 114, 200);

    // Reseta movimento do inimigo
    move_inimigo = false;

    // Limpa e reinicializa as moedas, ativando-as e definindo posições originais
    moedas.clear();
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 77, 70);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 77, 385);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 47, 500);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 112, 150);
    moedas.emplace_back("Moeda", SpriteAnimado("src/assets/moeda.txt", 10, COR::AMARELA), 112, 600);
}

// Função chamada quando o jogo termina (Game Over)
void Game::GameOver() {
    // Reinicia todos os objetos para o estado inicial
    resetGameObjects();

    // Reinicia a posição da câmera para o início do mapa
    cameraLin = 0;
    cameraCol = 0;
    camera.moveTo(cameraLin, cameraCol);

    // Ativa o menu e desativa o estado de jogo rodando
    menu_running = true;
    running = false;

    // Exibe o menu
    menu();
}

// Loop principal do menu inicial
void Game::menu() {
    while (menu_running) {
        screen.clear();              // Limpa a tela para desenhar o menu
        sprite_menu.draw(screen, 0, 0); // Desenha o sprite do menu

        // Limpa terminal e imprime a tela atualizada
        std::cout << "\033[2J\033[H" << screen << std::endl;

        // Aguarda input do usuário
        char key = input.readKey();

        // Se o usuário apertar 'z', inicia o jogo
        if (key == 'z') {
            running = true;
            menu_running = false;
        }

        usleep(16000); // Pausa ~16ms para rodar a ~60 FPS
    }
}

// Atualiza o estado do jogo a cada frame
void Game::update() {
    // Lê tecla pressionada
    char key = input.readKey();

    // Trata o input, se retornar false o jogo para (ex: sair)
    if (!input.handleKey(key, hero, colisoes)) {
        running = false;
    }

    // Atualiza posição da câmera para centralizar no herói
    cameraLin = hero.getPosL() - CAM_HEIGHT / 2;
    cameraCol = hero.getPosC() - CAM_WIDTH / 2;

    // Garante que a câmera não saia dos limites do mapa
    cameraLin = std::clamp(cameraLin, 3, mapa.getAltura() - CAM_HEIGHT - 3);
    cameraCol = std::clamp(cameraCol, 3, mapa.getLarguraMax() - CAM_WIDTH - 3);

    camera.moveTo(cameraLin, cameraCol);

    // Controle do movimento do inimigo entre os limites 5 e 350
    if (inimigo.getPosC() <= 5) {
        move_inimigo = true;   // Mover para a direita
    } else if (inimigo.getPosC() >= 350) {
        move_inimigo = false;  // Mover para a esquerda
    }

    // Move inimigo na direção apropriada
    if (move_inimigo) inimigo.moveRight(1);
    else inimigo.moveLeft(1);

    // Variáveis estáticas para controle de cooldown de dano
    static bool podeLevarDano = true;
    static int danoCooldown = 0;

    // Se colidir com inimigo e puder levar dano, aplica dano e inicia cooldown
    if (hero.colideCom(inimigo) && podeLevarDano) {
        hero.damage();
        podeLevarDano = false;
        danoCooldown = 60;  // cooldown de 60 frames (~1 segundo)
    }

    // Atualiza cooldown para poder levar dano novamente
    if (!podeLevarDano) {
        if (--danoCooldown <= 0) {
            podeLevarDano = true;
        }
    }

    // Verifica se o herói caiu fora do mapa (buraco)
    constexpr int FALL_LIMIT = 130;
    if (hero.getPosL() > FALL_LIMIT){
        hero.dead();         // Marca herói como morto
        hero.moveTo(50, 50); // Teleporta ele para posição segura temporariamente
    }

    // Se o herói morreu, chama GameOver e sai do update para não continuar o frame
    if (!hero.isAlive()){
        GameOver();
        return;
    }

    // Verifica se o herói pegou a chave, desativa a chave e marca o herói com a chave
    if(hero.colideCom(chave)){
        chave.desativarObj();
        hero.pegouChave();
    }

    // Verifica se o herói está no baú com a chave, abre o baú e termina o jogo
    if(hero.colideCom(bau) && hero.isKey()){
        bau.trocarSprite(bau_aberto); // troca o sprite para baú aberto
        GameOver();
        return;
    }

    // Atualiza moedas: se herói colidir com moeda, desativa moeda
    for (auto& moeda : moedas) {
        if (hero.colideCom(moeda)) {
            moeda.desativarObj();
        }
        moeda.update();  // Atualiza animação da moeda
    }

    // Atualiza animação dos objetos móveis
    inimigo.update();
    chave.update();
    bau.update();
    hero.update();
}

// Renderiza todos os elementos na tela
void Game::render() {
    screen.clear(); // Limpa a tela antes de desenhar o frame

    // Função lambda para desenhar um objeto se estiver visível dentro da câmera
    auto drawIfVisible = [&](auto& obj, int offsetL = 0, int offsetC = 0) {
        int screenL = obj.getPosL() - cameraLin;
        int screenC = obj.getPosC() - cameraCol;
        obj.draw(screen, screenL + offsetL, screenC + offsetC);
    };

    // Desenha o fundo/mapa via câmera
    camera.draw(screen, 0, 0);

    // Desenha os objetos de colisão (obstáculos)
    for (auto& c : colisoes) {
        drawIfVisible(c, -2, -10);
    }

    // Desenha objetos do jogo
    drawIfVisible(chave);
    drawIfVisible(bau);
    drawIfVisible(inimigo, 0, -8);
    drawIfVisible(hero, -2, -7);

    // Desenha todas as moedas
    for (auto& moeda : moedas) {
        drawIfVisible(moeda);
    }

    // Desenha corações na HUD de acordo com a vida do herói
    int vidas = hero.getLifes();
    if (vidas >= 1) coracao.draw(screen, 5, 260);
    if (vidas >= 2) coracao.draw(screen, 5, 280);
    if (vidas >= 3) coracao.draw(screen, 5, 300);

    // Desenha barra de vida
    vida.draw(screen, 3, 5);
    int HP = hero.getHP();
    int baseX = 23;      // Posição base horizontal da barra
    int spriteWidth = 6; // Largura de cada barra de vida
    int numBarras = HP / 10; // Número de barras para desenhar

    for (int i = 0; i < numBarras; ++i) {
        barra_vida.draw(screen, 7, baseX + i * (spriteWidth + 1));
    }

    std::cout << "\033[2J\033[H" << screen << std::endl;
}

void Game::run() {
    while (true) {
        menu_running = true;
        running = false;

        menu(); // Espera apertar 'z'

        running = true;
        while (running) {
            update();
            render();
            usleep(16000);
        }
    }
}