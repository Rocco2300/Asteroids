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

    sf::RenderWindow window;
    sf::Texture* shipTex;
    sf::Texture* overlay;
    sf::Sprite overlaySpr;

    sf::Font* font;
    sf::Text scoreText;
    sf::Text gameOverText;

    Ship ship;
    Enemy enemy;
    sf::Texture* shipHpTexture;
    sf::Sprite shipHpSprite;
    std::vector<Asteroid> asteroids;
    std::vector<Bullet> bullets;
    ast::Vector2 v;
public:
    Game();
    void pollEvents();
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states);
    void update();
private:
    void reset();
    void createWindow(std::string windowName, int frameLimit);
    void loadTextures();
    template <typename T>
    void updateEntities(std::vector<T>& v, sf::Time dt);
    template <typename T>
    void drawEntities(std::vector<T>& v);
    void drawLives();
    void checkDespawnedBullets();
    void draw();
};
