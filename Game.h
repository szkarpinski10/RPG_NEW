#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"


class Game{
private:
    Map map;
    Player* player;
    Enemy* enemy;
    bool running;


public:
    Game(Player* p);
    ~Game();

    void start();
    void update();
    void handleInput(char input);
    bool isRunning() const;

};
