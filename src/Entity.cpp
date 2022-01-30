#include <iostream>
#include "Constants.h"
#include "Entity.h"

Entity::Entity() {} 

Entity::Entity(ast::Vector2 initialPos, std::string colliderTag)
{
    // Initializing pos and rot
    pos = initialPos;
    vel = ast::Vector2(0.f, 0.f);
    this->colliderTag = colliderTag;
}

void Entity::setOrigin(ast::Vector2 pos)
{
    sprite.setOrigin(pos.toSfVector2f());
}

void Entity::setCollider()
{
    collider.create(pos, colliderRadius, colliderTag);
}

void Entity::setCollider(float radius, ast::Vector2 pos)
{
    collider.create(pos, radius, colliderTag);
}

// We use this function for textures that contain just one sprite
void Entity::setSprite()
{
    sprite.setTexture(*this->texture);
    sf::Vector2u texSize = this->texture->getSize();
    sprite.setOrigin(texSize.x / 2, texSize.y / 2);
    sprite.setPosition(pos.toSfVector2f());
    sprite.setRotation(dirOffset);

    colliderRadius = std::min(texSize.x, texSize.y);
}

// We use this function for textures that contain multiple sprites for more control
void Entity::setSprite(ast::Vector2 pos, ast::Vector2 size)
{
    sprite.setTexture(*this->texture);
    sprite.setTextureRect(sf::IntRect(pos.x, pos.y, size.x, size.y));
    sprite.setPosition(pos.toSfVector2f());
    sprite.setRotation(dirOffset);
}

void Entity::wrap()
{
    if(pos.x > WINDOW_WIDTH) pos.x = 0.f;
    else if(pos.x < 0.f) pos.x = WINDOW_WIDTH;
    if(pos.y > WINDOW_HEIGHT) pos.y = 0.f;
    else if(pos.y < 0.f) pos.y = WINDOW_HEIGHT;
}

CircleCollider Entity::getCircleCollider()
{
    return collider;
}

void Entity::move(ast::Vector2 vector) 
{
    pos += vector;
    sprite.setPosition(pos.toSfVector2f());
    collider.setPosition(pos);
} 

void Entity::update(sf::Time dt) { }
ast::Vector2 Entity::getPosition() { return pos; }

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
    #if DEBUG
    target.draw(collider, states);
    #endif
}