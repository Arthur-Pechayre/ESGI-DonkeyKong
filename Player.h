#pragma once

#include "ABlock.h"

class Player : public sf::Sprite
{
public:
    static const float  SPEED;
    static const float  MAX_X_SPEED;
    static const float  MAX_Y_SPEED;
    static const int    FACING_RIGHT;
    static const int    FACING_LEFT;

    int                 facing;
    bool                facingChanged;

public:
    Player(const RessourcesManager&);
    ~Player();
    float width() const;
    float height() const;
    float top() const;
    float bot() const;
    float left() const;
    float right() const;
};
