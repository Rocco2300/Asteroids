#include "Enemy.h"
#include "TextureLoader.h"
#include <cmath>

Enemy::Enemy()
{
    alive = false;
}

Enemy::Enemy(ast::Vector2 pos, ast::Vector2 dir, float speed,
    std::vector<Bullet>* bullets) : Entity(pos, "enemy")
{
    this->dir.normalize();
    this->dir = dir;
    this->speed = speed;
    this->alive = true;

    this->bullets = bullets;
    this->bulletSpeed = 10.f;
    this->shootTime = clock.getElapsedTime();
    this->predict = false;
    this->shootCount = 2;

    this->texture = TextureLoader::getInstance()->getEnemyTexture();
    setSprite();
    setCollider(18.f, pos);
}

void Enemy::calculateShootDir(ast::Vector2 tp, ast::Vector2 tv)
{
    // tp = Target Position
    // tv = Target Velocity
    float a = tv.x*tv.x + tv.y*tv.y - bulletSpeed*bulletSpeed;
    float b = 2 * (tv.x * (tp.x - pos.x) + tv.y * (tp.y - pos.y));
    float c = (tp.x - pos.x)*(tp.x - pos.x) + (tp.y - pos.y)*(tp.y - pos.y);

    float delta = b*b - 4*a*c;
    // std::cout << delta << std::endl;
    if(delta >= 0 && predict)
    {
        float t1 = (-b + sqrt(delta)) / (2*a);
        float t2 = (-b - sqrt(delta)) / (2*a);

        float t = std::max(t1, t2);
        ast::Vector2 intersection;
        intersection.x = t * tv.x + tp.x;
        intersection.y = t * tv.y + tp.y;

        shootDir = intersection - pos;
        shootDir.normalize();
    }
    else
    {
        shootDir = tp - pos;
        shootDir.normalize();
    }
}

void Enemy::shoot()
{
    Bullet bullet;
    bullet = Bullet(pos + (shootDir * 24.f), shootDir, bulletSpeed, "enemyBullet");
    bullets->push_back(bullet);
    shootCount--;
}

void Enemy::update(sf::Time dt, ast::Vector2 tp, ast::Vector2 tv)
{
    float frameSpeed = speed / ((dt.asSeconds() == 0.f) ? .016f : dt.asSeconds());
    vel = dir * frameSpeed * dt.asSeconds();
    Entity::move(vel);
    currentTime = clock.getElapsedTime();
    if((currentTime - shootTime).asSeconds() >= 2.f)
    {
        if(shootCount == 0)
            predict = true;
        else if(shootCount < 0)
        {
            predict = false;
            shootCount = 2;
        }
        calculateShootDir(tp, tv);
        shoot();
        shootTime = clock.getElapsedTime();
    }
    Entity::wrap();
}

bool Enemy::isAlive() { return alive; }