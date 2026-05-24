#pragma once
#include "Player.h"
class Mage : public Player{
public:



    Mage(): Player ("Mage",80,80,3,15,10.0f,0.9f,1,1){}

    void specialAbility(Character& target) override{
        if(!abilityUsed){
            health=maxHealth;
            abilityUsed=true;
        }
    }
    
  

};