#pragma once
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include "HUD.h"
#include <vector>

class Game {
private:
    Map map;
    Player* player;
    //Enemy* enemy;
    bool running;
    HUD* hud;
    std::vector<Enemy*> enemies;
    bool abilityReady;

    sf::CircleShape fireball;
    bool isfireballflying = false;
    sf::Vector2f fireballVelocity;
   

    //timery i czcionka
    sf::Font font;
    sf::Clock enemyMoveClock;
    sf::Clock playerMoveClock;
    sf::Clock specialAbilityClock;
    sf::Clock attackSpeedClock;  
    sf::Clock attackAnimationClock;    
   
    
    bool isAttacking=false;    

    //bronie 

    sf::Texture warriorWeaponImg;
    sf::Texture rogueWeaponImg;
    sf::Texture mageWeaponImg;
    sf::Sprite* weaponSprite;

    

    void handleInput(sf::Keyboard::Key key);
    void handleMouseClick(sf::Vector2i mousePos,sf::RenderWindow& window); 
    void render(sf::RenderWindow& window);

public:
    Game(Player* p);
    ~Game();

    void start(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    bool isRunning() const{
        return running;
    }
};