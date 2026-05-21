#include "Menu.h"
#include "Game.h"
#include "Warrior.h"
#include "Mage.h"
#include "Rogue.h"

#include <ctime>

int main() {
    
    srand(time(0));
    Menu menu;
    int choice = menu.showMenuSfml();

    if (choice == 1) {
        
        int classChoice = menu.chooseClass();

        Player* player;
        if (classChoice == 1) {
            player = new Warrior();
        } else if (classChoice == 2) {
            player = new Mage();
        } else {
            player = new Rogue();
        }

        Game game(player);
        game.start();
    }
   

    return 0;
}