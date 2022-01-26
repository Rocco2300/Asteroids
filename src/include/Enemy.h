#pragma once

#include "Entity.h"
#include "Bullet.h"

class Enemy : public Entity
{
private:
    ast::Vector2 dir;
    float speed;
    bool alive;

    bool predict;
    int shootCount;
    float bulletSpeed;
    ast::Vector2 shootDir;
    sf::Clock clock;
    sf::Time currentTime;
    sf::Time shootTime;
    std::vector<Bullet>* bullets;
private:
    void calculateShootDir(ast::Vector2 tp, ast::Vector2 tv);
public:
    Enemy();
    Enemy(ast::Vector2 pos, ast::Vector2 dir, float speed,
        std::vector<Bullet>* bullets);
    void shoot();
    void update(sf::Time dt, ast::Vector2 tp, ast::Vector2 tv);
    bool isAlive();
};