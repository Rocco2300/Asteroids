#pragma once

#include "Asteroid.h"

class Spawner
{
private:
    std::vector<Asteroid>* asteroids;
public:
    Spawner();
    Spawner(std::vector<Asteroid>& asteroids);
    void init(std::vector<Asteroid>& asteroids);
    void spawnAsteroid(ast::Vector2 pos, ast::Vector2 dir, float speed, AsteroidSize size);
    void spawnAsteroids(int count);
};

