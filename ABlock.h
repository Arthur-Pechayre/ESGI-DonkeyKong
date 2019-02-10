#pragma once

#include "RessourcesManager.h"

class ABlock : public sf::Sprite
{
private:
    const RessourcesManager::Tids TID;

public:
    ABlock(const RessourcesManager& manager, const RessourcesManager::Tids& tid);
    virtual ~ABlock() {};
};
