#include "Particle.h"

Particle::Particle()
{
    
}

Particle::Particle(ast::Vector2 pos, ast::Vector2 dir, float speed, float lifetime)
{
    this->pos = pos;
    this->dir = dir;
    this->dir.normalize();
    this->speed = speed;
    this->lifetime = lifetime;
    this->stLifetime = lifetime;
    this->alive = true;

    this->texture = AssetLoader::getInstance()->getTexture("particle");
    sprite.setTexture(*texture);
    sprite.setOrigin(texture->getSize().x/2, texture->getSize().y);
    sprite.setPosition(pos.toSfVector2f());
}

bool Particle::isAlive() { return alive; }

/*
f : [0, 2] -> [0, 1]
f(x) = {
    0.233 * x + 0.15, x <= 1.5 
    x - 1, x >  1.5
}
*/
float speedFalloff(float x)
{
    if(x < 0.f)
        return 0.15f;
    
    if(x > 2.f) 
        return 1.f;
    
    if(x <= 1.5f)
        return  0.233f * x + 0.15f;
    else
        return x - 1.f;
}

/*
f : [0, 2] -> [0, 1]
f(x) = {
    0.65 * x + 0.15, x <= 1 
    0.2 * x + 0.6, x >  1
}
*/
float alphaFalloff(float x)
{
    if(x < 0.f)
        return 0.15f;
    
    if(x > 2.f)
        return 1.f;
    
    if(x <= 1.f)
        return 0.65f * x + 0.15f;
    else
        return 0.2f * x + 0.6f;
}

void Particle::update(sf::Time dt)
{
    float frameSpeed = speed / ((dt.asSeconds() == 0.f) ? .016f : dt.asSeconds());
    ast::Vector2 vel = dir * frameSpeed * dt.asSeconds();
    // We clamp the values between 0.f and 2.f
    pos += vel * speedFalloff(lifetime / stLifetime * 2.f);
    sf::Uint8 alpha = alphaFalloff(lifetime / stLifetime * 2.f) * 255;

    sprite.setPosition(pos.toSfVector2f());
    sprite.setColor({255, 255, 255, alpha});

    lifetime -= dt.asSeconds();
    if(lifetime <= 0)
        alive = false;
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(alive)
        target.draw(sprite, states);
}