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
    void    move(sf::Vector2f&, const sf::Time&, bool);
    ABlock* isOnLadder();
    ABlock* isGrounded();
    bool    canJump();

private:
    void    updateJumpingCD(bool, const sf::Time&);
    void    handleCollisions(const sf::Time&);
    void    applyFriction();
    void    applyGravity();
    void    updateFacing();
};
