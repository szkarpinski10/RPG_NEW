#pragma once
#include "Tile.h"

class Map{
private:
    static const int WIDTH=25;
    static const int HEIGHT=15;
    Tile tiles[HEIGHT][WIDTH];

public:
    Map();

    int getWidth() const {return WIDTH;}
    int getHeight() const {return HEIGHT;}

    void generate();
    void display() const;
    bool isInside(int x, int y) const;
    bool checkIfWalkable(int x, int y) const;
    Tile* getTile(int x, int y);

    bool placeCharacter(int x, int y, Character* character);
    bool removeCharacter(int x, int y);
    bool moveCharacter(int fromX, int fromY, int toX, int toY);

};