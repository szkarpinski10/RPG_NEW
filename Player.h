#pragma once
#include "Character.h"
#include <vector>

class Enemy;
class Map;

/**
 * @brief Klasa bazowa dla gracza.
 */
class Player : public Character {
protected:
    int level;
    int exp;
    int expToNextLevel;
    bool abilityUsed;

public:
    /**
     * @brief Tworzy gracza z podanymi statystykami.
     */
    Player(std::string n, int h, int mH, int ar, int aD, float aR, float aS, int posX, int posY);

    /// @brief Zwraca poziom gracza.
    int getLevel() const { return level; }

    /// @brief Zwraca aktualny exp gracza.
    int getExp() const { return exp; }

    /// @brief Zwraca ilość expa potrzebną do następnego poziomu.
    int getExpToNextLevel() const { return expToNextLevel; }

    /// @brief Sprawdza czy umiejętność została użyta.
    bool isAbilityUsed() const { return abilityUsed; }

    /// @brief Ustawia pozycję X gracza.
    void setX(int newX) { x = newX; }

    /// @brief Ustawia pozycję Y gracza.
    void setY(int newY) { y = newY; }

    /**
     * @brief Dodaje exp graczowi.
     * @param amount ilość zdobytego expa
     */
    void gainExp(int amount);

    /**
     * @brief Zwiększa poziom gracza.
     */
    void levelUp();

    /**
     * @brief Resetuje stan użycia umiejętności specjalnej.
     */
    void resetAbility();

    /**
     * @brief Umiejętność specjalna gracza. Polimorfizm
     * @param enemies lista przeciwników
     * @param map mapa gry
     */
    virtual void specialAbility(std::vector<Enemy*>& enemies, Map& map) = 0;
};