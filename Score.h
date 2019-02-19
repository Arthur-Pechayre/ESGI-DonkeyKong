#pragma once

#include "Player.h"
#include "RessourcesManager.h"

class Score
{
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
    unsigned int        diamonds;

public:
    Score(const RessourcesManager&);
    ~Score() {};
    void draw(sf::RenderWindow&);
    void init(const Player*, sf::Font*, sf::Vector2u*);
};
