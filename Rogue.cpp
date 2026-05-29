
#include "Rogue.h"

Rogue::Rogue() 
    : Player("Rogue", 100, 90, 4, 15, 4.0f, 0.5f, 1, 1) {
}

void Rogue::specialAbility(std::vector<Enemy*>& enemies, Map& map) {
    attackDamage += 7;
    attackSpeed += 0.5f;

    abilityUsed = true;
}