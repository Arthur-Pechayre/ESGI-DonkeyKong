#pragma once

#include "ABlock.h"
#include "ASolidBlock.h"
#include "RessourcesManager.h"
#include <random>

class StonebrickBlock : public ABlock, virtual public ASolidBlock
{

private:
    RessourcesManager::Tids randomizeTexture();

public:
    StonebrickBlock(const RessourcesManager&, const char&, const sf::Vector2f&);
    ~StonebrickBlock();
};
