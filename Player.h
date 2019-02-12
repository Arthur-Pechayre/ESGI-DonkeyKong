#pragma once

#include "ABlock.h"

class Player : public sf::Sprite
{
public:
    static const float MAX_X_SPEED;
    static const float MAX_Y_SPEED;
    static const int FACING_RIGHT;
    static const int FACING_LEFT;

    sf::RectangleShape  _feetHitBox;
    sf::FloatRect       _hitBox;
    int                 _facing;
    bool                _facingChanged;
public:
    Player(const RessourcesManager& manager);
    ~Player();
    void updateHitboxes();
};
