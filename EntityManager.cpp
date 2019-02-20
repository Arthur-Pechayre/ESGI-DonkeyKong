#include "pch.h"
#include "EntityManager.h"

EntityManager::EntityManager(const RessourcesManager& manager) :
    ressourcesManager{&manager},
    diamondsMap()
{
}

void EntityManager::initDiamonds(const std::vector<sf::Vector2f>& diamonds)
{
    for (auto realPos : diamonds) {
        ++this->diamondsCount;
        auto neod = new DiamondEntity(*this->ressourcesManager);
        neod->setPosition(realPos);
        neod->scale(sf::Vector2f(0.75f, 0.75f));

        auto pos = neod->getGridPosition();
        this->diamondsMap[pos.x][pos.y] = neod;
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

std::vector<AEntity*> EntityManager::getEntitiesAt(int y, int x) const
{
    std::vector<AEntity*> entities;

    auto itx = this->diamondsMap.find(x);
    if (itx != this->diamondsMap.end()) {
        auto ity = itx->second.find(y);
        if (ity != itx->second.end()) {
            entities.push_back(ity->second);
        }
    }

    return entities;
}

int EntityManager::updateDiamonds(std::vector<DiamondEntity*> dimondsCaught) {
    int n = 0;

    for (auto e : dimondsCaught) {
        sf::Vector2i pos = e->getGridPosition();

        auto itx = this->diamondsMap.find(pos.x);
        if (itx != this->diamondsMap.end()) {
            auto ity = itx->second.find(pos.y);
            if (ity != itx->second.end()) {
                itx->second.erase(ity);
                ++n;
                if (itx->second.size() == 0) {
                    this->diamondsMap.erase(itx);
                }
            }
        }
    }

    return n;
}
