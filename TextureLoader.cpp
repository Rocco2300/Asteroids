#include "src/include/TextureLoader.h"

TextureLoader* TextureLoader::instance = nullptr;

TextureLoader* TextureLoader::getInstance()
{
    if (instance == nullptr)
    {
        instance = new TextureLoader();
    }
    return instance;
}

void TextureLoader::loadTextures()
{
    if(!ShipTexture.loadFromFile("img/Ship.png"))
        std::cerr << "Loading ship texture failed!" << std::endl;
    if(!BulletTexture.loadFromFile("img/Bullet.png"))
        std::cerr << "Loading bullet texture failed!" << std::endl;
    if(!AsteroidTexture.loadFromFile("img/Asteroids.png"))
        std::cerr << "Loading asteroid texture failed!" << std::endl;
    ShipTexture.setRepeated(false);
    BulletTexture.setRepeated(false);
    AsteroidTexture.setRepeated(false);
}

void TextureLoader::destroyInstance()
{
    delete instance;
}

sf::Texture* TextureLoader::getShipTexture()
{
    return &ShipTexture;
}

sf::Texture* TextureLoader::getBulletTexture()
{
    return &BulletTexture;
}

sf::Texture* TextureLoader::getAsteroidTexture()
{
    return &AsteroidTexture;
}
