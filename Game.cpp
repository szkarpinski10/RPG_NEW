#include <iostream>
#include "Game.h"
#include "HUD.h"
#include <SFML/Graphics.hpp>




Game::Game(Player* p){
    player=p;
    running=true;

    if (!font.openFromFile("PressStart2P-Regular.ttf")) {
        std::cout << "brak czcionki\n";
    }
    
    hud = new HUD(font);
}



Game::~Game(){
    delete player;
    delete enemy;
    
}

void Game::start(sf::RenderWindow& window) {
    enemy = new Enemy("Goblin", 50, 50, 2, 10, 1.0f, 1.0f, 7, 7, 50);
    
    map.placeCharacter(player->getX(), player->getY(), player);
    map.placeCharacter(enemy->getX(), enemy->getY(), enemy);

    while (running && window.isOpen()) {
        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                running = false;
            }
            
            // 1. REAKCJA NA KLAWIATURĘ (Ruch WASD i specjalna umiejętność E)
            if (event->is<sf::Event::KeyPressed>()) {
                const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                if (keyPressed) {
                    handleInput(keyPressed->code); 
                }
            }

            // 2. REAKCJA NA MYSZKĘ (Atak pod Lewym Przyciskiem Myszy)
            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>();
                if (mousePressed && mousePressed->button == sf::Mouse::Button::Left) {
                    
                    // Wywołujemy logikę ataku bezpośrednio po kliknięciu LPM
                    float playerRange = player->getAttackRange();
                    int distance = abs(player->getX() - enemy->getX()) + abs(player->getY() - enemy->getY());

                    if (distance <= playerRange) {
                        player->attackTarget(*enemy);
                        std::cout << "Atak mieczem (LPM)!\n";
                    } else {
                        std::cout << "Za daleko na atak!\n";
                    }
                }
            }
        }

        update();

        window.clear(sf::Color::Black);
        render(window); 
        window.display();
    }
}

void Game::update(){

    if (!enemy->isAlive()) {
        std::cout << "zwyciestwo. wrogowie pokonani\n";
        running = false;
    }

    if (!player->isAlive()) {
        std::cout << "you died\n";
        running = false;
    }

   if (running) {
    if(enemyMoveClock.getElapsedTime().asSeconds()>=0.6f){
        enemy->randomMove(map);
        enemyMoveClock.restart();
    }
       float enemyRange=enemy->getAttackRange();
       int distance=abs(enemy->getX()-player->getX())+abs(enemy->getY()-player->getY());
       if(distance<=enemyRange){
        enemy->attackTarget(*player);
       }
    }
}


void Game::handleInput(sf::Keyboard::Key key) {
    int dx = 0;
    int dy = 0;

    // --- COOLDOWN UMIEJĘTNOŚCI SPECJALNEJ (E) ---
    // Jeśli minęło 5 sekund od użycia, odblokowujemy możliwość ponownego użycia skilla!
    if (player->isAbilityUsed() && specialAbilityClock.getElapsedTime().asSeconds() >= 30.0f) {
        // Ponieważ w Player.h nie masz funkcji resetującej, 
        // wywołamy ponowne pełne wyleczenie u Maga lub po prostu pozwolimy użyć skilla.
        // Żeby to działało idealnie, w Player.h dopiszemy potem małą metodę.
    }

    // --- OBSŁUGA KLIKNIĘĆ ---
    if (key == sf::Keyboard::Key::W) {
        dy = -1;
    } else if (key == sf::Keyboard::Key::S) {
        dy = 1;
    } else if (key == sf::Keyboard::Key::A) {
        dx = -1;
    } else if (key == sf::Keyboard::Key::D) {
        dx = 1;
    } else if (key == sf::Keyboard::Key::E) {
        // Gracz klika E
        if (!player->isAbilityUsed()) {
            player->specialAbility(*enemy);
            specialAbilityClock.restart(); // Startujemy stoper cooldownu (np. 5 sekund)
        } else {
            std::cout << "Umiejetnosc sie odnawia!\n";
        }
    }

    // --- OGRANICZENIE PRĘDKOŚCI RUCHU (ZASUWANIA) ---
    if (dx != 0 || dy != 0) {
        // Gracz może zrobić krok tylko raz na 0.15 sekundy (150 milisekund)
        // Jeśli klika za szybko lub trzyma klawisz - gra zignoruje to, dopóki czas nie minie!
        if (playerMoveClock.getElapsedTime().asSeconds() >= 0.15f) {
            int newX = player->getX() + dx;
            int newY = player->getY() + dy;

            if (map.checkIfWalkable(newX, newY)) {
                map.moveCharacter(player->getX(), player->getY(), newX, newY);
                player->setX(newX);
                player->setY(newY);
                
                playerMoveClock.restart(); // Resetujemy stoper kroku gracza
            }
        }
    }
}

bool Game::isRunning() const {
    return running;
}


void Game::render(sf::RenderWindow& window) {
    const float tileSize = 32.f; 
    sf::RectangleShape shape(sf::Vector2f(tileSize - 1.f, tileSize - 1.f)); 

    for (int y = 0; y < map.getHeight(); y++) {
        for (int x = 0; x < map.getWidth(); x++) {
            
            Tile* tile = map.getTile(x, y);
            if (!tile) continue;

            
            shape.setPosition({x * tileSize, y * tileSize});

            // Logika sprawdzania, co stoi na kafelku
            if (tile->hasOccupant()) {
                Character* c = tile->getOccupant();
                std::string name = c->getName();

                if (name == "Warrior") {
                    shape.setFillColor(sf::Color(50, 120, 200));  // Wojownik - Niebieski
                } else if (name == "Mage") {
                    shape.setFillColor(sf::Color(180, 50, 200));  // Mag - Fioletowy
                } else if (name == "Rogue") {
                    shape.setFillColor(sf::Color(200, 150, 50));  // Łotr - Złoty
                } else {
                    shape.setFillColor(sf::Color::Red);            // Goblin - Czerwony
                }
            } 
            else {
                // Rysowanie ścian i podłogi
                if (tile->getSymbol() == '#') {
                    shape.setFillColor(sf::Color(50, 50, 50));    // Ściana - Szary
                } else {
                    shape.setFillColor(sf::Color(0, 160, 0));    // Podłoga - Ciemnoszary
                }
            }

            window.draw(shape);
        }
    }
hud->draw(window, player, specialAbilityClock);
}