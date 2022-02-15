#pragma once

#include <SFML/Graphics.hpp>

class Asteroids;

class MenuState
{
protected:
    Asteroids* context;
public:
    virtual ~MenuState();
    void setContext(Asteroids* context);

    virtual void pollEvents() = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw() = 0;
};
