#pragma once
#include "Character.h"
#include <cstdlib>

class Enemy : public Character {
private:
    int expReward;

public:
    Enemy(std::string n, int h, int mH, int ar, int aD,
          float aR, float aS, int posX, int posY, int expR)
        : Character(n, h, mH, ar, aD, aR, aS, posX, posY) {

        expReward = expR;
    }

    int getExpReward() const {
        return expReward;
    }

    void randomMove() {
        int direction = rand() % 5;

        if (direction == 0) {
            move(0, -1);
        }

        if (direction == 1) {
            move(0, 1);
        }

        if (direction == 2) {
            move(-1, 0);
        }

        if (direction == 3) {
            move(1, 0);
        }
        if(direction == 4){
            move(0,0);
        }
    }
};

