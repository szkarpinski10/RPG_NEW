#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "HUD.h"


class Game{
private:
    Map map;
    Player* player;
    Enemy* enemy;
    bool running;
    HUD* hud;

    sf::Font font;
    sf::Clock enemyMoveClock;
    sf::Clock playerMoveClock;
    sf::Clock specialAbilityClock;

  

    void handleInput(sf::Keyboard::Key key);
    void render(sf::RenderWindow& window);

public:
    Game(Player* p);
    ~Game();

    void start(sf::RenderWindow& window);
    void update();
    bool isRunning() const;

};
