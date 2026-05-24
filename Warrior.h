#pragma once
#include "Player.h"
class Warrior : public Player{
public:



    Warrior(): Player ("Warrior",120,120,8,20,5.0f,1.2f,1,1){}

    void specialAbility(Character& target) override{
        if(!abilityUsed){
            target.takeDamage(attackDamage*3);
            abilityUsed=true;
        }
    }
    
  

};