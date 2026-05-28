#include "GUI.h"

GUI::GUI(sf::Font& f) {
    font = &f;
    weaponSprite = nullptr;
    fireball = nullptr;
    isFireballFlying = nullptr;
    
}

GUI::~GUI() {}

void GUI::setWeaponSprite(sf::Sprite* weapon) {
    weaponSprite = weapon;
}

void GUI::setFireball(sf::CircleShape* fb, bool* flying) {
    fireball = fb;
    isFireballFlying = flying;
}

void GUI::drawMap(sf::RenderWindow& window, Map& map) {
    map.display(window);
}

void GUI::drawPlayer(sf::RenderWindow& window, Player* player) {
    if (!player->isAlive()) return;

    sf::RectangleShape playerShape({32.f, 32.f});
    playerShape.setPosition({player->getX() * 32.f, player->getY() * 32.f});

    if (player->getName() == "Warrior") {
        playerShape.setFillColor(sf::Color::Yellow);
    }
    else if (player->getName() == "Mage") {
        playerShape.setFillColor(sf::Color::Magenta);
    }
    else if (player->getName() == "Rogue") {
        playerShape.setFillColor(sf::Color::Blue);
    }

    window.draw(playerShape);

    if (weaponSprite != nullptr) {
        window.draw(*weaponSprite);
    }
}

void GUI::drawEnemies(sf::RenderWindow& window, const std::vector<Enemy*>& enemies) {
    sf::Text enemyText(*font);
    enemyText.setCharacterSize(18);

    for (Enemy* e : enemies) {
        if (e == nullptr || !e->isAlive()) continue;

        sf::RectangleShape enemyShape({32.f, 32.f});
        sf::Vector2f enemyPos(e->getX() * 32.f, e->getY() * 32.f);
        enemyShape.setPosition(enemyPos);

        bool isOrc = (e->getName().rfind("Orc", 0) == 0);

        if (isOrc) {
           
            enemyShape.setSize({40.f, 40.f});
            enemyShape.setPosition({enemyPos.x - 4.f, enemyPos.y - 4.f});
            enemyShape.setFillColor(sf::Color::Red);
            enemyShape.setOutlineThickness(3.f);
            enemyShape.setOutlineColor(sf::Color::Black);

            enemyText.setString("O");
            enemyText.setFillColor(sf::Color::White);
            enemyText.setPosition({enemyPos.x + 12.f, enemyPos.y + 10.f});
        }
        else {
           
            enemyShape.setFillColor(sf::Color(0, 200, 0));
            enemyShape.setOutlineThickness(2.f);
            enemyShape.setOutlineColor(sf::Color(138, 43, 226));

            enemyText.setString("G");
            enemyText.setFillColor(sf::Color::Black);
            enemyText.setPosition({enemyPos.x + 8.f, enemyPos.y + 6.f});
        }

        window.draw(enemyShape);
        window.draw(enemyText);
    }
}

void GUI::drawFireball(sf::RenderWindow& window) {
    if (isFireballFlying != nullptr && *isFireballFlying && fireball != nullptr) {
        window.draw(*fireball);
    }
}

void GUI::drawAll(sf::RenderWindow& window, Map& map, Player* player,
                  const std::vector<Enemy*>& enemies) {
    drawMap(window, map);
    drawPlayer(window, player);
    drawEnemies(window, enemies);
    drawFireball(window);
}

void GUI::setupFireball(sf::CircleShape& fireball, sf::Vector2f position) {
    fireball.setPosition(position);
    fireball.setRadius(8.f);
    fireball.setFillColor(sf::Color(255, 140, 0));
    fireball.setOutlineThickness(2.f);
    fireball.setOutlineColor(sf::Color::Red);
}