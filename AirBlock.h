#pragma once

#include "ABlock.h"

class AirBlock :
    public ABlock
{
public:
    AirBlock(const RessourcesManager&, const char&, const sf::Vector2f&);
    ~AirBlock();
};
