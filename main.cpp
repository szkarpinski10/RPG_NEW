#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Player.h"   
#include "Warrior.h"
#include "Mage.h"
#include "Rogue.h"
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1600, 900)), "RPG Gra");

    Menu menu;
    int choice = menu.showMenu(window);

    if (choice == 1 && window.isOpen()) {
        int classChoice = menu.chooseClass(window);

        Player* player = nullptr;
        if (classChoice == 1) {
            player = new Warrior();
        } else if (classChoice == 2) {
            player = new Mage();
        } else {
            player = new Rogue();
        }

        if (window.isOpen()) {
            Game game(player);
            game.start(window);
        }

        delete player;  // ← main usuwa, bo main tworzył
        player = nullptr;
    }

    return 0;
}