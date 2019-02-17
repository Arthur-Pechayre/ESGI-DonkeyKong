#pragma once

#include "Player.h"
#include "Map.h"
#include "PlayerSurroundings.hpp"
#include "RessourcesManager.h"

class PlayerManager
{
public:
    Player                  player;

private:
    PlayerSurroundings      playerSurroundings;

public:
    PlayerManager(const RessourcesManager&);
    ~PlayerManager();
    void    updateSurroundings(const Map&);
    void    updateFacing();
    void    move(sf::Vector2f&, const sf::Time&, bool);
    void    handleCollisions(const sf::Time&);
    void    applyFriction();
    void    applyGravity();
    ABlock* isOnLadder();
    ABlock* isGrounded();
};
