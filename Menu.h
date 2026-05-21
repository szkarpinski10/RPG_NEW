#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Menu{
public:
    Menu();
    ~Menu();

    int showMenu();
    int chooseClass();

    //smfl
    int showMenuSfml();
};
