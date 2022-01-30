#pragma once

#include <SFML/Graphics.hpp>
#include "CircleCollider.h"
#include "Constants.h"

class Entity : public sf::Drawable
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
    virtual void setCollider();
    virtual void setCollider(float radius, ast::Vector2 pos);
    virtual void setSprite();
    virtual void setSprite(ast::Vector2 pos, ast::Vector2 size);
    virtual void wrap();
    virtual void move(ast::Vector2 vector);
    virtual void update(sf::Time dt);
    virtual CircleCollider getCircleCollider();
    virtual ast::Vector2 getPosition();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

