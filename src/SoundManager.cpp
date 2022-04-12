#include "SoundManager.h"
#include <cassert>
#include <thread>

SoundManager::SoundManager() 
{
    assetLoader = AssetLoader::getInstance();
}

void SoundManager::loadSound(std::string id)
{
    sf::SoundBuffer* buffer;
    buffer = assetLoader->getSoundBuffer(id);
    buffers.insert(std::make_pair(id, std::move(buffer)));
    sounds.insert(std::make_pair(id, sf::Sound()));
}

void SoundManager::setBuffers()
{
    for(auto& sound : sounds)
    {
        sound.second.setBuffer(*buffers.at(sound.first));
    }
}

void SoundManager::playSound(std::string id)
{
    auto it = sounds.find(id);
    assert(it != sounds.end());
    if(sounds[id].getStatus() != sf::Sound::Playing)
        sounds[id].play();
}

void SoundManager::playMusic(std::string path)
{
    // sf::Music music;
    std::unique_ptr<sf::Music> music(new sf::Music);

    if(!music->openFromFile(path))
    {
        std::cerr << "Error loading music file from " << path << std::endl;
        return;
    }

    playing.insert(std::make_pair(path, std::move(music)));
    playing[path]->play();
}

void SoundManager::stopMusic(std::string path)
{
    auto it = playing.find(path);
    assert(it != playing.end());
    playing[path]->stop();
    playing.erase(path);
}

void SoundManager::changeMusicVolume(std::string path, int volume)
{
    auto it = playing.find(path);
    assert(it != playing.end());
    playing[path]->setVolume(volume);
}