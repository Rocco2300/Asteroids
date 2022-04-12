#pragma once

#include "Ship.h"
#include "Bullet.h"
#include "Spawner.h"
#include "Enemy.h"
#include "ParticleSystem.h"
#include <vector>

enum GameState
{
    GameOver = 0,
    Running,
};

class GameManager
{
private:
    GameState state;
    Spawner spawner;
    ParticleSystem* particles;
    SoundManager* soundManager;

    int wave;
    int score;
    sf::Clock clock;
    sf::Time waveEndTime;
    sf::Time currentTime;
    sf::Time enemySpawnCheck;
    std::vector<AsteroidSize> toSpawn;
    bool waveEnd;

    Ship *player; 
    std::vector<Asteroid> *asteroids;
    std::vector<Bullet> *bullets;
    Enemy* enemy;
private:
    void buildAsteroidWaveList();
public:
    GameManager();
    GameManager(Ship* player, std::vector<Asteroid>* asteroids,
        std::vector<Bullet>* bullets, Enemy* enemy, ParticleSystem* particles, 
        SoundManager* soundManager);
    void reset();
    int getScore();
    void spawnAsteroids();
    void destroyAsteroid(int index);
    void destroyBullet(int index);
    void destroyEnemy();
    void destroyPlayer();
    void checkBulletCollisions();
    GameState checkPlayerCollisions();
    GameState update();
};
