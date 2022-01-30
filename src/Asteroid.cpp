#include "Asteroid.h"
#include "AssetLoader.h"

Asteroid::Asteroid() { }

Asteroid::Asteroid(ast::Vector2 pos, ast::Vector2 dir, float speed, AsteroidSize size) 
    : Entity(pos, "asteroid")
{
    dirOffset = 0.f;
    dir.normalize();
    this->dir = dir;
    this->speed = speed;
    this->dirOfRot = (rand() % 2 - .5f) * 2.f;
    this->rotationSpeed = (rand() % 60 + 30.f) * speed;

    this->texture = AssetLoader::getInstance()->getAsteroidTexture();
    this->size = size;

    int index = rand() % 3;
    int startY = (size == Large) ? 0.f 
               : (size == Medium) ? 128.f 
               : 192.f;
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
    dirOffset += dirOfRot * rotationSpeed * dt.asSeconds();
    this->sprite.setRotation(dirOffset);
}

ast::Vector2 Asteroid::getDirection() { return dir; }
AsteroidSize Asteroid::getSize() { return size; }