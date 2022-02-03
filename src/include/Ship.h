#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Entity.h"
#include "Vector2.h"
#include "CircleCollider.h"
#include "Asteroid.h"
#include "Bullet.h"

class Ship : public Entity
{
private:
    int rotateInput;
    int accelInput;
    int shootInput;

    sf::Clock clock;
    sf::Time shootCooldown;

    sf::Clock animationClock;
    sf::Time timeBetweenFrames;
    int indexToCurrentFrame;

    ast::Vector2 gunDir;
    ast::Vector2 gunPos;
    std::vector<Bullet> *bullets;

    int hp;
    float dir;
    float maxVel;
    float turningSpeed;
    float accelTime;
    float accel;
public:
    Ship();
    Ship(std::vector<Bullet>& bullet);
    int getLives();
    void takeDamage();
    void reset();
    void getInput();
    void animate();
    void rotate(sf::Time dt);
    void thrust(sf::Time dt);
    void shoot();
    void update(sf::Time dt);
    ast::Vector2 getVelocityVector();
};