#pragma once

#include "pch.h"

#include "ABlock.h"
#include "Map.h"
#include "Player.h"

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
        BotR
    };
    std::vector<ABlock*>    blocks;

private:
    template <typename Block>
    ABlock* isColliding(const sf::FloatRect& hb, const std::initializer_list<Pos>& addresses) {
        for (auto i : addresses) {
            if (this->blocks[i] && this->blocks[i]->getGlobalBounds().intersects(hb) && dynamic_cast<Block*>(this->blocks[i])) {
                return this->blocks[i];
            }
        }

        return nullptr;
    };

public:
    PlayerSurroundings() :
        blocks(10, nullptr)
    {
    };

    ~PlayerSurroundings() {};

    void update(const Player& player, const Map& map)
    {
        int x = round(player.left() / 32);
        int y = round(player.top() / 32) + 1;
        unsigned int bot = y + 1;
        unsigned int right = x + 1;
        int left = x - 1;
        int head = y - 1;
        int top = y - 2;

        this->blocks[Pos::BotL] = bot > map.size.y || left < 0 ? nullptr : map.tileMap[bot][left];
        this->blocks[Pos::Bot] = bot > map.size.y ? nullptr : map.tileMap[bot][x];
        this->blocks[Pos::BotR] = bot > map.size.y || right > map.size.x ? nullptr : map.tileMap[bot][right];
        this->blocks[Pos::MiddleBotL] = left < 0 ? nullptr : map.tileMap[y][left];
        this->blocks[Pos::MiddleBotR] = right > map.size.x ? nullptr : map.tileMap[y][right];
        this->blocks[Pos::MiddleTopL] = head < 0 || left < 0 ? nullptr : map.tileMap[head][left];
        this->blocks[Pos::MiddleTopR] = head < 0 || right > map.size.x ? nullptr : map.tileMap[y - 1][right];
        this->blocks[Pos::TopL] = top < 0 || left < 0 ? nullptr : map.tileMap[top][left];
        this->blocks[Pos::Top] = top < 0 ? nullptr : map.tileMap[top][x];
        this->blocks[Pos::TopR] = top < 0 || right > map.size.x ? nullptr : map.tileMap[top][right];
    };

    template <typename Block>
    ABlock* isCollidingL(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.left -= 1;

        return this->isColliding<Block>(hb, { Pos::TopL, Pos::MiddleTopL, Pos::MiddleBotL, Pos::BotL });
    };

    template <typename Block>
    ABlock* isCollidingR(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.width += 1;

        return this->isColliding<Block>(hb, { Pos::TopR, Pos::MiddleTopR, Pos::MiddleBotR, Pos::BotR });
    };

    template <typename Block>
    ABlock* isCollidingT(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.top -= 1;

        return this->isColliding<Block>(hb, { Pos::Top, Pos::TopL, Pos::TopR });
    };

    template <typename Block>
    ABlock* isCollidingB(const sf::FloatRect& playerHitBox)
    {
        sf::FloatRect hb(playerHitBox);
        hb.height += 1;

        return this->isColliding<Block>(hb, { Pos::Bot, Pos::BotL, Pos::BotR });
    };
};
