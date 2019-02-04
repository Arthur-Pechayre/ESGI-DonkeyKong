#pragma once
#include "Entity.h"

class Player :
    public Entity
{
public:
    Player();
    ~Player();
    sf::CircleShape _feetHitBox;
    sf::FloatRect       _hitBox;
};
