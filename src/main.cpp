#include "Asteroids.h"
#include "MainMenu.h"

int main()
{
    Asteroids asteroids;
    std::unique_ptr<MenuState> newState(new MainMenu(&asteroids));
    asteroids.setState(newState);
    asteroids.update();
    return 0;
}