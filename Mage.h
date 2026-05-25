#pragma once
#include "Player.h"
class Mage : public Player{
public:


// nazwa, zycie, max zycie, armor, attackdamage, attackrange, attackspeed, posx i pos y
    Mage(): Player ("Mage",80,80,3,15,10.0f,0.9f,1,1){}

    void specialAbility(Character& target) override{
        if(!abilityUsed){
            health=maxHealth;
            abilityUsed=true;
        }
    }
    
  

};