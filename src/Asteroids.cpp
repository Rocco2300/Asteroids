#include "Asteroids.h"

Asteroids::Asteroids() : state{nullptr} 
{
    createWindow("Asteroids", 60);
}

Asteroids::Asteroids(std::unique_ptr<MenuState>& state) : state{nullptr}
{
    createWindow("Asteroids", 60);
    setState(state);
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
        bool changedState = state->pollEvents();
        
        if(!changedState)
        {    
            state->update(dt);
            state->draw(); 
        }
    }
}

void Asteroids::setState(std::unique_ptr<MenuState>& state)
{
    this->state = std::move(state);
}

sf::RenderWindow* Asteroids::getWindow()
{
    return &window;
}