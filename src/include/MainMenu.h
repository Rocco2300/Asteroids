#pragma once

#include "Asteroids.h"
#include "MenuState.h"

class MainMenu : public MenuState
{
private:
    sf::Text finalScoreText;
public:
    MainMenu(Asteroids* asteroids);

    bool pollEvents();
    void update(sf::Time dt);
    void draw();
};
