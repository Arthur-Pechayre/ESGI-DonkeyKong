#pragma once

#include "ABlock.h"
#include "ASolidBlock.hpp"
#include "RessourcesManager.h"
#include <random>

class StonebrickBlock : public ABlock, virtual public ASolidBlock
{

private:
    RessourcesManager::Tids randomizeTexture();

public:
    StonebrickBlock(const RessourcesManager&);
    ~StonebrickBlock();
};
