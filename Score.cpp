#include "pch.h"

#include "Score.h"

Score::Score(const RessourcesManager& manager) :
    txt(),
    bg(),
    hearts(LIFE_POINTS),
    font{manager.F_MAP.at(RessourcesManager::Fids::Sansation)}
{
    bg.setTexture(manager.T_MAP.at(RessourcesManager::Tids::UIscore_bg));
    bg.setColor(sf::Color(255, 255, 255, 190));

    for (int i = 0; i < this->hearts.size(); ++i) {
        this->hearts[i].setTexture(manager.T_MAP.at(RessourcesManager::Tids::UIheart));
    }
}

void Score::init(const Player* player, sf::Vector2u* windowSize, unsigned int diamondsCount)
{
    this->diamondsCount = diamondsCount;
    this->diamondsCollected = 0;
    this->player = player;
    this->origin = sf::Vector2f(windowSize->x * 0.75, 0);
    this->size = sf::Vector2f(windowSize->x - this->origin.x, windowSize->y / 3);

    this->txt.setFont(this->font);
    this->txt.setPosition(this->origin.x + this->size.x / 6, this->size.y * 0.18);
    this->txt.setCharacterSize(25);
    this->txt.setFillColor(sf::Color(230, 160, 0));
    this->txt.setOutlineThickness(1);
    this->txt.setOutlineColor(sf::Color::Black);

    sf::Vector2f scale(this->size.x / this->bg.getGlobalBounds().width, this->size.y / this->bg.getGlobalBounds().height);

    this->bg.setPosition(this->origin);
    this->bg.scale(scale);

    sf::Vector2f heartsBasePos(this->origin.x + this->size.x / 6, this->size.y * 0.65);
    for (int i = 0; i < this->hearts.size(); ++i) {
        this->hearts[i].setPosition(heartsBasePos.x, heartsBasePos.y);
        heartsBasePos.x += 32 + 8;
    }
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
    for (auto h : this->hearts) {
        w.draw(h);
    }
}

Score::LevelStatus Score::getLevelStatus()
{
    if (this->hearts.size() == 0) {
        return LevelStatus::Lost;
    }

    if (diamondsCollected == diamondsCount) {
        return LevelStatus::Won;
    }

    return LevelStatus::Running;
}

void Score::removeLifePoint()
{
    this->hearts.erase(this->hearts.end() - 1);
}
