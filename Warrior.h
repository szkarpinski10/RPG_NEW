#pragma once
#include "Player.h"
#include "Enemy.h"

/**
 * @brief Klasa wojownika.
 */
class Warrior : public Player {
public:
    /**
     * @brief Tworzy wojownika z podstawowymi statystykami.
     */
    Warrior();

    /**
     * @brief Umiejętność specjalna wojownika.
     * @param enemies lista przeciwników
     * @param map mapa gry
     */
    void specialAbility(std::vector<Enemy*>& enemies, Map& map) override;
};