#include <iostream>
#include "Menu.h"


Menu::Menu() {}

Menu::~Menu() {}

int Menu::showMenu(){
    int choice=0;
    while(choice<1||choice>2){
        std::cout << "------------------------"<<std::endl;
        std::cout<<"1. Start game"<<std::endl;
        std::cout<<"2. Quit"<<std::endl;
        std::cout << "------------------------"<<std::endl;
        std::cout<<"Choice: ";
        std::cin>>choice;
    }
    return choice;
}

int Menu::chooseClass(){
    int choice=0;
     while(choice<1||choice>3){
        std::cout<< "------------------------"<<std::endl;
        std::cout<<"Choose your class: "<<std::endl;
        std::cout<<"1. Warrior"<<std::endl;
        std::cout<<"2. Mage"<<std::endl;
        std::cout<<"3. Rogue"<<std::endl;
        std::cout<< "------------------------"<<std::endl;
        std::cout<<"Choice: ";
        std::cin>>choice;
    }
    return choice;
}
//sfml
int Menu::showMenuSfml() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "RGP");

    // 1. Deklarujemy czcionkę TYLKO RAZ
    sf::Font font;

    // 2. Klasyczna metoda ładowania (zwykłe loadFromFile)
    if (!font.openFromFile("PressStart2P-Regular.ttf")) {
        std::cout << "Blad ladowania czcionki!" << std::endl;
        return 2; 
    }

    // 3. Tworzymy napis "Start Game" (czcionka, tekst, rozmiar w pikselach)
    sf::Text startText(font, "1. Start Game", 32); 
    startText.setFillColor(sf::Color::White);
    startText.setPosition({250.f, 200.f});

    // 4. Tworzymy napis "Quit"
    sf::Text quitText(font, "2. Quit", 32);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition({250.f, 300.f});

    // Główna pętla okna Menu
    while (window.isOpen()) {
        // Obsługa zdarzeń (np. zamknięcie okna krzyżykiem)
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return 2; // Zwracamy wyjście z gry
            }
        }

        // POBIERANIE POZYCJI MYSZKI WZGLĘDEM OKNA
        sf::Vector2i mousePosI = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos(static_cast<float>(mousePosI.x), static_cast<float>(mousePosI.y));

        // INTERAKCJA Z NAPISAMI:
        
        // Czy myszka jest nad "Start Game"?
        if (startText.getGlobalBounds().contains(mousePos)) {
            startText.setFillColor(sf::Color::Yellow); // Podświetlamy na żółto
            
            // Jeśli klikniemy lewy przycisk myszy
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                window.close(); // Zamykamy okienko menu
                return 1;       // Zwracamy 1, żeby gra ruszyła dalej!
            }
        } else {
            startText.setFillColor(sf::Color::White); // Jeśli myszka uciekła, wraca biały
        }

        // Czy myszka jest nad "Quit"?
        if (quitText.getGlobalBounds().contains(mousePos)) {
            quitText.setFillColor(sf::Color::Red); // Podświetlamy na czerwono
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                window.close();
                return 2; // Zwracamy 2 (wyjście z gry)
            }
        } else {
            quitText.setFillColor(sf::Color::White);
        }

        // RYSOWANIE MENU NA EKRANIE
        window.clear(sf::Color::Black); // Czyszczenie na czarno
        
        window.draw(startText);          // Rysujemy napis start
        window.draw(quitText);           // Rysujemy napis quit
        
        window.display();               // Wyświetlamy wszystko
    }

    return 2;
}