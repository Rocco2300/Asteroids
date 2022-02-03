#pragma once

#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include "AssetLoader.h"

class SoundManager
{
private:
    AssetLoader* assetLoader;
    std::map<std::string, sf::SoundBuffer*> buffers;
    std::map<std::string, sf::Sound> sounds;
public:
    SoundManager();
    void loadSound(std::string id);
    void setBuffers();
    void playSound(std::string id);
};

