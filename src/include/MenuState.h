#pragma once

#include <SFML/Graphics.hpp>

class Asteroids;

class MenuState
{
protected:
    Asteroids* context;
    sf::RenderWindow* window;
    sf::Font* font;
public:
    virtual ~MenuState();
    void setContext(Asteroids* context);

    virtual bool pollEvents() = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw() = 0;
};
