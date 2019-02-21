#pragma once

#include "Player.h"
#include "RessourcesManager.h"

class Score
{
public:
    enum LevelStatus
    {
        Running,
        Won,
        Lost
    };

private:
    sf::Text            txt;
    sf::Sprite          bg;

public:
    const Player*       player;
    sf::Font*           font;
    sf::Vector2f        origin;
    sf::Vector2f        size;

    //sf::Time          timeLeft;
    //unsigned int      score;
    unsigned int        diamondsCollected;
    unsigned int        diamondsCount;

public:
    Score(const RessourcesManager&);
    ~Score() {};
    void            draw(sf::RenderWindow&);
    void            init(const Player*, sf::Font*, sf::Vector2u*, unsigned int);
    LevelStatus     getLevelStatus();
};
