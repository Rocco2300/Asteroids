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
    if(!shipTexture.loadFromFile("img/Ship.png"))
        std::cerr << "Loading ship texture failed!" << std::endl;
    if(!bulletTexture.loadFromFile("img/Bullet.png"))
        std::cerr << "Loading bullet texture failed!" << std::endl;
    if(!asteroidTexture.loadFromFile("img/Asteroids.png"))
        std::cerr << "Loading asteroid texture failed!" << std::endl;
    if(!enemyTexture.loadFromFile("img/Enemy.png"))
        std::cerr << "Loading asteroid texture failed!" << std::endl;
    if(!overlayTexture.loadFromFile("img/Overlay.png"))
        std::cerr << "Loading overlay texture failed!" << std::endl;
    shipTexture.setRepeated(false);
    bulletTexture.setRepeated(false);
    asteroidTexture.setRepeated(false);
    enemyTexture.setRepeated(false);
    overlayTexture.setRepeated(false);
}

// void AssetLoader::loadSounds()
// {
//     if(!shootSoundBuffer.loadFromFile("sounds/Shoot.wav"))
//         std::cerr << "Loading the shoot sound failed!" << std::endl;
// }

void AssetLoader::destroyInstance() { delete instance; }

sf::Texture* AssetLoader::getShipTexture() { return &shipTexture; }
sf::Texture* AssetLoader::getBulletTexture() { return &bulletTexture; }
sf::Texture* AssetLoader::getAsteroidTexture() { return &asteroidTexture; }
sf::Texture* AssetLoader::getEnemyTexture() { return &enemyTexture; }
sf::Texture* AssetLoader::getOverlayTexture() { return &overlayTexture; }
// sf::SoundBuffer* AssetLoader::getShootSoundBuffer() { return &shootSoundBuffer; }