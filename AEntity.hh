#pragma once
class AEntity
{
public:
    AEntity(size_t x, size_t y, char d);
    virtual ~AEntity() = 0;
    //virtual void move() = 0;
    void setX(size_t x);
    void setY(size_t y);
    size_t getX() const;
    size_t getY() const;
    char getDirection() const;
protected:
    char _direction;
    size_t _x;
    size_t _y;
};
   