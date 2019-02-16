#pragma once

#include "ABlock.h"
#include "BlockGenerator.hpp"

class Map {
    typedef std::vector<std::vector<ABlock*>> ABlockMap;
public:
    ABlockMap       tileMap;
    sf::Vector2u    size;
    
private:
    const RessourcesManager* ressourcesManager;

public:
    Map(const RessourcesManager&);
    ~Map() {};
    void loadMap();
    void draw(sf::RenderWindow&);
};
