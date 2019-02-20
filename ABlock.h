#pragma once

#include "RessourcesManager.h"

class ABlock : public sf::Sprite
{
private:
    const RessourcesManager::Tids _tid;

public:
    ABlock(const RessourcesManager&, const RessourcesManager::Tids&, const sf::Vector2f&);
    virtual ~ABlock() {};
};
