#include <cmath>
#include "Constants.h"
#include "Ship.h"
#include "TextureLoader.h"

Ship::Ship() { }

Ship::Ship(std::vector<Bullet>& bullets) 
    : Entity(ast::Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), "player")
{   
    // Init values for input
    rotateInput = 0;
    accelInput = 0;
    shootInput = 0;

    // Initializing the values
    hp = 3;
    dirOffset = -90.f;
    maxVel = 4.f;
    turningSpeed = 300.f;
    accel = 10.f;
    
    this->texture = TextureLoader::getInstance()->getShipTexture();
    indexToCurrentFrame = 0;
    setSprite({(float)indexToCurrentFrame, 0.f}, {32.f, 45.f});
    setCollider(16.f, pos);
    setOrigin({16.f, 16.f});

    this->bullets = &bullets;

    // Starting the clock for the shooting firerate
    shootCooldown = clock.restart();
    timeBetweenFrames = animationClock.restart();
    
    // Initializing pos and rot
    dir = dirOffset;
    vel = ast::Vector2(0.f, 0.f);
}

int Ship::getLives() { return hp; }
void Ship::takeDamage() { hp--; }

void Ship::reset()
{
    // Init values for input
    rotateInput = 0;
    accelInput = 0;
    shootInput = 0;

    // Initializing the values
    dirOffset = -90.f;

    // Initializing pos and rot
    this->pos = ast::Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    dir = dirOffset;
    vel = ast::Vector2(0.f, 0.f);
}

void Ship::animate()
{
    if(accelInput)
    {
        // Offset the sprite based on time passed
        timeBetweenFrames = animationClock.getElapsedTime();
        if(timeBetweenFrames.asSeconds() >= 0.15f)
        { 
            setSprite({(float)indexToCurrentFrame, 0.f}, {32.f, 45.f});
            indexToCurrentFrame += 32;
            indexToCurrentFrame %= 96;
            timeBetweenFrames = animationClock.restart();
        }
    }
    else
    {
        // We set the current frame to 32
        // to show the flame as soon as we press space
        indexToCurrentFrame = 32;
        setSprite({0.f, 0.f}, {32.f, 45.f});
    }
}

void Ship::getInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotateInput = 1;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotateInput = -1;
    else 
        rotateInput = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        accelInput = 1;
    else
        accelInput = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        shootInput = 1;
    else 
        shootInput = 0;
}

void Ship::rotate(sf::Time dt)
{
    if(rotateInput)
        dir += rotateInput * (turningSpeed * dt.asSeconds());
    gunDir = ast::Vector2(std::cos(dir * PI/180), std::sin(dir * PI/180));
    gunPos = gunDir * 14.f + pos;
    sprite.setRotation(dir - dirOffset);
}

void Ship::thrust(sf::Time dt)
{
    ast::Vector2 heading(std::cos(dir * PI/180), std::sin(dir * PI/180));
    if(accelInput)
        vel += (heading * accel * dt.asSeconds());
    vel.clamp(maxVel);   
}

void Ship::shoot()
{
    if(shootInput)
    {
        shootCooldown = clock.getElapsedTime();
        if(shootCooldown.asSeconds() >= .5f)
        {
            Bullet bullet;
            bullet = Bullet(gunPos, gunDir, 10.f, "bullet");
            bullets->push_back(bullet);
            shootCooldown = clock.restart();
        }
    }
}

void Ship::update(sf::Time dt)
{
    getInput();
    animate();
    Entity::wrap();
    rotate(dt);
    thrust(dt);
    Entity::move(vel);
    shoot();

}

ast::Vector2 Ship::getVelocityVector()
{
    return vel;
}

sf::CircleShape Ship::getDebugCircle()
{
    return collider.getDebugCircle();
}

sf::Sprite Ship::getSprite()
{
    return sprite;
}