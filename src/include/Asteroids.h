#pragma once

#include <memory>
#include "MenuState.h"
#include "Game.h"

class Asteroids
{
private:
    sf::RenderWindow window;
    // MenuState* state;
    std::unique_ptr<MenuState> state;
public:
    Asteroids();
    Asteroids(std::unique_ptr<MenuState>& state);
    void createWindow(std::string name, int frameLimit);
    void setState(std::unique_ptr<MenuState>& state);
    void update();
    sf::RenderWindow* getWindow();
};

