#pragma once

#include "Vector2.h"
#include "Entity.h"

class Bullet : public Entity
{
private:
    //ast::Vector2 pos;
    ast::Vector2 dir;
    float speed;
    bool despawned;
public:
    Bullet();
    Bullet(ast::Vector2 pos, ast::Vector2 dir, float speed);
    void respawn(ast::Vector2 pos, ast::Vector2 dir, float speed);
    void update(sf::Time dt);
    void despawn();
    void setDespawned(bool value);
    bool isDespawned();
};


