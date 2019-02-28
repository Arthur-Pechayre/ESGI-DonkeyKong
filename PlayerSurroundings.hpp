#pragma once

#include "pch.h"

#include "ABlock.h"
#include "Map.h"
#include "Player.h"
#include "EntityManager.h"

class PlayerSurroundings
{
public:
    enum Pos
    {
        TopL,
        Top,
        TopR,
        MiddleTopL,
        MiddleTopR,
        MiddleBotL,
        MiddleBotR,
        BotL,
        Bot,
        BotR,
        Head,
        Legs
    };

    enum EntityPos
    {
        EHead,
        ELegs,
        EPufferfishs
    };

    std::vector<ABlock_>               blocks;
    std::vector<std::vector<AEntity_>>      entities;

private:
    template <typename Block>
    ABlock_ isColliding(const sf::FloatRect& hb, const std::initializer_list<Pos>& addresses) {
        for (auto i : addresses) {
            if (this->blocks[i] && this->blocks[i]->getGlobalBounds().intersects(hb) && std::dynamic_pointer_cast<Block>(this->blocks[i])) {
                return this->blocks[i];
            }
        }

        return nullptr;
    };

public:
    PlayerSurroundings() :
        blocks(12, nullptr),
        entities(3)
    {
    };

    ~PlayerSurroundings() {};

    void update(const Player& player, const Map& map, const EntityManager& e)
    {
        auto pos = player.getGridPosition();
        int x = pos.x;
        int y = pos.y;
        unsigned int bot = y + 1;
        unsigned int right = x + 1;
        int left = x - 1;
        int head = y - 1;
        int top = y - 2;

        // Update blocks
        this->blocks[Pos::BotL] = bot > map.size.y || left < 0 ? nullptr : map.tileMap[bot][left];
        this->blocks[Pos::Bot] = bot > map.size.y ? nullptr : map.tileMap[bot][x];
        this->blocks[Pos::BotR] = bot > map.size.y || right > map.size.x ? nullptr : map.tileMap[bot][right];
        this->blocks[Pos::Legs] = map.tileMap[y][x];
        this->blocks[Pos::MiddleBotL] = left < 0 ? nullptr : map.tileMap[y][left];
        this->blocks[Pos::MiddleBotR] = right > map.size.x ? nullptr : map.tileMap[y][right];
        this->blocks[Pos::Head] = map.tileMap[head][x];
        this->blocks[Pos::MiddleTopL] = head < 0 || left < 0 ? nullptr : map.tileMap[head][left];
        this->blocks[Pos::MiddleTopR] = head < 0 || right > map.size.x ? nullptr : map.tileMap[head][right];
        this->blocks[Pos::TopL] = top < 0 || left < 0 ? nullptr : map.tileMap[top][left];
        this->blocks[Pos::Top] = top < 0 ? nullptr : map.tileMap[top][x];
        this->blocks[Pos::TopR] = top < 0 || right > map.size.x ? nullptr : map.tileMap[top][right];

        // Update entities
        this->entities[EntityPos::ELegs] = e.getEntitiesAt(y, x);
        this->entities[EntityPos::EHead] = e.getEntitiesAt(head, x);
        this->entities[EntityPos::EPufferfishs].assign(e.pufferfishs.begin(), e.pufferfishs.end());
    };

    template <typename Block>
    ABlock_ isCollidingL(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.top += 2;
        hb.left -= 1;
        hb.width += 2;
        hb.height -= 4;

        return this->isColliding<Block>(hb, { Pos::TopL, Pos::MiddleTopL, Pos::MiddleBotL, Pos::BotL });
    };

    template <typename Block>
    ABlock_ isCollidingR(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.top += 2;
        hb.left -= 1;
        hb.width += 2;
        hb.height -= 4;

        return this->isColliding<Block>(hb, { Pos::TopR, Pos::MiddleTopR, Pos::MiddleBotR, Pos::BotR });
    };

    template <typename Block>
    ABlock_ isCollidingT(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.top -= 1;
        hb.left += 1;
        hb.width -= 2;
        hb.height += 2;

        return this->isColliding<Block>(hb, { Pos::Top, Pos::TopL, Pos::TopR });
    };

    template <typename Block>
    ABlock_ isCollidingB(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.top -= 1;
        hb.left += 1;
        hb.width -= 2;
        hb.height += 2;

        return this->isColliding<Block>(hb, { Pos::Bot, Pos::BotL, Pos::BotR });
    };

    template <typename Block>
    ABlock_ isOn(const sf::FloatRect& hb)
    {
        return this->isColliding<Block>(hb, { Pos::Head, Pos::Legs });
    };

    template <typename Entity>
    std::vector<std::shared_ptr<Entity>> touchingEntities(const sf::FloatRect& hb)
    {
        std::vector<std::shared_ptr<Entity>> res;

        for (auto i : { EntityPos::EHead, EntityPos::ELegs }) {
            for (auto e : this->entities[i]) {
                if (e->getGlobalBounds().intersects(hb)) {
                    auto entityColliding = std::dynamic_pointer_cast<Entity>(e);
                    if (entityColliding) {
                        res.push_back(entityColliding);
                    }
                }
            }
        }

        return res;
    };

    template <>
    std::vector<std::shared_ptr<PufferfishEntity>> touchingEntities<PufferfishEntity>(const sf::FloatRect& hb)
    {
        std::vector<std::shared_ptr<PufferfishEntity>> res;
    
        for (auto p : this->entities[EntityPos::EPufferfishs]) {
            if (p->getGlobalBounds().intersects(hb)) {
                res.push_back(std::dynamic_pointer_cast<PufferfishEntity>(p));

                return res;
            }
        }

        return res;
    };
};
