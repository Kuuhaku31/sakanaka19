
// position.cpp

#include "base.h"


void
Position::MoveTo(float x, float y)
{
    this->x = x;
    this->y = y;
}

void
Position::MoveBy(float dx, float dy)
{
    this->x += dx;
    this->y += dy;
}

void
Position::MoveTo(const Vector2& p)
{
    this->x = p.vx;
    this->y = p.vy;
}

void
Position::MoveBy(const Vector2& d)
{
    this->x += d.vx;
    this->y += d.vy;
}

void
Position::MoveTo(const Point& p)
{
    this->x = p.px;
    this->y = p.py;
}

void
Position::MoveBy(const Point& d)
{
    this->x += d.px;
    this->y += d.py;
}
