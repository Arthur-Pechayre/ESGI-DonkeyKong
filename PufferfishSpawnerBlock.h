#pragma once

#include "Const.h"
#include "ABlock.h"
#include "ASolidBlock.h"
#include "PufferfishEntity.h"
#include <random>

class PufferfishSpawnerBlock :
    public ABlock,
    virtual public ASolidBlock
{
public:
    static const float  SPAWN_RATE;
    const static int    FACING_RIGHT = 1;
    const static int    FACING_LEFT = -1;
    int facing;

private:
    sf::Time  spawnCooldown;

public:
    PufferfishSpawnerBlock(const RessourcesManager&, const char&, const sf::Vector2f&);
    ~PufferfishSpawnerBlock() {};
    void    setPosition(float, float);
    void    setPosition(const sf::Vector2f&);
    bool    spawn(const sf::Time&);
};
