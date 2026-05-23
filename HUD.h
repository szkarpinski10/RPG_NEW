#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class HUD{
private:
    sf::Text* hudText;
    const float hudX=1250.f;
    const float hudY=30.f;
    const float hudWidth=200.f;
    const float hudHeight=25.f;

public:
    HUD(sf::Font& font);
    ~HUD();

    void draw(sf::RenderWindow& window, const Player* player, sf::Clock& specialAblilityClock);



};