#pragma once

#include "MenuState.h"
#include "Game.h"

class Asteroids
{
private:
    sf::RenderWindow window;
    MenuState* state;
public:
    Asteroids();
    Asteroids(MenuState* state);
    ~Asteroids();
    void setState(MenuState* state);
    void update();
};

