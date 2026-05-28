#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class GUI {
private:
    sf::Font* font;
    sf::Sprite* weaponSprite;
    sf::CircleShape* fireball;
    bool* isFireballFlying;

public:
    GUI(sf::Font& f);
    ~GUI();

    void setWeaponSprite(sf::Sprite* weapon);
    void setFireball(sf::CircleShape* fb, bool* flying);

    void drawMap(sf::RenderWindow& window, Map& map);
    void drawPlayer(sf::RenderWindow& window, Player* player);
    void drawEnemies(sf::RenderWindow& window, const std::vector<Enemy*>& enemies);
    void drawFireball(sf::RenderWindow& window);
    void drawAll(sf::RenderWindow& window, Map& map, Player* player, const std::vector<Enemy*>& enemies);
    void setupFireball(sf::CircleShape& fireball, sf::Vector2f position);
};
