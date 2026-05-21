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

int main(){
sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1600, 900)), "RPG Gra");

    Menu menu;
    
    int choice = menu.showMenu(window);

    if (choice == 1 && window.isOpen()) {
        
        // 3. Przekazujemy to samo okno do funkcji chooseClass
        int classChoice = menu.chooseClass(window);

        Player* player = nullptr;
        if (classChoice == 1) {
            player = new Warrior();
        } else if (classChoice == 2) {
            player = new Mage();
        } else {
            player = new Rogue();
        }

        // 4. Odpalamy Twoją dotychczasową grę
        if (window.isOpen()) {
            Game game(player);
            game.start(); 
        }

        delete player;
    }

    return 0;
}