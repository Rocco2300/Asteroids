#include <set>
#include <cmath>
#include "GameManager.h"
#include "Constants.h"

GameManager::GameManager()
{
}

GameManager::GameManager(Ship& player, std::vector<Asteroid>& asteroids, 
    std::vector<Bullet>& bullets, Enemy& enemy)
{
    srand(time(NULL));
    this->state = GameState::Running;
    this->spawner.init(player, asteroids);
    this->score = 0;
    this->waveEnd = false;
    this->enemySpawnCheck = clock.getElapsedTime();

    this->player = &player;
    this->asteroids = &asteroids;
    this->bullets = &bullets;
    this->enemy = &enemy;
}

void GameManager::init(Ship& player, std::vector<Asteroid>& asteroids,
    std::vector<Bullet>& bullets, Enemy& enemy)
{
    srand(time(NULL));
    this->state = GameState::Running;
    this->spawner.init(player, asteroids);
    this->score = 0;
    this->waveEnd = false;
    this->enemySpawnCheck = clock.getElapsedTime();

    this->player = &player;
    this->asteroids = &asteroids;
    this->bullets = &bullets;
    this->enemy = &enemy;
}

void GameManager::reset()
{
    this->enemySpawnCheck = clock.getElapsedTime();
    *enemy = Enemy();
    score = 0;
    state = GameState::Running;
}

int GameManager::getScore()
{
    return score;
}

void GameManager::spawnAsteroids(int n)
{
    waveEnd = false;
    asteroids->clear();
    spawner.spawnAsteroids(n);
}

void calculateOffsetVectors(ast::Vector2 dir, ast::Vector2& offset1, ast::Vector2& offset2)
{
    // Find 2 perpendicular vectors to dir to place new asteroid
    // when the larger asteroid is broken
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
    // Get a 2 random angle offsets
    int rand1, rand2;
    rand1 = (rand() % 40) + 5;
    rand2 = (rand() % 40) + 5;
    // Build the new direction vector
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
    // Check player - asteroid collisions
    for(int i = asteroids->size()-1; i >= 0; i--)
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

    // Check player - bullet collisions
    for(int i = bullets->size()-1; i >= 0; i--)
    {
        std::string tag = CircleCollider::checkCollision
                            (
                                player->getCircleCollider(), 
                                bullets->at(i).getCircleCollider()
                            );       
        if(tag == "bullet")
        {
            player->takeDamage();
            player->reset();
            bullets->erase(bullets->begin() + i);
            if(player->getLives() == 0)
            {
                state = GameOver;
            }
            return state;
        }
    }

    // Check the asteroid - bullet collisions
    for(int j = asteroids->size()-1; j >= 0; j--)
    {
        for(int i = bullets->size()-1; i >= 0; i--)
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
                break;
            }
        }
    }

    if(enemy->isAlive())
    {
        // Check enemy - player collisions
        std::string t = CircleCollider::checkCollision
        (
            player->getCircleCollider(), 
            enemy->getCircleCollider()
        );

        if(t == "enemy")
        {
            player->takeDamage();
            player->reset();
            *enemy = Enemy();
            if(player->getLives() == 0)
            {
                state = GameOver;
            }
            enemySpawnCheck = clock.getElapsedTime();
            return state;
        }

        // Check enemy - bullet collisions
        for(int i = bullets->size()-1; i >= 0; i--)
        {
            std::string tag = CircleCollider::checkCollision
            (
                enemy->getCircleCollider(), 
                bullets->at(i).getCircleCollider()
            );

            if(tag == "bullet")
            {
                bullets->erase(bullets->begin() + i);
                *enemy = Enemy();
                score += 500;
                enemySpawnCheck = clock.getElapsedTime();
                break;
            }
        }
    }
    return state;
}

GameState GameManager::update()
{
    GameState state = checkCollisions();
    currentTime = clock.getElapsedTime();
    if(asteroids->empty())
    {
        if(!waveEnd)
        {
            waveEndTime = clock.getElapsedTime();
            waveEnd = true;
        }

        if((currentTime - waveEndTime).asSeconds() >= 3.f)
        {
            enemySpawnCheck = clock.getElapsedTime();
            spawnAsteroids(1);
        }
    }

    if((currentTime - enemySpawnCheck).asSeconds() >= 3.f && !enemy->isAlive() && !waveEnd)
    {
        int chance = rand() % 100 + 1;
        if(chance <= 50)
        {
            int randomHeight = rand() % (WINDOW_HEIGHT - 120) + 60;
            int randomSide = rand() % 2;
            ast::Vector2 pos(randomSide * WINDOW_WIDTH, randomHeight);
            ast::Vector2 dir((randomSide == 0) ? 1.f : -1.f, 0.f);
            *enemy = Enemy(pos, dir, 3.f, bullets);
        }
    }
    return state;
}