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
    sf::Sound               hurtSound;

public:
    PlayerManager(const RessourcesManager&);
    ~PlayerManager();
    void                                        update(const Map&, const EntityManager&);
    void                                        move(sf::Vector2f&, const sf::Time&, bool);
    std::vector<std::shared_ptr<DiamondEntity>> collectDiamonds();
    bool                                        isTakingDamages(const sf::Time&);
    ABlock_                                     isOnLadder();
    ABlock_                                     isGrounded();
    bool                                        canJump();

private:
    void    updateJumpingCD(bool, const sf::Time&);
    void    handleCollisions(const sf::Time&);
    void    applyFriction();
    void    applyGravity();
    void    updateFacing();
};
