#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Vector2.h"

class CircleCollider
{
private:
    sf::CircleShape debug;
    ast::Vector2 pos;
    std::string tag;
    float radius;
    bool enabled;
public:
    CircleCollider();
    CircleCollider(ast::Vector2 pos, float radius, std::string tag);
    void create(ast::Vector2 pos, float radius, std::string tag);
    void setPosition(ast::Vector2 pos);
    void disable();
    ast::Vector2 getPos();
    float getX();
    float getY();
    float getRadius();
    bool isEnabled();
    std::string getTag();
    sf::CircleShape getDebugCircle();
    static std::string checkCollision(CircleCollider first, CircleCollider second);
};
