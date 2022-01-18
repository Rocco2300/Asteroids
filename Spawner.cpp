#include "src/include/Spawner.h"
#include "src/include/Constants.h"
#include <cmath>

Spawner::Spawner() { }

Spawner::Spawner(std::vector<Asteroid>& asteroids)
{
    this->asteroids = &asteroids;
}

void Spawner::init(std::vector<Asteroid>& asteroids)
{
    this->asteroids = &asteroids;
}

void Spawner::spawnAsteroid(ast::Vector2 pos, ast::Vector2 dir, float speed, AsteroidSize size)
{
    asteroids->emplace_back(pos, dir, speed, size);
}

void Spawner::spawnAsteroids(int count)
{
    // Bounds of the grace area
    int x1 = 275, x2 = 525;
    int y1 = 200, y2 = 400;
    ast::Vector2 randPos;
    ast::Vector2 randDir;
    for(int i = 0; i < count; i++)
    {
        randPos.x = rand() % WINDOW_WIDTH;
        randPos.y = rand() % WINDOW_HEIGHT;

        ast::Vector2 proj(0.f, 0.f);
        if(randPos.x > x1 && randPos.x < x2)
        {
            proj.x = std::min(randPos.x - x1, x2 - randPos.x);
        }
        if(randPos.y > y1 && randPos.y < y2)
        {
            proj.y = std::min(randPos.y - y1, y2 - randPos.y);
        }

        if(proj.x <= proj.y)
        {
            //int temp = WINDOW_WIDTH - proj.x;
            if(randPos.x >= WINDOW_WIDTH / 2)
                randPos.x += (rand() % x1) + proj.x;
            else 
                randPos.x -= (rand() % x1) + proj.x;
        }
        else
        {
            //int temp = WINDOW_HEIGHT - proj.y;
            if(randPos.y >= WINDOW_HEIGHT / 2)
                randPos.y += (rand() % y1) + proj.y;
            else
                randPos.y -= (rand() % y1) + proj.y;
        }

        float randAng = rand() % 360;
        randDir.x = cos(randAng * PI/180);
        randDir.y = sin(randAng * PI/180);
        spawnAsteroid(randPos, randDir, 3.f, AsteroidSize::Large);

        // axis = rand() % 2;      // Coinflip if the asteroid spawns on the top/bottom size or left/right size
        // side = rand() % 2;      // Cointflip to choose between the 2 sides of the screen
        // randPos.x = (rand() % (800 - 32)) + 16;
        // randPos.y = (rand() % (600 - 32)) + 16;
        // // We project the random pos to the coinflipped side
        // if(axis == 0)       // Vertical
        //     randPos.y = randPos.y * side + (WINDOW_HEIGHT - randPos.y) * side;
        // else if(axis == 1) // Horizontal
        //     randPos.x = randPos.x * side + (WINDOW_WIDTH - randPos.x) * side;

        // float randAng;
        // if(axis == 0)
        //     randAng = (rand() % 120) + 30 + 180*side;
        // else if(axis == 1)
        //     randAng = (rand() % 120) + 120 + (-180)*(~side);
        // randDir.x = std::cos(randAng * PI/180);
        // randDir.y = std::sin(randAng * PI/180);
        // spawnAsteroid(randPos, randDir, 3.f, AsteroidSize::Large);
    }
}