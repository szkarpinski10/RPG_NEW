#pragma once
#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;

public:
    Menu();
    ~Menu();

    int showMenu(sf::RenderWindow& window);
    int chooseClass(sf::RenderWindow& window);
};