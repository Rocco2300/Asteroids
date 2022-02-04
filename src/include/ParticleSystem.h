#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.h"

class ParticleSystem : public sf::Drawable
{
private:
    ast::Vector2 pos;
    std::vector<Particle> particles;
    float lifetime;
    int particleNo;
    bool empty;
public:
    ParticleSystem();
    ParticleSystem(ast::Vector2 pos, int particleNo, float lifetime);
    void spawn();
    void update(sf::Time dt);
    void clear();
    bool isEmpty();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
