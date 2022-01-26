#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include "Game.h"
#include "TextureLoader.h"

#define DEBUG true

Game::Game()
{ 
    srand(time(NULL));
    createWindow("Asteroids", 60);
    TextureLoader::getInstance()->loadTextures();

    shipHpTexture = TextureLoader::getInstance()->getShipTexture();
    shipHpSprite.setTexture(*shipHpTexture);
    shipHpSprite.setTextureRect({0, 0, 32, 32});
    shipHpSprite.setOrigin({16.f, 16.f});
    shipHpSprite.setScale({.75f, .75f});
    
    if(!font.loadFromFile("fonts/ARCADECLASSIC.TTF"))
        std::cerr << "Error loading font!" << std::endl;
    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOrigin({30.f, 0.f});
    scoreText.setPosition({800.f, 0.f});

    ship = Ship(bullets);

    manager.init(ship, asteroids, bullets, enemy);
    manager.spawnAsteroids(1);
    scoreText.setString(std::to_string(manager.getScore()));
}

void Game::createWindow(std::string name, int frameLimit)
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), name);
    window.setFramerateLimit(frameLimit);
    window.setVerticalSyncEnabled(true);
}

void Game::update()
{
    GameState state;
    sf::Clock clk;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                TextureLoader::getInstance()->destroyInstance();
                window.close();
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
            {
                reset();
                // enemy = Enemy();
                manager.reset();
                state = GameState::Running;
            }
        }

        state = manager.update();
        if(state != GameOver)
        {
            ship.update(dt);
            if(enemy.isAlive())
                enemy.update(dt, ship.getPosition(), ship.getVelocityVector());
            updateEntities(asteroids, dt);
            updateEntities(bullets, dt);
            checkDespawnedBullets();

            // Correct the score display to display at the edge regardless of width of text
            int score = manager.getScore();
            float offset = (score > 0) ? ((int)floor(log10(score)) * 20.f) + 30.f : 30.f;
            scoreText.setOrigin({offset, 0.f});
            scoreText.setString(std::to_string(manager.getScore()));

            if(state == GameState::GameOver && !gameOver)
            {
                gameOver = true;
                std::cout << "Game over!" << std::endl;
            }
        }

        // Framerate counter
        #if DEBUG
        sf::Time frameCntTime;
        frameCntTime = clk.getElapsedTime();
        if(frameCntTime.asSeconds() >= 1.f)
        {
            std::cout << 1.f/dt.asSeconds() << std::endl;
            frameCntTime = clk.restart();
        }
        #endif
        draw();
    }
}

void Game::reset()
{
    ship = Ship(bullets);
    int randAng;
    ast::Vector2 randPos;
    ast::Vector2 randDir;
    Asteroid asteroid;
    asteroids.clear();
    bullets.clear();
    manager.spawnAsteroids(1);
}

template <typename T>
void Game::updateEntities(std::vector<T>& v, sf::Time dt)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        v[i].update(dt);
    }
}

template <typename T>
void Game::drawEntities(std::vector<T>& v)
{
    bool ceva = false;
    for(size_t i = 0; i < v.size(); i++)
    {
        window.draw(v[i].getSprite());
    }
}

template <typename T>
void Game::drawDebugEntities(std::vector<T>& v)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        window.draw(v[i].getDebugCircle());
    }
}

void Game::drawLives()
{
    // Use on sprite to draw lives up to the livesNo
    for(int i = 0; i < ship.getLives(); i++)
    {
        shipHpSprite.setPosition({16.f + 32.f * i, 28.f});
        window.draw(shipHpSprite);
    }
}

void Game::checkDespawnedBullets()
{
    for(int i = 0; i < bullets.size(); i++)
    {
        if(bullets[i].isDespawned())
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Game::draw()
{
    window.clear();
    window.draw(ship.getSprite());
    window.draw(enemy.getSprite());
    drawEntities(asteroids);
    drawEntities(bullets);
    #if DEBUG 
    window.draw(ship.getDebugCircle());
    window.draw(enemy.getDebugCircle());
    drawDebugEntities(asteroids);
    drawDebugEntities(bullets);
    #endif
    window.draw(scoreText);
    drawLives();
    window.display();
}