#include <iostream>
#include <optional>
#include "Menu.h"

Menu::Menu() {
    if (!font.openFromFile("PressStart2P-Regular.ttf")) {
        std::cout << "blad czczionki" << std::endl;
    }
}

Menu::~Menu() {}

int Menu::showMenu(sf::RenderWindow& window) {

    sf::Text startText(font, "1. Start Game", 32);
    startText.setFillColor(sf::Color::White);
    startText.setPosition({600.f, 400.f});

    sf::Text quitText(font, "2. Quit", 32);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition({600.f, 480.f});

    while (window.isOpen()) {
                
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return 2;
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    
    
                    sf::Vector2f clickPos = window.mapPixelToCoords(mousePressed->position);

                    if (startText.getGlobalBounds().contains(clickPos)) {
                        return 1; 
                    }
                    if (quitText.getGlobalBounds().contains(clickPos)) {
                        window.close();
                        return 2; 
                    }
                }
            }
        }

        
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (startText.getGlobalBounds().contains(mousePos)) {
            startText.setFillColor(sf::Color::Yellow);
        } else {
            startText.setFillColor(sf::Color::White);
        }

        if (quitText.getGlobalBounds().contains(mousePos)) {
            quitText.setFillColor(sf::Color::Red);
        } else {
            quitText.setFillColor(sf::Color::White);
        }

        window.clear(sf::Color::Black);
        window.draw(startText);
        window.draw(quitText);
        window.display();
    }
    return 2;
}

int Menu::chooseClass(sf::RenderWindow& window) {

    sf::Text titleText(font, "CHOOSE YOUR CLASS", 42);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition({450.f, 200.f});

    sf::Text warriorText(font, "1. Warrior", 32);
    warriorText.setFillColor(sf::Color::White);
    warriorText.setPosition({650.f, 400.f});

    sf::Text mageText(font, "2. Mage", 32);
    mageText.setFillColor(sf::Color::White);
    mageText.setPosition({650.f, 480.f});

    sf::Text rogueText(font, "3. Rogue", 32);
    rogueText.setFillColor(sf::Color::White);
    rogueText.setPosition({650.f, 560.f});

    while (window.isOpen()) {
        
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return 0;
            }
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2f clickPos = window.mapPixelToCoords(mousePressed->position);

                    if (warriorText.getGlobalBounds().contains(clickPos)) return 1;
                    if (mageText.getGlobalBounds().contains(clickPos)) return 2;
                    if (rogueText.getGlobalBounds().contains(clickPos)) return 3;
                }
            }
        }


        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (warriorText.getGlobalBounds().contains(mousePos)) warriorText.setFillColor(sf::Color::Yellow);
        else warriorText.setFillColor(sf::Color::White);

        if (mageText.getGlobalBounds().contains(mousePos)) mageText.setFillColor(sf::Color::Yellow);
        else mageText.setFillColor(sf::Color::White);

        if (rogueText.getGlobalBounds().contains(mousePos)) rogueText.setFillColor(sf::Color::Yellow);
        else rogueText.setFillColor(sf::Color::White);

        window.clear(sf::Color::Black);
        window.draw(titleText);
        window.draw(warriorText);
        window.draw(mageText);
        window.draw(rogueText);
        window.display();
    }

    return 0;
}