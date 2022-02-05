#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.h"

class ParticleSystem : public sf::Drawable
{
private:
    std::vector<Particle> particles;
    bool empty;
public:
    ParticleSystem();
    // ParticleSystem(ast::Vector2 pos, int particleNo, float lifetime);
    void spawn(ast::Vector2 pos, int particleNo, float lifetime);
    void update(sf::Time dt);
    void clear();
    bool isEmpty();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
