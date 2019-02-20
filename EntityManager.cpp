#include "pch.h"
#include "EntityManager.h"

EntityManager::EntityManager(const RessourcesManager& manager, const Map& map) :
    ressourcesManager{ &manager },
    map{ &map },
    pufferfishs(),
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

    for (auto p : this->pufferfishs) {
        w.draw(*p);
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

void EntityManager::updatePufferfishs(const sf::Time& elapsedTime)
{
    for (auto p : this->pufferfishs) {
        p->velocity.x = this->isGrounded(*p) ? p->facing * PufferfishEntity::SPEED + p->velocity.x : 0;
        this->applyGravity(*p);
        this->applyFriction(*p);
        p->rotate(10 * p->facing);

        if (abs(p->velocity.x) > PufferfishEntity::MAX_X_SPEED) {
            p->velocity.x = p->velocity.x > 0 ? PufferfishEntity::MAX_X_SPEED : -PufferfishEntity::MAX_X_SPEED;
        }
        if (abs(p->velocity.y) > PufferfishEntity::MAX_Y_SPEED) {
            p->velocity.y = p->velocity.y > 0 ? PufferfishEntity::MAX_Y_SPEED : -PufferfishEntity::MAX_Y_SPEED;
        }
        p->move(p->velocity * elapsedTime.asSeconds());
        auto b = isCollidingInBlock(*p);
        if (b) {
            if (p->hitsRemaining == 0) {
                this->pufferfishs.erase(std::remove(this->pufferfishs.begin(), this->pufferfishs.end(), p), this->pufferfishs.end());
            }
            p->move(abs(p->getPosition().x - b->getPosition().x) * p->velocity.x > 0 ? -1 : 1, 0);
            p->velocity.x *= -1;
            --p->hitsRemaining;
        }
        this->updateFacing(*p);
    }
}

void EntityManager::spawnPufferfishs(const sf::Time& elapsedTime)
{
    for (auto s : this->spawners) {
        if (s->spawn(elapsedTime)) {
            sf::Vector2i spawnPos(
                (round(s->getPosition().x / 32) + s->facing),
                round(s->getPosition().y / 32)
            );
            if (dynamic_cast<ASolidBlock*>(this->map->tileMap[spawnPos.y][spawnPos.x])) {
                return;
            }
            PufferfishEntity* neo = new PufferfishEntity(*this->ressourcesManager);
            neo->setPosition(spawnPos.x * 32 + 16, spawnPos.y * 32 - 16) ;
            neo->facing = s->facing;

            this->pufferfishs.push_back(neo);
        }
    }
}

void EntityManager::updateFacing(AEntity& e)
{
    int prevFacing = e.facing;
    e.facing = e.velocity.x == 0 ? e.facing : e.velocity.x > 0 ? AEntity::FACING_RIGHT : AEntity::FACING_LEFT;
    e.facingChanged = prevFacing != e.facing;
}

ABlock* EntityManager::isCollidingInBlock(AEntity& e)
{
    auto pos = e.getGridPosition();

    return dynamic_cast<ASolidBlock*>(this->map->tileMap[pos.y][pos.x]) ? this->map->tileMap[pos.y][pos.x] : nullptr;
};

bool EntityManager::isGrounded(AEntity& e)
{
    int y = round((e.bot() - 16) / 32.f);
    int x1 = round((e.left() + 16) / 32.f);
    int x2 = round((e.right() - 16) / 32.f);

    return dynamic_cast<ASolidBlock*>(this->map->tileMap[y][x1]) || dynamic_cast<ASolidBlock*>(this->map->tileMap[y][x2]);
}

void EntityManager::applyFriction(AEntity& e)
{
    e.velocity.x *= this->isGrounded(e) ? FRICTION : 1;
}

void EntityManager::applyGravity(AEntity& e)
{
    if (!this->isGrounded(e)) {
        e.velocity.y += GRAVITY;
    }
    else {
        e.velocity.y = 0;
    }
}
