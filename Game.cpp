#include <iostream>
#include "Game.h"




Game::Game(Player* p){
    player=p;
    running=true;
}

Game::~Game(){
    delete player;
    delete enemy;
    
}

void Game::start(){
    enemy = new Enemy("Goblin", 50, 50, 2, 10, 1.0f, 1.0f, 7, 7, 50);
    
    
    map.placeCharacter(player->getX(), player->getY(), player);
    map.placeCharacter(enemy->getX(), enemy->getY(), enemy);

      while (running) {
        update();
    }

}

void Game::update(){

    map.display();
    char input;
    std::cin>>input;
    handleInput(input);

    if (!enemy->isAlive()) {
        std::cout << "Enemy defeated! You win!\n";
        running = false;
    }

    if (!player->isAlive()) {
        std::cout << "You died! Game over.\n";
        running = false;
    }

   if (running) {
        enemy->randomMove(map);
        //map.moveCharacter(fromX,fromY, enemy->getX(), enemy->getY());
        float enemyRange = enemy->getAttackRange();
        int playerX = player->getX();
        int playerY = player->getY();
        int distance = abs(enemy->getX() - playerX) + abs(enemy->getY() - playerY);

        if (distance <= enemyRange) {
            enemy->attackTarget(*player);
            std::cout << "Enemy attacked you!\n";
        }

    }
}
void Game::handleInput(char input){
    int dx=0;
    int dy=0;

        if (input == 'w' || input == 'W') {
        dy = -1;
    } else if (input == 's' || input == 'S') {
        dy = 1;
    } else if (input == 'a' || input == 'A') {
        dx = -1;
    } else if (input == 'd' || input == 'D') {
        dx = 1;
    } else if (input == 'e' || input == 'E') {
        player->specialAbility(*enemy);
        std::cout << "You used special ability!\n";
    } else if (input == 'q' || input == 'Q') {
        running = false;
    }
    else if (input == 'f' || input == 'F') {
        float playerRange = player->getAttackRange();
        int enemyX = enemy->getX();
        int enemyY = enemy->getY();

        int distance = abs(player->getX() - enemyX) + abs(player->getY() - enemyY);

        if (distance <= playerRange) {
            player->attackTarget(*enemy);
            std::cout << "atak!\n";
        } else {
            std::cout << "za daleko\n";
        }
    }
    

    if (dx != 0 || dy != 0) {
    int newX = player->getX() + dx;
    int newY = player->getY() + dy;

    if (map.checkIfWalkable(newX, newY)) {
        map.moveCharacter(player->getX(), player->getY(), newX, newY);
    } else {
        std::cout << "Can't move there!\n";
    }
}

}

bool Game::isRunning() const {
    return running;
}