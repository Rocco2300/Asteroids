#include "Enemy.h"
#include "TextureLoader.h"

Enemy::Enemy()
{
    
}

Enemy::Enemy(ast::Vector2 pos, ast::Vector2 dir, float speed)
    : Entity(pos, "enemy")
{
    dirOffset = 0.f;
    dir.normalize();
    this->dir = dir;
    this->speed = speed;

    this->texture = TextureLoader::getInstance()->getEnemyTexture();
    setSprite();
    setCollider(18.f, pos);
}

void Enemy::update(sf::Time dt)
{
    float frameSpeed = speed / ((dt.asSeconds() == 0.f) ? .016f : dt.asSeconds());
    vel = dir * frameSpeed * dt.asSeconds();
    Entity::move(vel);
    Entity::wrap();
}