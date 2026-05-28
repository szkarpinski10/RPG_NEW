#include <iostream>
#include <cmath>
#include "Game.h"
#include "Player.h"
#include "HUD.h"
#include "Enemy.h"
#include "GUI.h"

Game::Game(Player* p) {
    player = p;
    running = true;
    weaponSprite = nullptr;

    if (!font.openFromFile("PressStart2P-Regular.ttf")) {
        std::cout << "blad czcionki\n";
    }
    
    hud = new HUD(font);
    gui = new GUI(font);

    if (!warriorWeaponImg.loadFromFile("LongSword-1.png") ||
        !rogueWeaponImg.loadFromFile("SmallSword.png") ||
        !mageWeaponImg.loadFromFile("Staff4.png")) {
        std::cout << "blad grafik broni\n";
    }

    if (player->getName() == "Warrior") {
        weaponSprite = new sf::Sprite(warriorWeaponImg);
    }
    else if (player->getName() == "Mage") {
        weaponSprite = new sf::Sprite(mageWeaponImg);
    }
    else if (player->getName() == "Rogue") {
        weaponSprite = new sf::Sprite(rogueWeaponImg);
    }

    if (weaponSprite != nullptr) {
        sf::FloatRect wymiaryBroni = weaponSprite->getLocalBounds();
        weaponSprite->setOrigin({wymiaryBroni.size.x / 2.f, wymiaryBroni.size.y});
    }

    // ← PRZENIESIONE TUTAJ, bo weaponSprite jest tworzony WYŻEJ
    gui->setWeaponSprite(weaponSprite);
    gui->setFireball(&fireball, &isfireballflying);  // ← uważaj na nazwę!
}

Game::~Game() {
    
    delete hud;
    delete gui;  // ← DODANE
    delete weaponSprite;

    for (Enemy* e : enemies) {
        delete e;
    }
    enemies.clear();
}

void Game::start(sf::RenderWindow& window) {
    
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 1.0f, 5, 4, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 1.0f, 3, 12, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 1.0f, 6, 20, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 1.0f, 8, 8, 30));
    enemies.push_back(new Enemy("Goblin", 45, 45, 2, 12, 4.0f, 1.1f, 20, 6, 35));
    enemies.push_back(new Enemy("Goblin", 45, 45, 2, 12, 4.0f, 1.1f, 22, 14, 35));
    enemies.push_back(new Enemy("Goblin", 45, 45, 2, 12, 4.0f, 1.1f, 18, 20, 35));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 0.9f, 35, 5, 40));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 0.9f, 40, 12, 40));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 0.9f, 44, 24, 40));
    enemies.push_back(new Enemy("Orc", 150, 150, 5, 25, 4.0f, 0.5f, 15, 15, 150));
    enemies.push_back(new Enemy("Orc", 160, 160, 4, 28, 4.0f, 0.6f, 30, 7, 160));
    enemies.push_back(new Enemy("Orc", 160, 160, 4, 28, 4.0f, 0.6f, 30, 22, 160));
    enemies.push_back(new Enemy("Orc", 200, 200, 6, 30, 4.0f, 0.4f, 42, 15, 200));
    

    map.placeCharacter(player->getX(), player->getY(), player);

    for (Enemy* e : enemies) {
        e->attackClockEnemy.restart();
        map.placeCharacter(e->getX(), e->getY(), e);
    }
    player->resetAbility();

    while (running && window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                handleInput(keyPressed->code);
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    handleMouseClick(mousePos, window);
                }
            }
        }

        update(window);
        window.clear(sf::Color::Black);

        gui->drawAll(window, map, player, enemies);
        hud->draw(window, player, specialAbilityClock);

        window.display();
    }
}

void Game::update(sf::RenderWindow& window) {
   

    if (!player->isAlive()) {
        std::cout << "you died" << std::endl;
        running = false;
        return;
    }

    if (specialAbilityClock.getElapsedTime().asSeconds() >= 30.0f) {
        if (player->isAbilityUsed()) { 
            player->resetAbility(); 
        }
    }

    //sprawdzenie czy wsyscy zyja
    bool allDead = true;
    for (Enemy* e : enemies) {
        if (e->isAlive()) {
            allDead = false;
            break;
        }
    }
    if (allDead) {
        std::cout << "koniec gry. zwyciestwo" << std::endl;
        running = false;
        return;
    }

    if (running) {

    // ruch i atak przeciwników     
        for (Enemy* e : enemies) {
            if (!e->isAlive()) continue;

           
            if (e->enemyMoveClock.getElapsedTime().asSeconds() >= 0.7f) {
            e->randomMove(map);
            e->enemyMoveClock.restart();
            }

            int distance = std::abs(e->getX() - player->getX()) + std::abs(e->getY() - player->getY());
            if (distance <= e->getAttackRange()) {
                if (e->attackClockEnemy.getElapsedTime().asSeconds() >=e->getAttackSpeed()) {
                    int chance = std::rand() % 3; 
                    if (chance < 2) { 
                        player->takeDamage(e->getAttackDamage());
                    } 
                    e->attackClockEnemy.restart();
                }
            }
        }


//atak maga 

    static sf::Clock frameClock;
    float dt = frameClock.restart().asSeconds();

        if (isfireballflying) {
            fireball.move(fireballVelocity * dt);

            sf::Vector2f playerCenter((player->getX() * 32.f) + 16.f, (player->getY() * 32.f) + 16.f);
            sf::Vector2f distVec = fireball.getPosition() - playerCenter;
            float dist = std::sqrt(distVec.x * distVec.x + distVec.y * distVec.y);

            if (dist > (player->getAttackRange() * 32.f)) {
                isfireballflying = false;
            }

            sf::Vector2f fireballPos = fireball.getPosition();
            for (Enemy* e : enemies) {
                if (!e->isAlive()) continue;

                float enemyPx = e->getX() * 32.f;
                float enemyPy = e->getY() * 32.f;
if (fireballPos.x >= enemyPx && fireballPos.x <= enemyPx + 32.f && fireballPos.y >= enemyPy && fireballPos.y <= enemyPy + 32.f) {
    
    e->takeDamage(player->getAttackDamage());
    isfireballflying = false;

    if (!e->isAlive()) {
        player->gainExp(e->getExpReward());

        map.removeCharacter(e->getX(), e->getY());
    }

    break;
}
            }
        }

        if (player->isAlive() && weaponSprite != nullptr) {
            sf::Vector2f playerCenter((player->getX() * 32.f) + 16.f, (player->getY() * 32.f) + 16.f);
            weaponSprite->setPosition(playerCenter);

            if (attackAnimationClock.getElapsedTime().asSeconds() >= 0.2f) {
                isAttacking = false;
                weaponSprite->setRotation(sf::degrees(0.f));
            }
        }
    }
}

//obsluga klawiatury

void Game::handleInput(sf::Keyboard::Key key){
    if(player->isAlive() && running){

    // ruch gracza WASD
        if (playerMoveClock.getElapsedTime().asSeconds() >= 0.15f) {
            int nextX = player->getX();
            int nextY = player->getY();

            if (key == sf::Keyboard::Key::W) nextY--;
            if (key == sf::Keyboard::Key::S) nextY++;
            if (key == sf::Keyboard::Key::A) nextX--;
            if (key == sf::Keyboard::Key::D) nextX++;

            if (nextX != player->getX() || nextY != player->getY()) {
                if (map.getTile(nextX, nextY)->canEnter()) {
                    map.moveCharacter(player->getX(), player->getY(), nextX, nextY);
                    player->setX(nextX);
                    player->setY(nextY);
                }
                playerMoveClock.restart();
            }
        }

// dziwnie zreczy sie tu dzieja do poprawy 

    if (key == sf::Keyboard::Key::E) {
    if (!player->isAbilityUsed()) {
    
        player->specialAbility(enemies,map); 
        specialAbilityClock.restart(); 
        
            }
        }
    }
}

void Game::handleMouseClick(sf::Vector2i mousePos, sf::RenderWindow& window) {
    if (!player->isAlive() || !running) {
        return;
    }

    sf::Vector2f playerCenter((player->getX() * 32.f) + 16.f, (player->getY() * 32.f) + 16.f);

    // === LOGIKA MAGA ===
    if (player->getName() == "Mage") {
        if (attackSpeedClock.getElapsedTime().asSeconds() >= player->getAttackSpeed()) {
            sf::Vector2f targetPos = window.mapPixelToCoords(mousePos);
            sf::Vector2f dir = targetPos - playerCenter;
            float distInPixels = std::sqrt(dir.x * dir.x + dir.y * dir.y);

            isfireballflying = true;
            gui->setupFireball(fireball, playerCenter);

            if (distInPixels > 0.f) {
                fireballVelocity = (dir / distInPixels) * 400.f;
            } else {
                fireballVelocity = sf::Vector2f(400.f, 0.f);
            }

            attackSpeedClock.restart();
        }
    }

    // === LOGIKA WOJOWNIKA / ŁOTRA ===
    else {
        if (attackSpeedClock.getElapsedTime().asSeconds() >= player->getAttackSpeed()) {
            sf::Vector2f targetPos = window.mapPixelToCoords(mousePos);
            sf::Vector2f dir = targetPos - playerCenter;

            float degrees = std::atan2(dir.y, dir.x) * 180.f / 3.1415f;
            if (weaponSprite != nullptr) {
                weaponSprite->setRotation(sf::degrees(degrees + 90.f));
            }

            isAttacking = true;
            attackAnimationClock.restart();

            for (Enemy* e : enemies) {
                if (!e->isAlive()) continue;

                int tileDistance = std::abs(player->getX() - e->getX())
                                 + std::abs(player->getY() - e->getY());

                if (tileDistance <= player->getAttackRange()) {
                    e->takeDamage(player->getAttackDamage());
                   

                    // Jesli wrog zginal - daj expa i usun z mapy
                    if (!e->isAlive()) {
                        player->gainExp(e->getExpReward());
                        
                        map.removeCharacter(e->getX(), e->getY());
                    }
                }
            }

            attackSpeedClock.restart();
        }
    }
}