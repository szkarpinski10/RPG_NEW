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
