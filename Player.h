#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
    static const float MAX_X_SPEED;
    static const float MAX_Y_SPEED;
    static const int FACING_RIGHT;
    static const int FACING_LEFT;

    sf::CircleShape     _feetHitBox;
    sf::FloatRect       _hitBox;
    int                 _facing;
    bool                _facingChanged;
public:
    Player();
    ~Player();
    bool grounded(std::vector<std::shared_ptr<Entity>> blocks);
    void updateHitboxes();
};
