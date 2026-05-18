#include <iostream>
#include "Map.h"
#include "Character.h"


Map::Map(){
    generate();
}

void Map::generate(){
    for(int y=0;y<HEIGHT;y++){
        for(int x=0;x<WIDTH;x++){
            tiles[y][x]=Tile('.',true);
        }
    }

   for (int x = 0; x < WIDTH; x++) {
        tiles[0][x] = Tile('#', false);
        tiles[HEIGHT-1][x] = Tile('#', false);
    }

    for (int y = 0; y < HEIGHT; y++) {
        tiles[y][0] = Tile('#', false);
        tiles[y][WIDTH-1] = Tile('#', false);
    }
    
}

void Map::display() const {
    for(int y=0;y<HEIGHT;y++){
        for(int x=0;x<WIDTH;x++){
            if(tiles[y][x].hasOccupant()){
            Character* c=tiles[y][x].getOccupant();
            std::string playerName=c->getName();

            if (playerName == "Warrior") {
                    std::cout << 'W';
                } else if (playerName == "Mage") {
                    std::cout << 'M';
                } else if (playerName == "Rogue") {
                    std::cout << 'R';
                } else {
                    std::cout << 'E';
                }
            }
            else {
                std::cout << tiles[y][x].getSymbol();
            }
            


            }
            std::cout<<'\n';
        }
        
}

bool Map::isInside(int x,int y) const {
    return x>=0 &&x<WIDTH&&y>=0&&y<HEIGHT;
}


bool Map::checkIfWalkable(int x,int y) const{
    if(!isInside(x,y)){
        return false;
    }
    return tiles[y][x].canEnter();
}


Tile* Map::getTile(int x, int y) {
    if (!isInside(x, y)) {
        return nullptr;
    }

    return &tiles[y][x];
}

bool Map::placeCharacter(int x, int y, Character* character) {
    if (!isInside(x, y)) {
        return false;
    }

    if (!tiles[y][x].canEnter()) {
        return false;
    }

    tiles[y][x].setOccupant(character);
    character->setPosition(x, y);
    return true;
}

bool Map::removeCharacter(int x, int y) {
    if (!isInside(x, y)) {
        return false;
    }

    if (!tiles[y][x].hasOccupant()) {
        return false;
    }

    tiles[y][x].clearOccupant();
    return true;
}

bool Map::moveCharacter(int fromX, int fromY, int toX, int toY) {
    if (!isInside(fromX, fromY) || !isInside(toX, toY)) {
        return false;
    }

    if (!tiles[fromY][fromX].hasOccupant()) {
        return false;
    }

    if (!tiles[toY][toX].canEnter()) {
        return false;
    }

    Character* character = tiles[fromY][fromX].getOccupant();

    tiles[fromY][fromX].clearOccupant();
    tiles[toY][toX].setOccupant(character);
    character->setPosition(toX, toY);

    return true;
}

