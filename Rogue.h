#pragma once
#include "Player.h"
#include "Enemy.h"

/**
 * @brief Klasa łotra.
 */
class Rogue : public Player {
public:
    /**
     * @brief Tworzy łotra z podstawowymi statystykami.
     */
    Rogue();

    /**
     * @brief Umiejętność specjalna łotra.
     * @param enemies lista przeciwników
     * @param map mapa gry
     */
    void specialAbility(std::vector<Enemy*>& enemies, Map& map) override;
};