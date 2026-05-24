#pragma once
#include "Character.h"

class Player: public Character{
protected:
    int level;
    int exp;
    int expToNextLevel;
    bool abilityUsed;
public:
    Player(std::string n, int h, int mH, int ar, int aD, float aR, float aS, int posX, int posY)
    : Character(n,h,mH,ar,aD,aR,aS,posX,posY){
        level=1;
        exp=0;
        expToNextLevel=100;
        abilityUsed=false;
    }

    int getLevel() const {return level;}
    int getExp() const {return exp;}
    int getExpToNextLevel() const {return expToNextLevel;}
    bool isAbilityUsed() const { return abilityUsed;}
    
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }

    void gainExp(int amount){
        exp+=amount;
        if(exp>=expToNextLevel){
            levelUp();
        }
    }

    void levelUp(){
        level++;
        exp=0;
        expToNextLevel+=200;
        maxHealth+=20;
        health=maxHealth;
        attackDamage+=5;
        
    }

    void resetAbility(){
        abilityUsed=false;
    }

    virtual void specialAbility(Character& target)=0;


};