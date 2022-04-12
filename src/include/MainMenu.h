#pragma once

#include "Asteroids.h"
#include "MenuState.h"

class MainMenu : public MenuState
{
private:
    Spawner spawner;
    SoundManager soundManager;

    sf::Text titleText;
    sf::Text startText;
    sf::Sprite overlay;
    
    std::vector<Asteroid> asteroids;
public:
    MainMenu(Asteroids* asteroids);

    bool pollEvents();
    void update(sf::Time dt);
    void draw();
private:
    template <typename T>
    void updateEntities(std::vector<T>& v, sf::Time dt);
    template <typename T>
    void drawEntities(std::vector<T>& v);
};
