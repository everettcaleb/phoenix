#pragma once
#ifndef INCLUDE_PHOENIX_GAME_H
#define INCLUDE_PHOENIX_GAME_H

#include "ComponentManager.h"
#include "EventManager.h"

class Game {
private:
    Game() {}
    Game(const Game& other) {}

public:
    ~Game(){}

    static bool IsForegroundApp;
    static ComponentManager *Components;
    static EventManager *Events;
};

#endif //INCLUDE_PHOENIX_GAME_H