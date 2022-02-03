#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include "Game.h"
#include "AssetLoader.h"

#define FRAMECOUNTER false

Game::Game()
{ 
    srand(time(NULL));
    createWindow("Asteroids", 60);
    AssetLoader* assetLoader = AssetLoader::getInstance();
    assetLoader->loadFont();
    assetLoader->loadTextures();
    // assetLoader->loadSounds();
    
    shipHpTexture = assetLoader->getTexture("player");
    shipHpSprite.setTexture(*shipHpTexture);
    shipHpSprite.setTextureRect({0, 0, 32, 32});
    shipHpSprite.setOrigin({16.f, 16.f});
    shipHpSprite.setScale({.75f, .75f});

    overlay = assetLoader->getTexture("overlay");
    overlaySpr.setTexture(*overlay);
    overlaySpr.setPosition({0.f, 0.f});

    font = assetLoader->getFont();
    scoreText.setFont(*font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setOrigin({30.f, 0.f});
    scoreText.setPosition({800.f, 0.f});

    gameOverText.setFont(*font);
    gameOverText.setCharacterSize(54);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setString("Game Over!");
    gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
    gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

    ship = Ship(bullets);

    gameOver = false;
    manager = GameManager(ship, asteroids, bullets, enemy);
    scoreText.setString(std::to_string(manager.getScore()));
}

void Game::createWindow(std::string name, int frameLimit)
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), name);
    window.setFramerateLimit(frameLimit);
    window.setVerticalSyncEnabled(false);
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
                window.close();
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
            {
                reset();
                manager.reset();
                state = GameState::Running;
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::N)
            {
                asteroids.clear();
            }
        }

        if(!gameOver)
        {
            state = manager.update();
            if(state == GameState::GameOver)
            {
                gameOver = true;
                continue;
            }

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
        }

        // Framerate counter
        #if FRAMECOUNTER
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
    gameOver = false;
    ship = Ship(bullets);
    bullets.clear();
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
    for(size_t i = 0; i < v.size(); i++)
    {
        window.draw(v[i]);
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
    window.draw(ship);
    window.draw(enemy);
    drawEntities(asteroids);
    drawEntities(bullets);
    if(!gameOver)
    {
        window.draw(scoreText);
        drawLives();
    }
    else
    {
        sf::Text finalScoreText;
        finalScoreText.setFont(*font);
        finalScoreText.setCharacterSize(36);
        finalScoreText.setFillColor(sf::Color::White);
        window.draw(overlaySpr);
        window.draw(gameOverText);
        finalScoreText.setString("Score");
        finalScoreText.setOrigin(finalScoreText.getLocalBounds().width / 2, finalScoreText.getLocalBounds().height / 2);
        finalScoreText.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 50.f});
        window.draw(finalScoreText);
        finalScoreText.setString(std::to_string(manager.getScore()));
        finalScoreText.setOrigin(finalScoreText.getLocalBounds().width / 2, finalScoreText.getLocalBounds().height / 2);
        finalScoreText.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 75.f});
        window.draw(finalScoreText);
    }
    window.display();
}