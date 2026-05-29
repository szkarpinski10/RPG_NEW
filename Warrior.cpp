#include "Warrior.h"

Warrior::Warrior() 
    : Player("Warrior", 120, 120, 8, 20, 5.0f, 1.2f, 1, 1) {
}

void Warrior::specialAbility(std::vector<Enemy*>& enemies, Map& map) {
    armor += 3;

    for (Enemy* e : enemies) {
        if (e->isAlive()) {
            e->takeDamage(20);
        }
    }
    abilityUsed = true;
}