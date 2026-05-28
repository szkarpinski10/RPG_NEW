#pragma once
#include "Character.h"
#include "Map.h"
#include <cstdlib>

class Enemy : public Character {
private:
    int expReward;
   

public:
    Enemy(std::string n, int h, int mH, int ar, int aD,float aR, float aS, int posX, int posY, int expR)
        :Character(n, h, mH, ar, aD, aR, aS, posX, posY) {

        expReward = expR;
    }

    int getExpReward() const {return expReward;}

    sf::Clock attackClockEnemy;
    sf::Clock enemyMoveClock;


    void randomMove(Map& map) {
        int dx = 0;
        int dy = 0;

        int direction = rand() % 5;

        if (direction == 0) {
        dy = -1;
        }

        else if (direction == 1) {
        dy = 1;
        }

        else if (direction == 2) {
        dx = -1;
        }

        else if (direction == 3) {
        dx = 1;
        }

    int newX = x + dx;
    int newY = y + dy;

    map.moveCharacter(x, y, newX, newY);
}



};

