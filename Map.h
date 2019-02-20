#pragma once

#include "ABlock.h"
#include "AEntity.h"
#include "BlockGenerator.hpp"


class Map {
    typedef std::vector<std::vector<ABlock*>> ABlockMap;
    typedef	void(Map::* EntityPositionInitializer) (ABlock*);

public:
    ABlockMap                               tileMap;
    sf::Vector2u                            size;
    sf::Vector2f                            initPlayerPos;
    std::vector<sf::Vector2f>               initDiamondsPos;
    std::vector<PufferfishSpawnerBlock*>    spawners;
    
private:
    const RessourcesManager*                    ressourcesManager;
    std::map<char, EntityPositionInitializer>   initializersMap;
    void                                        initEntitiesPositions(const char&, ABlock*);
    void                                        initPlayerOnBlock(ABlock*);
    void                                        initDiamondOnBlock(ABlock*);
    void                                        registerSpawner(ABlock*);

public:
    Map(const RessourcesManager&);
    ~Map() {};
    void loadMap();
    void draw(sf::RenderWindow&);
};
