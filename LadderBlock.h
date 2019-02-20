#pragma once

#include "ABlock.h"

class LadderBlock :
    public ABlock
{
public:
    LadderBlock(const RessourcesManager&, const char&, const sf::Vector2f&);
    ~LadderBlock() {};
};

