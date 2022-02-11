#include "ParticleSystem.h"

#include <cmath>

ParticleSystem::ParticleSystem() 
{
    particles.reserve(20);
}

void ParticleSystem::spawn(ast::Vector2 pos, int particleNo, float lifetime)
{
    Particle particle;
    for(int i = 0; i < particleNo; i++)
    {
        ast::Vector2 randDir;
        float randAng = rand() % 360;
        randDir.x = std::cos(randAng * PI/180);
        randDir.y = std::sin(randAng * PI/180);
        float randSpeed = (rand() % 50 + 50) / 10.f;
        particle = Particle({pos.x, pos.y}, randDir, randSpeed, lifetime);
        particles.push_back(particle);
    }
    empty = false;
}

void ParticleSystem::update(sf::Time dt)
{
    for(int i = particles.size()-1; i >= 0; i--)
    {
        if(!particles[i].isAlive())
            particles.erase(particles.begin() + i);
        particles[i].update(dt);
    }

    if(particles.empty())
        empty = true;
}

void ParticleSystem::clear()
{
    particles.clear();
}

bool ParticleSystem::isEmpty() { return empty; }

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(size_t i = 0; i < particles.size(); i++)
    {
        target.draw(particles[i], states);
    }
}