#pragma once

class AEntity : public sf::Sprite
{
public:
    AEntity();
    virtual ~AEntity() {};

    virtual void draw(sf::RenderWindow&);

    float width() const;
    float height() const;
    float top() const;
    float bot() const;
    float left() const;
    float right() const;
};

