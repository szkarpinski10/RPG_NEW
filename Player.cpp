#include "Player.h"

Player::Player(std::string n, int h, int mH, int ar, int aD, float aR, float aS, int posX, int posY)
    : Character(n, h, mH, ar, aD, aR, aS, posX, posY) {
    level = 1;
    exp = 0;
    expToNextLevel = 100;
    abilityUsed = false;
}

void Player::gainExp(int amount) {
    exp += amount;
    while (exp >= expToNextLevel) {
        exp -= expToNextLevel;
        levelUp();
    }
}

void Player::levelUp() {
    level++;
    expToNextLevel += 200;
    maxHealth += 20;
    health = maxHealth;
    attackDamage += 5;
}

void Player::resetAbility() {
    abilityUsed = false;
}