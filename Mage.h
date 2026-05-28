#pragma once
#include "Player.h"
#include "Enemy.h"

class Mage : public Player {
public:
    Mage() : Player("Mage", 80, 80, 3, 15, 10.0f, 0.9f, 1, 1) {}

    void specialAbility(std::vector<Enemy*>& enemies, Map& map) override {
        health = maxHealth;

        for (Enemy* e : enemies) {
            if (e->isAlive()) {

                int kierunekX = e->getX() - getX();
                int kierunekY = e->getY() - getY();

                int nastepneX = e->getX();
                int nastepneY = e->getY();

                if (kierunekX > 0) nastepneX += 3;
                else if (kierunekX < 0) nastepneX -= 3;

                if (kierunekY > 0) nastepneY += 3;
                else if (kierunekY < 0) nastepneY -= 3;

             
                if (nastepneX < 1) nastepneX = 1;
                if (nastepneX >= map.getWidth() - 1) nastepneX = map.getWidth() - 2;
                if (nastepneY < 1) nastepneY = 1;
                if (nastepneY >= map.getHeight() - 1) nastepneY = map.getHeight() - 2;

               
                if (!map.getTile(nastepneX, nastepneY)->canEnter()) {
                    continue; 
                }

               
                map.getTile(e->getX(), e->getY())->clearOccupant();
                e->setPosition(nastepneX, nastepneY);
                map.getTile(nastepneX, nastepneY)->setOccupant(e);
            }
        }

        abilityUsed = true;
    }
};