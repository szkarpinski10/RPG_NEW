#pragma once
#include "Player.h"
class Rogue : public Player{
public:



    Rogue(): Player ("Rogue",90,90,4,15,3.0f,2.0f,1,1){}

    void specialAbility(Character& target) override{
        if(!abilityUsed){
           target.takeDamage(attackDamage+20);
            heal(20);
            abilityUsed=true;
        }
    }
     

};