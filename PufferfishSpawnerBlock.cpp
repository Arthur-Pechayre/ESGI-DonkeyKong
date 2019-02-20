#include "pch.h"

#include "PufferfishSpawnerBlock.h"

const float PufferfishSpawnerBlock::SPAWN_RATE = SPAWNERS_SPAWN_RATE;

PufferfishSpawnerBlock::PufferfishSpawnerBlock(const RessourcesManager& manager, const char& c, const sf::Vector2f& pos) :
    ABlock(manager, RessourcesManager::Bpufferfish_spawner, pos),
    facing(c == '<' ? -1 : 1),
    spawnCooldown(sf::Time::Zero)
{
    this->rotate(90.f * facing);
    this->setPosition(pos);
}

void PufferfishSpawnerBlock::setPosition(float x, float y)
{
    sf::Sprite::setPosition(facing == 1 ? x + 32.f : x, facing == -1 ? y + 32.f : y);
}

void PufferfishSpawnerBlock::setPosition(const sf::Vector2f& pos)
{
    sf::Sprite::setPosition(pos + (facing == 1 ? sf::Vector2f(32, 0) : sf::Vector2f(0, 32)));
}

bool PufferfishSpawnerBlock::spawn(const sf::Time& elapsedTime)
{
    if (this->spawnCooldown > sf::Time::Zero) {
        this->spawnCooldown -= elapsedTime;

        return false;
    }
    this->spawnCooldown = sf::seconds(PufferfishSpawnerBlock::SPAWN_RATE);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, 1);
    
    return uni(rng) == 0;
}
