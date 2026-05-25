#include <iostream>
#include <cmath>
#include "Game.h"
#include "Player.h"
#include "HUD.h"
#include "Enemy.h"

Game::Game(Player* p){
    player=p;
    running=true;
    weaponSprite=nullptr;
   

    if (!font.openFromFile("PressStart2P-Regular.ttf")) {
        std::cout << "blad czcionki\n";
    }
    hud = new HUD(font);

    if(!warriorWeaponImg.loadFromFile("LongSword-1.png")||
        !rogueWeaponImg.loadFromFile("SmallSword.png") ||
        !mageWeaponImg.loadFromFile("Staff4.png")) {
        std::cout << "blad grafik broni\n";
    }

    if(player->getName()=="Warrior"){
        weaponSprite=new sf::Sprite(warriorWeaponImg);
    }
    else if(player->getName()=="Mage"){
        weaponSprite=new sf::Sprite(mageWeaponImg);
    }
    else if(player->getName()=="Rogue"){
        weaponSprite=new sf::Sprite(rogueWeaponImg);
    }

    if(weaponSprite!=nullptr){
        sf::FloatRect wymiaryBroni=weaponSprite->getLocalBounds();
        weaponSprite->setOrigin({wymiaryBroni.size.x/2.f,wymiaryBroni.size.y});
    }

}

Game::~Game(){
    delete player;
    delete hud;
    delete weaponSprite;

    for (Enemy* e : enemies) {
        delete e;
    }
    enemies.clear();
}


void Game::start(sf::RenderWindow& window){
    
    // Dodanie przeciwników i gracza
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 8, 4.0f, 1.0f, 5, 4, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 8, 4.0f, 1.0f, 4, 8, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 8, 4.0f, 1.0f, 9, 5, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 8, 4.0f, 1.0f, 10, 6, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 8, 4.0f, 1.0f, 9,  7, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 8, 4.0f, 1.0f, 3,  12, 30));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 8, 4.0f, 1.0f, 6,  14, 30));
    enemies.push_back(new Enemy("Goblin", 45, 45, 2, 10, 4.0f, 1.1f, 13, 8,  35));
    enemies.push_back(new Enemy("Goblin", 45, 45, 2, 10, 4.0f, 1.1f, 14, 11, 35));
    enemies.push_back(new Enemy("Goblin", 40, 40, 1, 12, 4.0f, 0.9f, 16, 6,  40));
    enemies.push_back(new Enemy("Orc", 150, 150, 5, 25, 4.0f, 0.5f, 12, 10, 150));
    enemies.push_back(new Enemy("Orc", 160, 160, 4, 28, 4.0f, 0.6f, 18, 13, 160));
    enemies.push_back(new Enemy("Orc", 200, 200, 6, 30, 4.0f, 0.4f, 19, 14, 200));

    map.placeCharacter(player->getX(), player->getY(), player);

    //reset ataku przeciwników i postawienie ich na mapie
    for (Enemy* e : enemies) {
        e->attackClockEnemy.restart();
        map.placeCharacter(e->getX(), e->getY(), e);
    }
    player->resetAbility();

    
    while(running && window.isOpen()){
        while (const std::optional event = window.pollEvent()) {
            //zamkniecie okna jak sie wcisnie X
            if (event->is<sf::Event::Closed>()) {
                
                window.close();
            }
            //odczytywanie znaków z klawiatury
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                handleInput(keyPressed->code);
            }
            //odczytywanie jak sie kliknie myszke LPM i pozycje
            else if(const auto* mousePressed=event->getIf<sf::Event::MouseButtonPressed>()){
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    handleMouseClick(mousePos,window);
                 }
            }
        }
       
        update(window);
        window.clear(sf::Color::Black);
        render(window);
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

           
            if (enemyMoveClock.getElapsedTime().asSeconds() >= 0.7f) {
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

                if (fireballPos.x >= enemyPx && fireballPos.x <= enemyPx + 32.f &&
                    fireballPos.y >= enemyPy && fireballPos.y <= enemyPy + 32.f) {
                    
                    e->takeDamage(player->getAttackDamage());
                    isfireballflying = false;
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

    //    if (key == sf::Keyboard::Key::E) {
    //         if (!player->isAbilityUsed()) {
    //             // Szukamy najbliższego żywego wroga
    //             Enemy* targetEnemy = nullptr;
    //             for (Enemy* e : enemies) {
    //                 if (e->isAlive()) {
    //                     targetEnemy = e;
    //                     break; 
    //                 }
    //             }

    //             bool skillExecuted = false;

    //             if (player->getName() == "Mage") {
    //                 // Mag leczy samego siebie – cel nie jest mu potrzebny
    //                 player->specialAbility(*player); 
    //                 std::cout << "Mag uzywa zaklecia uzdrawiania!" << std::endl;
    //                 skillExecuted = true;
    //             } 
    //             else if (targetEnemy != nullptr) {
    //                 // Wojownik i Łotr potrzebują celu
    //                 player->specialAbility(*targetEnemy);
    //                 std::cout << "Uzyto super umiejetnosci na: " << targetEnemy->getName() << "!" << std::endl;
    //                 skillExecuted = true;
    //             } else {
    //                 std::cout << "Brak przeciwnika w poblizu, nie mozesz uzyc tej zdolnosci!" << std::endl;
    //             }

    //             // Jeśli użyliśmy skilla: odpalamy cooldown
    //             if (skillExecuted) {
    //                 player->isAbilityUsed();
    //                 specialAbilityClock.restart(); // Zegar rusza od 0 do 30s
    //             }
    //         } 
    //         else {
    //             float elapsed = specialAbilityClock.getElapsedTime().asSeconds();
    //             float pozostalo = 30.0f - elapsed;
    //             std::cout << "Zdolnosc sie odnawia! Poczekaj jeszcze: " << std::round(pozostalo) << "s" << std::endl;
    //         }
    //     }
    }
}

void Game::render(sf::RenderWindow& window){
    map.display(window);
    
    if (player->isAlive()) {
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

        if (isfireballflying) {
            window.draw(fireball);
        }
    }

    // Rysowanie wszystkich żywych wrogów z wektora
  // Rysowanie wszystkich żywych wrogów z wektora razem z literkami
    for (Enemy* e : enemies) {
        if (e->isAlive()) {
            // Obiekt tekstu dla literki potwora
            sf::Text enemyText(font);
            enemyText.setCharacterSize(18); // Wielkość literki (dobrana do kafelka 32x32)

            if (e->getName().rfind("Orc", 0) == 0) { 
                // --- STYL DLA ORKA ---
                sf::RectangleShape orcShape({40.f, 40.f});
                orcShape.setFillColor(sf::Color::Red);
                orcShape.setOutlineThickness(3.f);
                orcShape.setOutlineColor(sf::Color::Black);
                
                sf::Vector2f orcPos((e->getX() * 32.f) - 4.f, (e->getY() * 32.f) - 4.f);
                orcShape.setPosition(orcPos);
                window.draw(orcShape);

                // Literka 'O' dla Orka
                enemyText.setString("O");
                enemyText.setFillColor(sf::Color::White); // Biała literka, żeby odcinała się od czerwieni
                
                // Wyśrodkowanie literki na Orku
                enemyText.setPosition({orcPos.x + 12.f, orcPos.y + 10.f});
                window.draw(enemyText);
            } 
            else {
                // --- STYL DLA GOBLINA ---
                sf::RectangleShape goblinShape({32.f, 32.f});
                goblinShape.setFillColor(sf::Color(0, 200, 0));
                goblinShape.setOutlineThickness(2.f);
                goblinShape.setOutlineColor(sf::Color(138, 43, 226));
                
                sf::Vector2f gobPos(e->getX() * 32.f, e->getY() * 32.f);
                goblinShape.setPosition(gobPos);
                window.draw(goblinShape);

                // Literka 'G' dla Goblina
                enemyText.setString("G");
                enemyText.setFillColor(sf::Color::Black); // Czarna literka, będzie idealnie widoczna na zielonym tle
                
                // Wyśrodkowanie literki na Goblinu
                enemyText.setPosition({gobPos.x + 8.f, gobPos.y + 6.f});
                window.draw(enemyText);
            }
        }
    }

    hud->draw(window, player, specialAbilityClock);
}

void Game::handleMouseClick(sf::Vector2i mousePos, sf::RenderWindow& window) {
    if (!player->isAlive() || !running) return;

    sf::Vector2f playerCenter((player->getX() * 32.f) + 16.f, (player->getY() * 32.f) + 16.f);

    // --- LOGIKA MAGA ---
    if (player->getName() == "Mage") {
        if (attackSpeedClock.getElapsedTime().asSeconds() >= (1.0f / player->getAttackSpeed())) {
            sf::Vector2f targetPos = window.mapPixelToCoords(mousePos);
            sf::Vector2f dir = targetPos - playerCenter;
            float distInPixels = std::sqrt(dir.x * dir.x + dir.y * dir.y);

            isfireballflying = true;
            fireball.setPosition(playerCenter);
            fireball.setRadius(8.f);
            fireball.setFillColor(sf::Color(255, 140, 0)); 
            fireball.setOutlineThickness(2.f);
            fireball.setOutlineColor(sf::Color::Red);

            if (distInPixels > 0.f) {
                fireballVelocity = (dir / distInPixels) * 400.f; 
            } else {
                fireballVelocity = sf::Vector2f(400.f, 0.f);
            }
            
            attackSpeedClock.restart();
        }
    } 
    // --- LOGIKA WOJOWNIKA / ŁOTRA ---
    else {
        if (attackSpeedClock.getElapsedTime().asSeconds() >= (1.0f / player->getAttackSpeed())) {
            sf::Vector2f targetPos = window.mapPixelToCoords(mousePos);
            sf::Vector2f dir = targetPos - playerCenter;

            float degrees = std::atan2(dir.y, dir.x) * 180.f / 3.1415f;
            if (weaponSprite != nullptr) {
                weaponSprite->setRotation(sf::degrees(degrees + 90.f));
            }

            isAttacking = true;
            attackAnimationClock.restart();

            bool trafionoKogos = false;
            for (Enemy* e : enemies) {
                if (!e->isAlive()) continue;

                int tileDistance = std::abs(player->getX() - e->getX()) + std::abs(player->getY() - e->getY());
                if (tileDistance <= player->getAttackRange()) {
                    e->takeDamage(player->getAttackDamage());
                    std::cout << "Trafiono " << e->getName() << "! HP wroga: " << e->getHealth() << std::endl;
                    trafionoKogos = true;
                }
            }

            if (!trafionoKogos) {
                std::cout << "Machnales mieczem w powietrze (Pudlo)!" << std::endl;
            }

            attackSpeedClock.restart(); 
        }
    }
}