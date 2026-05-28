#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class HUD{
private:
    sf::Text* hudText;
    sf::Font* fontRef; 
    const float hudX=1250.f;
    const float hudY=30.f;
    const float hudWidth=200.f;
    const float hudHeight=25.f;

    float statsX = 10.f;
    float statsY = 750.f;
    float statsWidth = 250.f;
    float statsHeight = 110.f;

public:
    HUD(sf::Font& font);
    ~HUD();

    void draw(sf::RenderWindow& window, const Player* player, sf::Clock& specialAblilityClock);
    void drawStatsPanel(sf::RenderWindow& window, const Player* player);


};