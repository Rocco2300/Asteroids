#include "Asteroid.h"
#include "TextureLoader.h"

Asteroid::Asteroid() { }

Asteroid::Asteroid(ast::Vector2 pos, ast::Vector2 dir, float speed) 
    : Entity(pos, "asteroid")
{
    dirOffset = 0.f;
    dir.normalize();
    this->dir = dir;
    this->speed = speed;

    this->texture = TextureLoader::getInstance()->getAsteroidTexture();
    int randSize = 2;// (rand() % 2) + 1;
    size = (AsteroidSize)(randSize * 32);

    int index = rand() % 3;
    int startY = (size == Large) ? 0.f : 64.f;
    setSprite({(float)index * size, (float)startY}, {(float)size, (float)size});
    setCollider(size / 2, pos);
    setOrigin({(float)size / 2, (float)size / 2});
}

Asteroid::Asteroid(ast::Vector2 pos, ast::Vector2 dir, float speed, AsteroidSize size) 
    : Entity(pos, "asteroid")
{
    dirOffset = 0.f;
    dir.normalize();
    this->dir = dir;
    this->speed = speed;

    this->texture = TextureLoader::getInstance()->getAsteroidTexture();
    this->size = size;

    int index = rand() % 3;
    int startY = (size == Large) ? 0.f : 64.f;
    setSprite({(float)index * size, (float)startY}, {(float)size, (float)size});
    setCollider(size / 2, pos);
    setOrigin({(float)size / 2, (float)size / 2});
}

void Asteroid::update(sf::Time dt)
{
    float frameSpeed = speed / ((dt.asSeconds() == 0.f) ? .016f : dt.asSeconds());
    vel = dir * frameSpeed * dt.asSeconds();
    Entity::move(vel);
    rotate(dt);
    Entity::wrap();
}

void Asteroid::rotate(sf::Time dt)
{
    dirOffset += 160.f * dt.asSeconds();
    this->sprite.setRotation(dirOffset);
}

ast::Vector2 Asteroid::getDirection() { return dir; }
AsteroidSize Asteroid::getSize() { return size; }