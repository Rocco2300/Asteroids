#include <cmath>
#include "src/include/GameManager.h"
#include "src/include/Constants.h"

GameManager::GameManager()
{
}

GameManager::GameManager(Ship& player, std::vector<Asteroid>& asteroids, 
    std::vector<Bullet>& bullets)
{
    srand(time(NULL));
    this->state = GameState::Running;
    this->spawner.init(player, asteroids);
    this->score = 0;

    this->player = &player;
    this->asteroids = &asteroids;
    this->bullets = &bullets;
}

void GameManager::init(Ship& player, std::vector<Asteroid>& asteroids,
    std::vector<Bullet>& bullets)
{
    srand(time(NULL));
    this->state = GameState::Running;
    this->spawner.init(player, asteroids);
    this->score = 0;

    this->player = &player;
    this->asteroids = &asteroids;
    this->bullets = &bullets;
}

void GameManager::reset()
{
    score = 0;
    state = GameState::Running;
}

int GameManager::getScore()
{
    return score;
}

void GameManager::spawnAsteroids(int n)
{
    asteroids->clear();
    spawner.spawnAsteroids(n);
}

void calculateOffsetVectors(ast::Vector2 dir, ast::Vector2& offset1, ast::Vector2& offset2)
{
    float delta = 4 + 4 * ((dir.x * dir.x) / (dir.y * dir.y));
    offset1.x = sqrt(delta) / (2 + 2 * ((dir.x * dir.x) / (dir.y * dir.y)));
    offset2.x = -sqrt(delta) / (2 + 2 * ((dir.x * dir.x) / (dir.y * dir.y)));
    offset1.y = -offset1.x * (dir.x / dir.y);
    offset2.y = -offset2.x * (dir.x / dir.y);
    offset1 *= 16.f;
    offset2 *= 16.f;
}

void randomizeDirection(ast::Vector2 dir, ast::Vector2 offset1, ast::Vector2& newDir1, ast::Vector2& newDir2)
{
    int rand1, rand2;
    rand1 = (rand() % 40) + 5;
    rand2 = (rand() % 40) + 5;
    float angleOfDir = atan2(dir.y, dir.x) * 180/PI;
    newDir1.x = cos((angleOfDir + rand1) * PI/180);
    newDir1.y = sin((angleOfDir + rand1) * PI/180);
    newDir2.x = cos((angleOfDir - rand2) * PI/180);
    newDir2.y = sin((angleOfDir - rand2) * PI/180);   
    // Make sure the directions of the new asteroids are 
    // pointing away from each other
    if(offset1 * newDir1 < 0)
    {
        ast::Vector2 aux = newDir1;
        newDir1 = newDir2;
        newDir2 = aux;
    }
}

GameState GameManager::checkCollisions()
{
    for(int i = 0; i < asteroids->size(); i++)
    {
        std::string tag = CircleCollider::checkCollision
                            (
                                player->getCircleCollider(), 
                                asteroids->at(i).getCircleCollider()
                            );
        if(tag == "asteroid")
        {
            player->takeDamage();
            player->reset();
            asteroids->erase(asteroids->begin() + i);
            if(player->getLives() == 0)
            {
                state = GameOver;
            }
            return state;
        }
    }

    for(int j = 0; j < asteroids->size(); j++)
    {
        for(int i = 0; i < bullets->size(); i++)
        {
            std::string tag = CircleCollider::checkCollision
                    (
                        bullets->at(i).getCircleCollider(), 
                        asteroids->at(j).getCircleCollider()
                    );
            if(tag == "asteroid")
            {
                bullets->erase(bullets->begin() + i);
                if(asteroids->at(j).getSize() == AsteroidSize::Large)
                {
                    ast::Vector2 pos = asteroids->at(j).getPosition();
                    ast::Vector2 dir = asteroids->at(j).getDirection();
                    asteroids->erase(asteroids->begin() + j);
                    ast::Vector2 offset1, offset2;
                    calculateOffsetVectors(dir, offset1, offset2);
                    ast::Vector2 newDir1, newDir2;
                    randomizeDirection(dir, offset1, newDir1, newDir2);
                    Asteroid ast;
                    spawner.spawnAsteroid(pos + offset1, newDir1, 3.f, AsteroidSize::Small);
                    spawner.spawnAsteroid(pos + offset2, newDir2, 3.f, AsteroidSize::Small);
                    score += 100; 
                }
                else
                {
                    asteroids->erase(asteroids->begin() + j);
                    score += 300;
                }
            }
        }
    }
    return state;
}