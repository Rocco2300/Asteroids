#include "ParticleSystem.h"

#include <cmath>

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::ParticleSystem(ast::Vector2 pos, int particleNo, float lifetime)
{
    this->pos = pos;
    this->particleNo = particleNo;
    this->lifetime = lifetime;
    this->empty = true;
}

void ParticleSystem::spawn()
{
    Particle particle;
    for(int i = 0; i < particleNo; i++)
    {
        ast::Vector2 randDir;
        float randAng = rand() % 360;
        randDir.x = std::cos(randAng * PI/180);
        randDir.y = std::sin(randAng * PI/180);
        float randSpeed = (rand() % 50 + 50) / 10.f;
        particle = Particle({pos.x, pos.y}, randDir, randSpeed, .25f);
        particles.push_back(particle);
    }
    empty = false;
}

void ParticleSystem::update(sf::Time dt)
{
    for(int i = particleNo - 1; i >= 0; i--)
    {
        particles[i].update(dt);
        if(!particles[i].isAlive())
            particles.erase(particles.begin() + i);
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
    for(int i = 0; i < particleNo; i++)
    {
        target.draw(particles[i], states);
    }
}