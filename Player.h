#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    ~Player();
    sf::CircleShape _feetHitBox;
    sf::FloatRect       _hitBox;

public:
    bool grounded(std::vector<std::shared_ptr<Entity>> blocks);
    void updateHitboxes();
};
