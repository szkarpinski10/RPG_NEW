#include "HUD.h"
#include "Player.h"
#include <string>
#include <iostream>

HUD::HUD(sf::Font& font){
    hudText =new sf::Text(font);
    hudText ->setCharacterSize(12);
    hudText->setFillColor(sf::Color::Black);

}

HUD::~HUD(){
    delete hudText;
}

void HUD::draw(sf::RenderWindow& window, const Player* player, sf::Clock& specialAbilityClock){
    //Pasek wyświetlający hp

    sf::RectangleShape hpBar({hudWidth,hudHeight});
    hpBar.setFillColor(sf::Color(200,30,30));
    hpBar.setPosition({hudX,hudY});
    window.draw(hpBar);

    hudText->setString("HP:"+ std:: to_string(player->getHealth()) +" / "+std::to_string(player->getMaxHealth()));
    hudText->setPosition({hudX +10.f, hudY+4.f});
    window.draw(*hudText);

    sf::RectangleShape barExp({hudWidth,hudHeight});
    barExp.setFillColor(sf::Color(125,255,0));
    barExp.setPosition({hudX,hudY+40.f});
    window.draw(barExp);

    hudText->setString("EXP:"+ std:: to_string(player->getExp()) +" / "+std::to_string(player->getExpToNextLevel()));
    hudText->setPosition({hudX +10.f, hudY+44.f});
    window.draw(*hudText);

    
}