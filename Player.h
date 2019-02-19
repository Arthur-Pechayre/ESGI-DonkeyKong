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
    static const int    FACING_RIGHT;
    static const int    FACING_LEFT;

    int                 facing;
    bool                facingChanged;
    sf::Time            jumpCooldown;

    sf::Vector2f        velocity;

public:
    Player(const RessourcesManager&);
    ~Player();
    void draw(sf::RenderWindow&);
    sf::Vector2i getGridPosition() const;
};
