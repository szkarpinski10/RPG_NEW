#include "HUD.h"
#include "Player.h"
#include <string>
#include <iostream>

HUD::HUD(sf::Font& font){
    hudText =new sf::Text(font);
    hudText ->setCharacterSize(12);
    hudText->setFillColor(sf::Color::Black);
    fontRef = &font;

}

HUD::~HUD(){
    delete hudText;
}

void HUD::draw(sf::RenderWindow& window, const Player* player, sf::Clock& specialAbilityClock){

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

   sf::RectangleShape specialAbilityBar({hudWidth,hudHeight});
   specialAbilityBar.setPosition({hudX,hudY+80.f});

  if (!player->isAbilityUsed()) {
    specialAbilityBar.setFillColor(sf::Color(0, 120, 255));
    window.draw(specialAbilityBar); 
    hudText->setString("ABILITY READY");
    hudText->setPosition({hudX + 10.f, hudY + 84.f});
    window.draw(*hudText);
}
   else{
    float elapsedAbilityTime = specialAbilityClock.getElapsedTime().asSeconds();
    float timeLeft = 30.0f - elapsedAbilityTime; 
        if (timeLeft < 0) timeLeft = 0;

    specialAbilityBar.setFillColor(sf::Color(70, 70, 70)); // Szary
    window.draw(specialAbilityBar);
    char timeStr[10];
        snprintf(timeStr, sizeof(timeStr), "%.1fs", timeLeft);

        hudText->setString("COOLDOWN: " + std::string(timeStr));
        hudText->setPosition({hudX + 10.f, hudY + 84.f});
        window.draw(*hudText);



   }

    drawStatsPanel(window, player);
}

void HUD::drawStatsPanel(sf::RenderWindow& window, const Player* player) {
    
    sf::RectangleShape panel({statsWidth, statsHeight});
    panel.setFillColor(sf::Color::Black);
    panel.setPosition({statsX, statsY});
    window.draw(panel);

    // Tekst
    sf::Text statsText(*fontRef);
    statsText.setCharacterSize(10);
    statsText.setFillColor(sf::Color::White);

    float lineHeight = 16.f;
    float startY = statsY + 10.f;

    statsText.setString("Class: " + player->getName());
    statsText.setPosition({statsX + 10.f, startY});
    window.draw(statsText);

    statsText.setString("LVL: " + std::to_string(player->getLevel()));
    statsText.setPosition({statsX + 10.f, startY + lineHeight});
    window.draw(statsText);

    statsText.setString("AttackDmg: " + std::to_string(player->getAttackDamage()));
    statsText.setPosition({statsX + 10.f, startY + lineHeight * 2});
    window.draw(statsText);

    statsText.setString("Armor: " + std::to_string(player->getArmor()));
    statsText.setPosition({statsX + 10.f, startY + lineHeight * 3});
    window.draw(statsText);

    statsText.setString("Range: " + std::to_string((int)player->getAttackRange()));
    statsText.setPosition({statsX + 10.f, startY + lineHeight * 4});
    window.draw(statsText);

    char speedStr[10];
    snprintf(speedStr, sizeof(speedStr), "%.1fs", player->getAttackSpeed());
    statsText.setString("AttackSpeed: " + std::string(speedStr));
    statsText.setPosition({statsX + 10.f, startY + lineHeight * 5});
    window.draw(statsText);
}