#include <iostream>
#include "src/include/Bullet.h"
#include "src/include/Constants.h"
#include "src/include/TextureLoader.h"

Bullet::Bullet() 
    : Entity(pos, "bullet")
{ 
    despawned = true;
    this->texture = TextureLoader::getInstance()->getBulletTexture();
    setSprite();
    setCollider(4.f, pos);
}

Bullet::Bullet(ast::Vector2 pos, ast::Vector2 dir, float speed) 
    : Entity(pos, "bullet")
{
    dirOffset = .0f;
    this->pos = pos;
    this->dir = dir;
    this->speed = speed;
    despawned = false;
    this->texture = TextureLoader::getInstance()->getBulletTexture();
    setSprite();
    setCollider(4.f, pos);
}

void Bullet::respawn(ast::Vector2 pos, ast::Vector2 dir, float speed)
{
    this->pos = pos;
    this->dir = dir;
    this->speed = speed;
    despawned = false;
}

void Bullet::update(sf::Time dt)
{
    float frameSpeed = speed / ((dt.asSeconds() == 0.f) ? .016f : dt.asSeconds());
    vel = dir * frameSpeed * dt.asSeconds();
    Entity::move(vel);
    despawn();
}

void Bullet::despawn()
{
    if(pos.x < 0.f || pos.x > WINDOW_WIDTH || pos.y < 0.f || pos.y > WINDOW_HEIGHT)
        despawned = true;
}

void Bullet::setDespawned(bool value)
{
    this->despawned = value;
}

bool Bullet::isDespawned()
{
    return despawned;
}