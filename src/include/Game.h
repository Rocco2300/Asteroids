#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Asteroids.h"
#include "MenuState.h"
#include "GameManager.h"
#include "Bullet.h"
#include "Constants.h"
#include "Ship.h"
#include "Enemy.h"

class Game : public MenuState
{
private:
    ParticleSystem particles;
    SoundManager soundManager;
    GameManager manager;
    GameState state;
    bool gameOver;

    sf::Texture* shipTex;
    sf::Texture* overlay;
    sf::Sprite overlaySpr;

    sf::Font* font;
    sf::Text scoreText;

    Ship ship;
    Enemy enemy;
    sf::Texture* shipHpTexture;
    sf::Sprite shipHpSprite;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
public:
    Game(Asteroids* context);
    bool pollEvents();
    void update(sf::Time dt);
    void draw();
    void update();
private:
    void reset();
    template <typename T>
    void updateEntities(std::vector<T>& v, sf::Time dt);
    template <typename T>
    void drawEntities(std::vector<T>& v);
    void drawLives();
    void checkDespawnedBullets();
};
