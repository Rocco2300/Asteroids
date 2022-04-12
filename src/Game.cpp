#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include "Game.h"
#include "AssetLoader.h"
#include "MainMenu.h"

#define FRAMECOUNTER false

Game::Game(Asteroids* context)
{ 
    srand(time(NULL));
    AssetLoader* assetLoader = AssetLoader::getInstance();
    window = context->getWindow();
    setContext(context);
    
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

    ship = Ship(bullets);
        
    soundManager.playMusic("sound/Game_theme.wav");
    soundManager.changeMusicVolume("sound/Game_theme.wav", 20);

    gameOver = false;
    paused = false;
    manager = GameManager(&ship, &asteroids, &bullets, &enemy, &particles, &soundManager);
    scoreText.setString(std::to_string(manager.getScore()));
}

bool Game::pollEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R)
        {
            reset();
            manager.reset();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && gameOver)
        {
            std::unique_ptr<MenuState> newState(new MainMenu(context));
            soundManager.stopMusic("sound/Game_theme.wav");
            context->setState(newState);
            return true;
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !gameOver)
        {
            paused = !paused;
            if(paused)
                soundManager.changeMusicVolume("sound/Game_theme.wav", 5);
            else
                soundManager.changeMusicVolume("sound/Game_theme.wav", 20);
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N)
            asteroids.clear();
    }
    return false;
}

void Game::update(sf::Time dt)
{
    if(!paused)
    {
        state = manager.update();
        if(state == GameState::GameOver)
        {
            gameOver = true;
        }

        ship.update(dt);
        if(enemy.isAlive())
            enemy.update(dt, ship.getPosition(), ship.getVelocityVector());
        particles.update(dt);
        updateEntities(asteroids, dt);
        updateEntities(bullets, dt);
        checkDespawnedBullets();

        // Correct the score display to display at the edge regardless of width of text
        int score = manager.getScore();
        float offset = (score > 0) ? ((int)floor(log10(score)) * 20.f) + 30.f : 30.f;
        scoreText.setOrigin({offset, 0.f});
        scoreText.setString(std::to_string(manager.getScore()));
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
        window->draw(v[i]);
    }
}

void Game::drawLives()
{
    // Use on sprite to draw lives up to the livesNo
    for(int i = 0; i < ship.getLives(); i++)
    {
        shipHpSprite.setPosition({16.f + 32.f * i, 28.f});
        window->draw(shipHpSprite);
    }
}

void Game::checkDespawnedBullets()
{
    for(size_t i = 0; i < bullets.size(); i++)
    {
        if(bullets[i].isDespawned())
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void Game::draw()
{
    window->clear();
    if(ship.getLives() != 0)
        window->draw(ship);
    window->draw(enemy);
    window->draw(particles);
    drawEntities(asteroids);
    drawEntities(bullets);
    if(gameOver || paused)
        window->draw(overlaySpr);

    if(paused)
    {
        sf::Text text;
        text.setFont(*font);
        text.setCharacterSize(64);
        text.setString("Paused");
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        text.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
        window->draw(text);
    }

    if(!gameOver && !paused)
    {
        window->draw(scoreText);
        drawLives();
    }
    else if(gameOver)
    {
        sf::Text gameOverText;
        sf::Text finalScoreText;
        gameOverText.setFont(*font);
        gameOverText.setCharacterSize(54);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setString("Game Over!");
        gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
        gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
        window->draw(gameOverText);
        finalScoreText.setFont(*font);
        finalScoreText.setCharacterSize(36);
        finalScoreText.setFillColor(sf::Color::White);
        finalScoreText.setString("Score");
        finalScoreText.setOrigin(finalScoreText.getLocalBounds().width / 2, finalScoreText.getLocalBounds().height / 2);
        finalScoreText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 50.f);
        window->draw(finalScoreText);
        finalScoreText.setString(std::to_string(manager.getScore()));
        finalScoreText.setOrigin(finalScoreText.getLocalBounds().width / 2, finalScoreText.getLocalBounds().height / 2);
        finalScoreText.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 75.f});
        window->draw(finalScoreText);
        gameOverText.setString("Press   R    to    restart");
        gameOverText.setCharacterSize(21);
        gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
        gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f);
        window->draw(gameOverText);
        gameOverText.setString("Press   ESC    to    return");
        gameOverText.setCharacterSize(21);
        gameOverText.setOrigin(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2);
        gameOverText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f + 20.f);
        window->draw(gameOverText);
    }
    window->display();
}