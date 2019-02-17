#include "pch.h"
#include "EntityManager.h"

EntityManager::EntityManager(const RessourcesManager& manager) :
    ressourcesManager{&manager},
    diamondsMap()
{
}

void EntityManager::initDiamonds(const std::vector<sf::Vector2f>& diamonds)
{
    for (auto diamPos : diamonds) {
        ++this->diamondsCount;
        this->diamondsMap[diamPos.x][diamPos.y] = new DiamondEntity(*this->ressourcesManager);
        this->diamondsMap[diamPos.x][diamPos.y]->setPosition(diamPos);
        this->diamondsMap[diamPos.x][diamPos.y]->scale(sf::Vector2f(0.75f, 0.75f));
    }
}

void EntityManager::draw(sf::RenderWindow& w)
{
    for (auto erow : this->diamondsMap) {
        for (auto& e : erow.second) {
            w.draw(*e.second);
        }
    }
}
