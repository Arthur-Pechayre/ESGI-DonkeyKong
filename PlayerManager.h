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
    void updateSurroundings(const Map&);
    void updateFacing(const sf::Vector2f& movement);
    void applyMovementConstraints(sf::Vector2f&, const sf::Time&);
};
