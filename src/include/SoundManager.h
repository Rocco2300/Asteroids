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
    std::map<std::string, std::unique_ptr<sf::Music>> playing;
    // std::map<std::string, sf::Music> playing;
public:
    SoundManager();
    void loadSound(std::string id);
    void setBuffers();
    void playSound(std::string id);
    void playSound(std::string id, int volume);
    void playMusic(std::string path);
    void stopMusic(std::string path);
    void changeMusicVolume(std::string path, int volume);
};

