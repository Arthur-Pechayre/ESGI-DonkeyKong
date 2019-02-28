#pragma once

#include "RessourcesManager.h"

class AEntity;
typedef std::shared_ptr<AEntity> AEntity_;

class AEntity : public sf::Sprite
{
public:
    static const int    FACING_RIGHT = 1;
    static const int    FACING_LEFT = -1;
    sf::Vector2f        velocity;

private:
    const RessourcesManager::Tids _tid;

public:
    AEntity(const RessourcesManager&, const RessourcesManager::Tids&);
    virtual ~AEntity() {}
    virtual void            draw(sf::RenderWindow&);
    int                     facing;
    bool                    facingChanged;
    float                   width() const;
    float                   height() const;
    float                   top() const;
    float                   bot() const;
    float                   left() const;
    float                   right() const;
    virtual sf::Vector2i    getGridPosition() const;
};

