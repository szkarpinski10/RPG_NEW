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

    Character* getOccupant() const {return occupant;}

    bool canEnter() const {return walkable && occupant == nullptr;}

    void setOccupant(Character* character) {occupant = character;}

    void clearOccupant() {occupant = nullptr;}

    void setSymbol(char s) {
        symbol = s;
    }

    void setWalkable(bool w) {
        walkable = w;
    }

};