#pragma once

#include <iostream>
#include <string>
#include <map>
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
    void loadTexture(std::string id, std::string path);
    void loadSoundBuffer(std::string id, std::string path);
    void loadFont();
    void loadTextures();
    void loadSounds();

    sf::Font* getFont();
    sf::Texture* getTexture(std::string id);
    sf::SoundBuffer* getSoundBuffer(std::string id);
private:
    AssetLoader() { }
    static AssetLoader* instance;
    bool loadedTextures = false;
    bool loadedFont = false;
    bool loadedSounds = false;

    sf::Font font;
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> soundBuffers;

    sf::Texture shipTexture;
    sf::Texture bulletTexture;
    sf::Texture asteroidTexture;
    sf::Texture enemyTexture;
    sf::Texture overlayTexture;
};


