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

    font = assetLoader->getFont();
    titleText.setFont(*font);
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    titleText.setString("Asteroids");
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
    titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 50.f);
    startText.setFont(*font);
    startText.setCharacterSize(25);
    startText.setString("PRESS   ENTER");
    startText.setOrigin(startText.getLocalBounds().width / 2, startText.getLocalBounds().height / 2);
    startText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    overlay.setTexture(*assetLoader->getTexture("overlay"));

    std::vector<AsteroidSize> sizes = {Small, Small, Small, Small, Small, Medium, Medium, Large, Large, Large};
    spawner.init(nullptr, &asteroids);
    spawner.spawnAsteroids(sizes);
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
    updateEntities(asteroids, dt);
}

template <typename T>
void MainMenu::updateEntities(std::vector<T>& v, sf::Time dt)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        v[i].update(dt);
    }
}

template <typename T>
void MainMenu::drawEntities(std::vector<T>& v)
{
    for(size_t i = 0; i < v.size(); i++)
    {
        window->draw(v[i]);
    }
}

void MainMenu::draw()
{
    window->clear();
    drawEntities(asteroids);
    window->draw(overlay);
    window->draw(titleText);
    window->draw(startText);
    window->display();
}