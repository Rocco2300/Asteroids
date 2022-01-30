#include <iostream>
#include "CircleCollider.h"
#include "Vector2.h"

CircleCollider::CircleCollider() { }

CircleCollider::CircleCollider(ast::Vector2 pos, float radius, std::string tag)
{
    this->pos = pos;
    this->radius = radius;
    this->tag = tag;
    this->enabled = true;

    debug.setRadius(radius);
    debug.setOutlineColor(sf::Color::Red);
    debug.setOutlineThickness(1);
    debug.setFillColor(sf::Color::Transparent);
    debug.setOrigin(radius, radius);
    debug.setPosition(pos.toSfVector2f());
}

void CircleCollider::create(ast::Vector2 pos, float radius, std::string tag)
{
    this->pos = pos;
    this->radius = radius;
    this->tag = tag;
    this->enabled = true;

    debug.setRadius(radius);
    debug.setOutlineColor(sf::Color::Red);
    debug.setOutlineThickness(1);
    debug.setFillColor(sf::Color::Transparent);
    debug.setOrigin(radius, radius);
    debug.setPosition(pos.toSfVector2f());
}

void CircleCollider::setPosition(ast::Vector2 pos)
{
    this->pos = pos;
    debug.setPosition(pos.toSfVector2f());
}

void CircleCollider::disable()
{
    this->enabled = true;
}

ast::Vector2 CircleCollider::getPos() { return pos; }
float CircleCollider::getX() { return pos.x; }
float CircleCollider::getY() { return pos.y; }
float CircleCollider::getRadius() { return radius; }
bool CircleCollider::isEnabled() { return enabled; }
std::string CircleCollider::getTag() { return tag; }
sf::CircleShape CircleCollider::getDebugCircle() { return debug; }

std::string CircleCollider::checkCollision(CircleCollider first, CircleCollider second)
{
    if(!first.enabled || !second.enabled)
        return "";
    if(ast::Vector2::distance(first.getPos(), second.getPos()) < first.getRadius() + second.getRadius())
    {
        return second.getTag(); 
    }
    return "";
}
