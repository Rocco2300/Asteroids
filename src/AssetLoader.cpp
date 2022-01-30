#include "AssetLoader.h"

AssetLoader* AssetLoader::instance = nullptr;

AssetLoader* AssetLoader::getInstance()
{
    if (instance == nullptr)
    {
        instance = new AssetLoader();
    }
    return instance;
}

void AssetLoader::loadTextures()
{
    if(!ShipTexture.loadFromFile("img/Ship.png"))
        std::cerr << "Loading ship texture failed!" << std::endl;
    if(!BulletTexture.loadFromFile("img/Bullet.png"))
        std::cerr << "Loading bullet texture failed!" << std::endl;
    if(!AsteroidTexture.loadFromFile("img/Asteroids.png"))
        std::cerr << "Loading asteroid texture failed!" << std::endl;
    if(!EnemyTexture.loadFromFile("img/Enemy.png"))
        std::cerr << "Loading asteroid texture failed!" << std::endl;
    ShipTexture.setRepeated(false);
    BulletTexture.setRepeated(false);
    AsteroidTexture.setRepeated(false);
    EnemyTexture.setRepeated(false);
}

void AssetLoader::destroyInstance()
{
    delete instance;
}

sf::Texture* AssetLoader::getShipTexture()
{
    return &ShipTexture;
}

sf::Texture* AssetLoader::getBulletTexture()
{
    return &BulletTexture;
}

sf::Texture* AssetLoader::getAsteroidTexture()
{
    return &AsteroidTexture;
}

sf::Texture* AssetLoader::getEnemyTexture()
{
    return &EnemyTexture;
}
