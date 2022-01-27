#include "Spawner.h"
#include "Constants.h"
#include <cmath>

Spawner::Spawner() { }

Spawner::Spawner(Ship& ship, std::vector<Asteroid>& asteroids)
{
    this->ship = &ship;
    this->asteroids = &asteroids;
}

void Spawner::init(Ship& ship, std::vector<Asteroid>& asteroids)
{
    this->ship = &ship;
    this->asteroids = &asteroids;
}

float Spawner::randomizeSpeed(AsteroidSize size)
{
    float speed;
    switch(size)
    {
    case Large:
        speed = (rand() % 100 + 50) / 100.f;
        break;
    case Medium:
        speed = (rand() % 100 + 100) / 100.f;
        break;
    case Small:
        speed = (rand() % 150 + 150) / 100.f;
    }
    return speed;
}

void Spawner::spawnAsteroid(ast::Vector2 pos, ast::Vector2 dir, float speed, AsteroidSize size)
{
    asteroids->emplace_back(pos, dir, speed, size);
}

void Spawner::spawnEnemy(Enemy* enemy, std::vector<Bullet>* bullets)
{
    int randomSide = rand() % 2;
    int y1 = ship->getPosition().y - 100;
    int y2 = ship->getPosition().y + 100;
    int randomHeight;
    do
    {
        randomHeight = rand() % (WINDOW_HEIGHT - 120) + 60;     
    } while (randomHeight < y1 && randomHeight > y2);
    
    ast::Vector2 pos(randomSide * WINDOW_WIDTH, randomHeight);
    ast::Vector2 dir((randomSide == 0) ? 1.f : -1.f, 0.f);
    *enemy = Enemy(pos, dir, 3.f, bullets);
}

bool Spawner::isInPlayerBounds(ast::Vector2 p)
{
    // Bounds of the grace area
    int x1 = ship->getPosition().x - 150;
    int y1 = ship->getPosition().y - 150;
    int x2 = ship->getPosition().x + 150;
    int y2 = ship->getPosition().y + 150;
    return p.x > x1 && p.x < x2 && p.y > y1 && p.y < y2;
}

bool Spawner::isNearAnotherAsteroid(ast::Vector2 p)
{
    for(int i = 0; i < asteroids->size(); i++)
    {
        if(ast::Vector2::distance(p, asteroids->at(i).getPosition()) <= 200.f)
            return true;
    }
    return false;
}

void Spawner::spawnAsteroids(const std::vector<AsteroidSize>& toSpawn)
{
    int cnt = 0;
    for(int i = 0; i < toSpawn.size(); i++)
    {
        ast::Vector2 randPos, randDir;
        // Do not spawn asteroids near player
        do
        {          
            randPos.x = rand() % WINDOW_WIDTH;
            randPos.y = rand() % WINDOW_HEIGHT;
            cnt ++;
        } while (isInPlayerBounds(randPos) || isNearAnotherAsteroid(randPos));

        float randAng = rand() % 360;
        randDir.x = cos(randAng * PI/180);
        randDir.y = sin(randAng * PI/180);
        float randSpeed = randomizeSpeed(toSpawn[i]);
        spawnAsteroid(randPos, randDir, randSpeed, toSpawn[i]);
    }
}