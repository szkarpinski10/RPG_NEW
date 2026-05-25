#pragma once

class Character;

class Tile{
private:
    char symbol;
    bool walkable;
    Character* occupant;

public:
     Tile(char s = '.', bool w = true)
        : symbol(s), walkable(w), occupant(nullptr) {}


    char getSymbol() const {return symbol;}
    bool isWalkable() const {return walkable;}
    bool hasOccupant() const {return occupant != nullptr;}
    bool canEnter() const {return walkable && occupant == nullptr;}

    Character* getOccupant() const {return occupant;}
    void setOccupant(Character* character) {occupant = character;}
    void clearOccupant() {occupant = nullptr;}


};