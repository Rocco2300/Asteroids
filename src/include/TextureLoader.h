#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

class TextureLoader
{
public:
    static TextureLoader* getInstance();
    void destroyInstance();
    void loadTextures();

    sf::Texture* getShipTexture();
    sf::Texture* getBulletTexture();
    sf::Texture* getAsteroidTexture();
private:
    TextureLoader() { }
    static TextureLoader* instance;

    sf::Texture ShipTexture;
    sf::Texture BulletTexture;
    sf::Texture AsteroidTexture;
};


