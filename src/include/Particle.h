#pragma once

#include "Entity.h"
#include "Vector2.h"
#include "AssetLoader.h"

class Particle : public sf::Drawable
{
private:
    sf::Texture* texture;
    sf::Sprite sprite;
    ast::Vector2 pos;
    ast::Vector2 dir;
    float speed;
    float lifetime;
    float stLifetime;
    float alive;
public:
    Particle();
    Particle(ast::Vector2 pos, ast::Vector2 dir, float speed, float lifetime);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
