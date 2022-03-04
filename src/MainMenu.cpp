#include "MainMenu.h"
#include "Game.h"

MainMenu::MainMenu(Asteroids* context)
{
    window = context->getWindow();
    AssetLoader* assetLoader = AssetLoader::getInstance();
    assetLoader->loadFont();
    assetLoader->loadTextures();
    assetLoader->loadSounds();
    setContext(context);

    font = AssetLoader::getInstance()->getFont();
    finalScoreText.setFont(*font);
    finalScoreText.setCharacterSize(64);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setString("Asteroids");
    finalScoreText.setOrigin(finalScoreText.getLocalBounds().width / 2, finalScoreText.getLocalBounds().height / 2);
    finalScoreText.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 50.f});

    manager.spawnAsteroids();
}

bool MainMenu::pollEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        {
            std::unique_ptr<MenuState> newState(new Game(context));
            context->setState(newState);
            return true;
        }
    }
    return false;
}

void MainMenu::update(sf::Time dt)
{
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    // {
    //     context->setState(new Game(context));
    // }
}

void MainMenu::draw()
{
    window->clear();
    window->draw(finalScoreText);
    window->display();
}