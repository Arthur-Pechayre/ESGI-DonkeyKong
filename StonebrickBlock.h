#pragma once

#include "ABlock.h"
#include "RessourcesManager.h"
#include <random>

class StonebrickBlock : public ABlock
{

private:
    RessourcesManager::Tids randomizeTexture();

public:
    StonebrickBlock(const RessourcesManager&);
    ~StonebrickBlock();
};
