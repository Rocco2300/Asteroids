#include "MenuState.h"

MenuState::~MenuState() { }

void MenuState::setContext(Asteroids* context)
{
    this->context = context;
}