#include "SoundManager.h"
#include <cassert>

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