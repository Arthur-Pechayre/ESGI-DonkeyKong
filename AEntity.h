#pragma once

#include "RessourcesManager.h"

class AEntity : public sf::Sprite
{
private:
    const RessourcesManager::Tids _tid;

public:
    AEntity(const RessourcesManager&, const RessourcesManager::Tids&);
    virtual ~AEntity() {};

    virtual void draw(sf::RenderWindow&);

    float                   width() const;
    float                   height() const;
    float                   top() const;
    float                   bot() const;
    float                   left() const;
    float                   right() const;
    virtual sf::Vector2i    getGridPosition() const;
};

