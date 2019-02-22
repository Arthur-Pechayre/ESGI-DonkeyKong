#pragma once

#include "ABlock.h"
#include "AEntity.h"

class Player : public AEntity
{
public:
    static const float  SPEED;
    static const float  JUMP_CD;
    static const int    JUMP_FORCE;
    static const float  MAX_X_SPEED;
    static const float  MAX_Y_SPEED;
    static const float  DAMAGE_CD;

    sf::Time            jumpCooldown;
    sf::Time            damageCooldown;

public:
    Player(const RessourcesManager&);
    ~Player();
    sf::Vector2i getGridPosition() const;
};
