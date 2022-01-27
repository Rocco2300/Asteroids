#pragma once

#include "Ship.h"
#include "Bullet.h"
#include "Spawner.h"
#include "Enemy.h"
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
    GameManager(Ship& player, std::vector<Asteroid>& asteroids,
        std::vector<Bullet>& bullets, Enemy& enemy);
    void reset();
    int getScore();
    void spawnAsteroids();
    GameState checkCollisions();
    GameState update();
};
