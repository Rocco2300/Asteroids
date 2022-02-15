#include "Asteroids.h"

Asteroids::Asteroids() : state{nullptr} { }

Asteroids::Asteroids(MenuState* state) : state{nullptr}
{
    createWindow("Asteroids", 60);
    setState(state);
}

Asteroids::~Asteroids()
{
    delete state;
}

void Asteroids::createWindow(std::string name, int frameLimit)
{
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), name);
    window.setFramerateLimit(frameLimit);
    window.setVerticalSyncEnabled(false);
}

void Asteroids::update()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        state->pollEvents();
        state->update(dt);
        state->draw(); 
    }
}

void Asteroids::setState(MenuState* state)
{
    if(this->state != nullptr)
        delete state;
    this->state = state;
    this->state->setContext(this);
}

sf::RenderWindow* Asteroids::getWindow()
{
    return &window;
}