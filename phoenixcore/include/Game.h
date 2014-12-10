#pragma once
#ifndef INCLUDE_PHOENIX_GAME_H
#define INCLUDE_PHOENIX_GAME_H

#include "ComponentManager.h"

class Game {
private:
    Game() {}
    Game(const Game& other) {}

public:
    ~Game(){}

    static ComponentManager *Components;
};

#endif //INCLUDE_PHOENIX_GAME_H