#pragma once

#include "Ship.h"
#include "Asteroid.h"
#include "Enemy.h"

class Spawner
{
private:
    Ship* ship;
    std::vector<Asteroid>* asteroids;
private:
    bool isInPlayerBounds(ast::Vector2 p);
    bool isNearAnotherAsteroid(ast::Vector2 p);
public:
    Spawner();
    Spawner(Ship& ship, std::vector<Asteroid>& asteroids);
    void init(Ship& ship, std::vector<Asteroid>& asteroids);
    float randomizeSpeed(AsteroidSize size);
    void spawnAsteroid(ast::Vector2 pos, ast::Vector2 dir, float speed, AsteroidSize size);
    void spawnEnemy(Enemy* enemy, std::vector<Bullet>* bullets);
    void spawnAsteroids(int count);
};

