#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

/*
This is a singleton class used for loading the 
textures needed just once
*/
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


