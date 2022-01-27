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
    this->wave = 1;

    this->player = &player;
    this->asteroids = &asteroids;
    this->bullets = &bullets;
    this->enemy = &enemy;

    spawnAsteroids();
}

void GameManager::reset()
{
    wave = 1;
    this->enemySpawnCheck = clock.getElapsedTime();
    *enemy = Enemy();
    score = 0;
    state = GameState::Running;
    spawnAsteroids();
}

int GameManager::getScore()
{
    return score;
}

void GameManager::buildAsteroidWaveList()
{
    toSpawn.clear();
    std::vector<int> weights = {50, 20, 5};

    int sum = 0, index = 0;
    int target = 60 + (wave - 1) * 35;
    target = (target > 180) ? 180 : target;

    while(sum != target && index < 3)
    {
        if(sum + weights[index] <= target)
        {
            sum += weights[index];
            switch(weights[index])
            {
            case 50:
                toSpawn.push_back(AsteroidSize::Large);
                break;
            case 20:
                toSpawn.push_back(AsteroidSize::Medium);
                break;
            case 5:
                toSpawn.push_back(AsteroidSize::Small);
                break;
            }
        }
        else
            index++;
    }
}

void GameManager::spawnAsteroids()
{
    std::cout << wave << std::endl;
    buildAsteroidWaveList();
    waveEnd = false;
    asteroids->clear();
    spawner.spawnAsteroids(toSpawn);
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
    rand1 = rand() % 90;
    rand2 = rand() % 90;
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
        if(tag == "enemyBullet")
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
                AsteroidSize size = asteroids->at(j).getSize();
                if(size != AsteroidSize::Small)
                {
                    ast::Vector2 pos = asteroids->at(j).getPosition();
                    ast::Vector2 dir = asteroids->at(j).getDirection();
                    asteroids->erase(asteroids->begin() + j);

                    ast::Vector2 offset1, offset2;
                    calculateOffsetVectors(dir, offset1, offset2);
                    ast::Vector2 newDir1, newDir2;
                    randomizeDirection(dir, offset1, newDir1, newDir2);

                    Asteroid ast;
                    AsteroidSize newSize = (size == Large) ? Medium : Small;
                    float speed1 = spawner.randomizeSpeed(newSize);
                    float speed2 = spawner.randomizeSpeed(newSize);
                    spawner.spawnAsteroid(pos + offset1, newDir1, speed1, newSize);
                    spawner.spawnAsteroid(pos + offset2, newDir2, speed2, newSize);
                    score += (size == AsteroidSize::Large) ? 50 : 100;
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

// 3 ^ (x - 1) + 3;
int f(int x)
{
    return std::pow(3, x - 1) + 3;
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
            // Cap the exponential growth at wave 5
            score += f((wave <= 5) ? wave : 5) * 100;
            wave++;
            enemySpawnCheck = clock.getElapsedTime();
            spawnAsteroids();
        }
    }

    if((currentTime - enemySpawnCheck).asSeconds() >= 10.f && !enemy->isAlive() && !waveEnd && wave != 1)
    {
        int chance = rand() % 100 + 1;
        if(chance <= 50)
        {
            spawner.spawnEnemy(enemy, bullets);
        }
    }
    return state;
}