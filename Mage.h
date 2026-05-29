#pragma once
#include "Player.h"
#include "Enemy.h"

/**
 * @brief Klasa maga.
 */
class Mage : public Player {
public:
    /**
     * @brief Tworzy maga z podstawowymi statystykami.
     */
    Mage();

    /**
     * @brief Umiejętność specjalna maga.
     * @param enemies lista przeciwników
     * @param map mapa gry
     */
    void specialAbility(std::vector<Enemy*>& enemies, Map& map) override;
};