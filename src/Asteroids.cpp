#include "Asteroids.h"

Asteroids::Asteroids() : state{nullptr} { }

Asteroids::Asteroids(MenuState* state) : state{nullptr}
{
}

Asteroids::~Asteroids()
{
    delete state;
}

void Asteroids::update()
{
    // GameState state;
    // sf::Clock clk;
    // sf::Clock clock;

    // while (window.isOpen())
    // {
        
    // }
}

void Asteroids::setState(MenuState* state)
{
    if(this->state != nullptr)
        delete state;
    this->state = state;
    this->state->setContext(this);
}