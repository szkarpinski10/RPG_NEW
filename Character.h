#pragma once
#include <string>

class Character{
protected:
    std::string name;
    int health;
    int maxHealth;
    int armor;

    int attackDamage;
    float attackRange;
    float attackSpeed;

    int x;
    int y;

public:
    Character(std::string n, int h, int mH, int ar, int aD, float aR, float aS, int posX, int posY){
        name=n;
        health=h;
        maxHealth=mH;
        armor=ar;
        attackDamage=aD;
        attackRange=aR;
        attackSpeed=aS;
        x=posX;
        y=posY;
    }
    virtual ~Character() {}
    
    std::string getName() const {return name;}
    int getHealth() const {return health;}
    int getMaxHealth() const {return maxHealth;}
    int getArmor() const {return armor;}

    int getAttackDamage() const {return attackDamage; }
    float getAttackRange() const { return attackRange; }
    float getAttackSpeed() const { return attackSpeed; }
    
    int getX() const { return x; }
    int getY() const { return y; }

    void setPosition(int newX, int newY){
        x=newX;
        y=newY;
    }

// funckje

void takeDamage(int damage){
    int realDamage=damage-armor;
    if (realDamage<=0){
        realDamage=0;
    }

    health=health-realDamage;

    if (health<0){
        health=0;
    }
}

void attackTarget(Character& target){
    target.takeDamage(attackDamage);
}

bool isAlive()const {
        return health>0;
}

 void move(int dx, int dy){
        x+=dx;
        y+=dy;
    }
 void heal(int amount) {
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
        }
    }
};
