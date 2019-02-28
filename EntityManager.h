#pragma once

#include "RessourcesManager.h"
#include "AEntity.h"
#include "ABlock.h"
#include "Map.h"
#include "DiamondEntity.h"
#include "PufferfishEntity.h"
#include "PufferfishSpawnerBlock.h"

class EntityManager
{
public:
    typedef std::map<int, DiamondEntity*>           DiamondEntityMapEntry;
    typedef std::map<int, DiamondEntityMapEntry>    DiamondEntityMap;

    std::vector<std::shared_ptr<PufferfishSpawnerBlock>>    spawners;
    std::vector<PufferfishEntity*>                          pufferfishs;

private:
    const RessourcesManager*                ressourcesManager;
    const Map*                              map;
    DiamondEntityMap                        diamondsMap;
    unsigned int                            diamondsCount;

public:
    EntityManager(const RessourcesManager&, const Map&);
    ~EntityManager() {};
    void                    draw(sf::RenderWindow&);
    std::vector<AEntity*>   getEntitiesAt(int y, int x) const;
    void                    initDiamonds(const std::vector<sf::Vector2f>&);
    int                     updateDiamonds(std::vector<DiamondEntity*>);
    void                    updatePufferfishs(const sf::Time&);
    void                    spawnPufferfishs(const sf::Time&);
    void                    updateFacing(AEntity&);
    void                    applyFriction(AEntity&);
    void                    applyGravity(AEntity&);
    bool                    isGrounded(AEntity &);
    ABlock_shrdp            isCollidingInBlock(AEntity &);
};

