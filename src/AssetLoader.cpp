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
    if(!font.loadFromFile("fonts/ARCADECLASSIC.TTF"))
        std::cerr << "Error loading font!" << std::endl;
}

sf::Font* AssetLoader::getFont()
{
    return &font;
}

void AssetLoader::loadTextures()
{
    loadTexture("player", "img/Ship.png");
    loadTexture("asteroids", "img/Asteroids.png");
    loadTexture("bullet", "img/Bullet.png");
    loadTexture("enemy", "img/Enemy.png");
    loadTexture("overlay", "img/Overlay.png");
}

sf::Texture* AssetLoader::getTexture(std::string id)
{
    auto it = textures.find(id);
    assert(it != textures.end());
    return &textures[id];
}