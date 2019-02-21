#include "pch.h"

#include "Score.h"

Score::Score(const RessourcesManager& manager) :
    txt(),
    bg()
{
    bg.setTexture(manager.T_MAP.at(RessourcesManager::Tids::score_bg));
    bg.setColor(sf::Color(255, 255, 255, 190));
}

void Score::init(const Player* player, sf::Font* font, sf::Vector2u* windowSize, unsigned int diamondsCount)
{
    this->diamondsCount = diamondsCount;
    this->diamondsCollected = 0;
    this->player = player;
    this->font = font;
    this->origin = sf::Vector2f(windowSize->x * 0.75, 0);
    this->size = sf::Vector2f(windowSize->x - this->origin.x, windowSize->y / 3);

    this->txt.setFont(*this->font);
    this->txt.setPosition(this->origin.x + this->size.x / 8, this->size.y * 0.1);
    this->txt.setCharacterSize(25);
    this->txt.setFillColor(sf::Color(230, 160, 0));
    this->txt.setOutlineThickness(1);
    this->txt.setOutlineColor(sf::Color::Black);

    sf::Vector2f scale(this->size.x / this->bg.getGlobalBounds().width, this->size.y / this->bg.getGlobalBounds().height);

    this->bg.setPosition(this->origin);
    this->bg.scale(scale);
}

void Score::draw(sf::RenderWindow& w)
{
    std::stringstream ss;

    ss
        << "                        SCORE\n"
        << "\n\n"
        << this->diamondsCollected << " / " << this->diamondsCount << " - Diamonds collected";
    this->txt.setString(ss.str());

    w.draw(this->bg);
    w.draw(this->txt);
}

Score::LevelStatus Score::getLevelStatus()
{
    if (diamondsCollected == diamondsCount) {
        return LevelStatus::Won;
    }

    return LevelStatus::Running;
}
