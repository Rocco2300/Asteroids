#pragma once

#include "Ship.h"
#include "Bullet.h"
#include "Spawner.h"
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
    sf::Clock clock;
    sf::Time waveRespawnTime;

    Ship *player; 
    int score;
    std::vector<Asteroid> *asteroids;
    std::vector<Bullet> *bullets;
public:
    GameManager();
    GameManager(Ship& player, std::vector<Asteroid>& asteroids,
        std::vector<Bullet>& bullets);
    void init(Ship& player, std::vector<Asteroid>& asteroids,
        std::vector<Bullet>& bullets);
    void reset();
    int getScore();
    void spawnAsteroids(int n);
    GameState checkCollisions();
    GameState update();
};
