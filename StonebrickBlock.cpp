#include "pch.h"
#include "StonebrickBlock.h"

StonebrickBlock::StonebrickBlock(const RessourcesManager& manager, const char&, const sf::Vector2f& pos) :
ABlock(manager, randomizeTexture(), pos)
{
}

StonebrickBlock::~StonebrickBlock()
{
}

RessourcesManager::Tids StonebrickBlock::randomizeTexture()
{
    std::random_device rd;     
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, 100);

    int randInt = uni(rng);
    RessourcesManager::Tids tids[3] = {
        RessourcesManager::Tids::Bstonebrick,
        RessourcesManager::Tids::Bstonebrick_mossy,
        RessourcesManager::Tids::Bstonebrick_craked
    };



    return randInt <= 70 ? tids[0] : randInt <= 85 ? tids[1] : tids[2];
}
