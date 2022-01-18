#pragma once

#include "Entity.h"
#include "Vector2.h"

enum AsteroidSize
{
    Small = 32,
    Large = 64
};

class Asteroid : public Entity
{
private:
    AsteroidSize size;
    ast::Vector2 dir;
    float speed;
    //float rot;
public:
    Asteroid();
    Asteroid(ast::Vector2 pos, ast::Vector2 dir, float speed);
    Asteroid(ast::Vector2 pos, ast::Vector2 dir, float speed, AsteroidSize size);
    void rotate(sf::Time dt);
    void update(sf::Time dt);
    ast::Vector2 getDirection();
    AsteroidSize getSize();
};

