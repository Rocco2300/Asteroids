#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

/*
This is a singleton class used for loading the 
textures needed just once
*/
class AssetLoader
{
public:
    static AssetLoader* getInstance();
    void destroyInstance();
    void loadFont();
    void loadTextures();
    void loadSounds();

    sf::Font* getFont();
    sf::Texture* getShipTexture();
    sf::Texture* getBulletTexture();
    sf::Texture* getAsteroidTexture();
    sf::Texture* getEnemyTexture();
    sf::Texture* getOverlayTexture();
    // sf::SoundBuffer* getShootSoundBuffer();
private:
    AssetLoader() { }
    static AssetLoader* instance;

    sf::Font font;
    sf::Texture shipTexture;
    sf::Texture bulletTexture;
    sf::Texture asteroidTexture;
    sf::Texture enemyTexture;
    sf::Texture overlayTexture;
    // sf::SoundBuffer shootSoundBuffer;
};


