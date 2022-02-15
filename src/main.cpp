#include "Asteroids.h"

int main()
{
    Asteroids asteroids(new Game(asteroids));
    asteroids.update();
    return 0;
}