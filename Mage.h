#pragma once
#include "Player.h"
class Mage : public Player{
public:



    Mage(): Player ("Mage",80,80,3,25,3.0f,1.0f,1,1){}

    void specialAbility(Character& target) override{
        if(!abilityUsed){
            health=maxHealth;
            abilityUsed=true;
        }
    }
    
  

};