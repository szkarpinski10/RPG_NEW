#pragma once
#include "Player.h"
#include "Enemy.h"

    
class Warrior : public Player {
public:

    // nazwa, zycie, max zycie, armor, attackdamage, attackrange, attackspeed, posx i pos y
    Warrior(): Player("Warrior", 120, 120, 8, 20, 5.0f, 1.2f, 1, 1) {}

    void specialAbility(std::vector<Enemy*>& enemies, Map& map) override {
        armor += 5; // Wojownik: bezpośrednio zwiększasz swój pancerz
        
        for (Enemy* e : enemies) {
            if (e->isAlive()) {
                e->takeDamage(20); 
            }
        }
        abilityUsed = true;
        
    }
};