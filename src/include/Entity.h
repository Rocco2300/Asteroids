#pragma once

#include <SFML/Graphics.hpp>
#include "CircleCollider.h"

class Entity // : public sf::Transformable
{
protected:
    CircleCollider collider;
    std::string colliderTag;
    int colliderRadius;
    sf::Texture* texture;
    sf::Sprite sprite;
    ast::Vector2 pos;
    ast::Vector2 vel;

    float dirOffset;
public:
    Entity();
    Entity(ast::Vector2 initialPos, std::string colliderTag);
    virtual void setOrigin(ast::Vector2 pos);
    virtual void setCollider(float radius, ast::Vector2 pos);
    virtual void setSprite();
    virtual void setSprite(ast::Vector2 pos, ast::Vector2 size);
    virtual void wrap();
    virtual void move(ast::Vector2 vector);
    virtual void update(sf::Time dt);
    virtual CircleCollider getCircleCollider();
    virtual sf::CircleShape getDebugCircle();
    virtual sf::Sprite getSprite();
    virtual ast::Vector2 getPosition();
};

