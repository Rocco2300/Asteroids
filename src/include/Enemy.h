#pragma once

#include "Entity.h"
#include "Vector2.h"

class Enemy : public Entity
{
private:
    ast::Vector2 dir;
    float speed;
public:
    Enemy();
    Enemy(ast::Vector2 pos, ast::Vector2 dir, float speed);
    void update(sf::Time dt);
};