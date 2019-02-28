#pragma once

#include "ABlock.h"
#include "AEntity.h"
#include "BlockGenerator.hpp"

class Map {
    typedef std::vector<std::vector<ABlock_>> ABlockMap;
    typedef	void(Map::* EntityPositionInitializer) (ABlock_);

public:
    ABlockMap                                               tileMap;
    sf::Vector2u                                            size;
    sf::Vector2f                                            initPlayerPos;
    std::vector<sf::Vector2f>                               initDiamondsPos;
    std::vector<std::shared_ptr<PufferfishSpawnerBlock>>    spawners;
    
private:
    const RessourcesManager*                    ressourcesManager;
    std::map<char, EntityPositionInitializer>   initializersMap;
    void                                        initEntitiesPositions(const char&, ABlock_);
    void                                        initPlayerOnBlock(ABlock_);
    void                                        initDiamondOnBlock(ABlock_);
    void                                        registerSpawner(ABlock_);

public:
    Map(const RessourcesManager&);
    ~Map() {};
    void loadMap(const std::string&);
    void draw(sf::RenderWindow&);
};
