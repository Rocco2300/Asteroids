#include "AssetLoader.h"
#include <cassert>

AssetLoader* AssetLoader::instance = nullptr;

AssetLoader* AssetLoader::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AssetLoader();
    }
    return instance;
}

void AssetLoader::loadTexture(std::string id, std::string path)
{
    sf::Texture texture;
    if(!texture.loadFromFile(path))
        std::cerr << "Error loading texture " << id << "!\n";
    texture.setRepeated(false);
    textures.insert(std::make_pair(id, std::move(texture)));
}

void AssetLoader::loadSoundBuffer(std::string id, std::string path)
{
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile(path))
        std::cerr << "Error loading buffer " << id << "!\n";
    soundBuffers.insert(std::make_pair(id, std::move(buffer)));
}

void AssetLoader::loadFont()
{
    if(loadedFont)
        return;
    if(!font.loadFromFile("fonts/ARCADECLASSIC.TTF"))
        std::cerr << "Error loading font!" << std::endl;
    loadedFont = true;
}

void AssetLoader::loadTextures()
{
    if(loadedTextures)
        return;
    loadTexture("player", "img/Ship.png");
    loadTexture("asteroids", "img/Asteroids.png");
    loadTexture("bullet", "img/Bullet.png");
    loadTexture("enemy", "img/Enemy.png");
    loadTexture("overlay", "img/Overlay.png");
    loadTexture("particle", "img/Particle.png");
    loadedTextures = true;
}

void AssetLoader::loadSounds()
{
    if(loadedSounds)
        return;
    loadSoundBuffer("shoot", "sound/Shoot.wav");
    loadSoundBuffer("ship_explosion", "sound/Ship_Explosion.wav");
    loadedSounds = true;
}

sf::Texture* AssetLoader::getTexture(std::string id)
{
    auto it = textures.find(id);
    assert(it != textures.end());
    return &textures[id];
}

sf::SoundBuffer* AssetLoader::getSoundBuffer(std::string id)
{
    auto it = soundBuffers.find(id);
    assert(it != soundBuffers.end());
    return &soundBuffers[id];
}

sf::Font* AssetLoader::getFont()
{
    return &font;
}
