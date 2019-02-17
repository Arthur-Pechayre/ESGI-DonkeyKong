#pragma once

#include "RessourcesManager.h"
#include "AEntity.h"
#include "DiamondEntity.h"

class EntityManager
{
    typedef std::map<int, std::map<int, DiamondEntity*>> DiamondEntityMap;

private:
    const RessourcesManager*    ressourcesManager;
    DiamondEntityMap            diamondsMap;
    unsigned int                diamondsCount;

public:
    EntityManager(const RessourcesManager&);
    ~EntityManager() {};
    void initDiamonds(const std::vector<sf::Vector2f>&);
    void draw(sf::RenderWindow&);
};

