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

    int score;
    int numberOfAsteroids;
    sf::Clock clock;
    sf::Time waveEndTime;
    sf::Time currentTime;
    sf::Time enemySpawnCheck;
    bool waveEnd;

    Ship *player; 
    std::vector<Asteroid> *asteroids;
    std::vector<Bullet> *bullets;
    Enemy* enemy;
public:
    GameManager();
    GameManager(Ship& player, std::vector<Asteroid>& asteroids,
        std::vector<Bullet>& bullets, Enemy& enemy);
    void reset();
    int getScore();
    void spawnAsteroids(int n);
    GameState checkCollisions();
    GameState update();
};
