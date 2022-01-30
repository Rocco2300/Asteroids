#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

/*
This is a singleton class used for loading the 
textures needed just once
*/
class AssetLoader
{
public:
    static AssetLoader* getInstance();
    void destroyInstance();
    void loadTextures();

    sf::Texture* getShipTexture();
    sf::Texture* getBulletTexture();
    sf::Texture* getAsteroidTexture();
    sf::Texture* getEnemyTexture();
private:
    AssetLoader() { }
    static AssetLoader* instance;

    sf::Texture ShipTexture;
    sf::Texture BulletTexture;
    sf::Texture AsteroidTexture;
    sf::Texture EnemyTexture;
};


